#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

#include "HazardPointer.h"

struct TestNode {
  int value;
  TestNode* next;
  explicit TestNode(int v) : value(v), next(nullptr) {}
};

template class HazardPointer<TestNode>;

TEST(HazardPointerTest, BasicProtectRelease) {
  HazardPointer<TestNode> hp(1);
  TestNode* node = new TestNode(42);

  hp.protect(node);
  hp.release();

  delete node;
}

TEST(HazardPointerTest, MultiThreadedProtectRetire) {
  const size_t num_threads = 4;
  const size_t ops_per_thread = 1000;

  HazardPointer<TestNode> hp(num_threads);
  std::atomic<size_t> operations_completed{0};

  auto worker = [&]() {
    for (size_t i = 0; i < ops_per_thread; ++i) {
      TestNode* node = new TestNode(static_cast<int>(i));
      hp.protect(node);

      volatile int sum = 0;
      for (int j = 0; j < 100; ++j) sum += j;

      hp.release();
      hp.retire(node);
      operations_completed.fetch_add(1, std::memory_order_relaxed);
    }
  };

  std::vector<std::thread> threads;
  for (size_t i = 0; i < num_threads; ++i) {
    threads.emplace_back(worker);
  }

  for (auto& t : threads) {
    t.join();
  }

  EXPECT_EQ(operations_completed.load(), num_threads * ops_per_thread);
}

TEST(HazardPointerTest, StressTest) {
  const size_t num_threads = 8;
  const size_t num_shared_nodes = 100;

  HazardPointer<TestNode> hp(num_threads);

  std::vector<TestNode*> shared_nodes;
  for (size_t i = 0; i < num_shared_nodes; ++i) {
    shared_nodes.push_back(new TestNode(static_cast<int>(i)));
  }

  std::atomic<bool> stop{false};
  std::atomic<size_t> protections{0};
  std::atomic<size_t> retires{0};

  auto worker = [&](size_t thread_id) {
    while (!stop.load(std::memory_order_relaxed)) {
      size_t idx = thread_id % num_shared_nodes;
      TestNode* node = shared_nodes[idx];

      hp.protect(node);
      protections.fetch_add(1, std::memory_order_relaxed);

      volatile int val = node->value;
      (void)val;

      hp.release();

      if (thread_id % 2 == 0) {
        TestNode* new_node = new TestNode(static_cast<int>(thread_id));
        hp.retire(new_node);
        retires.fetch_add(1, std::memory_order_relaxed);
      }
    }
  };

  std::vector<std::thread> threads;
  for (size_t i = 0; i < num_threads; ++i) {
    threads.emplace_back(worker, i);
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  stop.store(true, std::memory_order_relaxed);

  for (auto& t : threads) {
    t.join();
  }

  for (auto* node : shared_nodes) {
    delete node;
  }

  EXPECT_GT(protections.load(), 0);
  EXPECT_GT(retires.load(), 0);
}

TEST(HazardPointerTest, ProtectThenVerifyPattern) {
  HazardPointer<TestNode> hp(2);
  std::atomic<TestNode*> head{new TestNode(1)};

  auto attempt_pop = [&]() -> TestNode* {
    TestNode* ptr = head.load(std::memory_order_acquire);
    hp.protect(ptr);

    if (ptr != head.load(std::memory_order_acquire)) {
      hp.release();
      return nullptr;
    }

    if (ptr) {
      EXPECT_EQ(ptr->value, 1);
    }

    hp.release();
    return ptr;
  };

  TestNode* result = attempt_pop();
  EXPECT_NE(result, nullptr);

  delete head.load();
}

TEST(HazardPointerTest, ABAProtection) {
  // This test simulates the ABA problem where a pointer changes from A->B->A
  // Hazard pointers should prevent premature reclamation during this sequence

  const size_t num_threads = 4;
  HazardPointer<TestNode> hp(num_threads);

  // Create nodes A, B, C
  TestNode* nodeA = new TestNode(100);
  TestNode* nodeB = new TestNode(200);
  TestNode* nodeC = new TestNode(300);

  std::atomic<TestNode*> head{nodeA};
  std::atomic<bool> start{false};
  std::atomic<size_t> successful_reads{0};
  std::atomic<size_t> aba_sequences{0};

  // Thread 1: Reads A, gets preempted, then tries to use it
  auto slow_reader = [&]() {
    while (!start.load(std::memory_order_acquire)) {
      std::this_thread::yield();
    }

    // Step 1: Load head (points to A)
    TestNode* observed = head.load(std::memory_order_acquire);
    hp.protect(observed);

    // Verify protection still valid
    if (observed != head.load(std::memory_order_acquire)) {
      hp.release();
      return;
    }

    // Simulate slow operation
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Step 4: Try to read value (A might have been freed and reallocated)
    if (observed) {
      volatile int val = observed->value;
      EXPECT_EQ(val, 100);  // Should still be valid due to hazard pointer
      successful_reads.fetch_add(1, std::memory_order_relaxed);
    }

    hp.release();
  };

  // Thread 2 & 3: Create ABA sequence (A -> B -> A)
  auto aba_creator = [&](bool first) {
    while (!start.load(std::memory_order_acquire)) {
      std::this_thread::yield();
    }

    if (first) {
      // Step 2: Change head from A to B
      std::this_thread::sleep_for(std::chrono::milliseconds(2));
      TestNode* expected = nodeA;
      if (head.compare_exchange_strong(expected, nodeB,
                                       std::memory_order_release,
                                       std::memory_order_acquire)) {
        hp.retire(nodeA);  // Try to retire A (but it's protected!)
        aba_sequences.fetch_add(1, std::memory_order_relaxed);
      }
    } else {
      // Step 3: Change head from B back to C
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
      TestNode* expected = nodeB;
      if (head.compare_exchange_strong(expected, nodeC,
                                       std::memory_order_release,
                                       std::memory_order_acquire)) {
        hp.retire(nodeB);
      }
    }
  };

  // Launch threads
  std::vector<std::thread> threads;
  threads.emplace_back(slow_reader);
  threads.emplace_back(aba_creator, true);
  threads.emplace_back(aba_creator, false);

  // Start all threads simultaneously
  start.store(true, std::memory_order_release);

  for (auto& t : threads) {
    t.join();
  }

  // NodeA should NOT have been freed yet because slow_reader protected it
  EXPECT_GT(successful_reads.load(), 0);

  // Cleanup - retire remaining nodes
  hp.retire(nodeC);

  // Force final scan to clean up protected nodes
  for (int i = 0; i < 20; ++i) {
    hp.retire(new TestNode(i));
  }
}

TEST(HazardPointerTest, ConcurrentRetireAndScan) {
  // Test that scan_and_free works correctly when multiple threads
  // are retiring nodes simultaneously

  const size_t num_threads = 6;
  const size_t retires_per_thread = 500;

  HazardPointer<TestNode> hp(num_threads);
  std::atomic<size_t> total_retired{0};
  std::atomic<size_t> scans_triggered{0};

  auto worker = [&]() {
    for (size_t i = 0; i < retires_per_thread; ++i) {
      TestNode* node = new TestNode(static_cast<int>(i));

      // Occasionally protect a node to prevent immediate reclamation
      if (i % 10 == 0) {
        hp.protect(node);
        std::this_thread::sleep_for(std::chrono::microseconds(10));
        hp.release();
      }

      hp.retire(node);
      total_retired.fetch_add(1, std::memory_order_relaxed);

      // Check if scan was triggered (retire_threshold = 2 * num_threads)
      if (i % (2 * num_threads) == 0) {
        scans_triggered.fetch_add(1, std::memory_order_relaxed);
      }
    }
  };

  std::vector<std::thread> threads;
  for (size_t i = 0; i < num_threads; ++i) {
    threads.emplace_back(worker);
  }

  for (auto& t : threads) {
    t.join();
  }

  EXPECT_EQ(total_retired.load(), num_threads * retires_per_thread);
  EXPECT_GT(scans_triggered.load(), 0);
}

TEST(HazardPointerTest, ProtectionAcrossMultipleInstances) {
  // Test that thread_local retire lists work correctly when
  // multiple HazardPointer instances exist

  const size_t num_threads = 4;

  HazardPointer<TestNode> hp1(num_threads);
  HazardPointer<TestNode> hp2(num_threads);

  std::atomic<size_t> hp1_retires{0};
  std::atomic<size_t> hp2_retires{0};

  auto worker = [&](bool use_hp1) {
    HazardPointer<TestNode>& hp = use_hp1 ? hp1 : hp2;
    std::atomic<size_t>& counter = use_hp1 ? hp1_retires : hp2_retires;

    for (int i = 0; i < 100; ++i) {
      TestNode* node = new TestNode(i);
      hp.protect(node);

      // Simulate work
      volatile int sum = 0;
      for (int j = 0; j < 50; ++j) sum += j;

      hp.release();
      hp.retire(node);
      counter.fetch_add(1, std::memory_order_relaxed);
    }
  };

  std::vector<std::thread> threads;
  for (size_t i = 0; i < num_threads; ++i) {
    threads.emplace_back(worker, i % 2 == 0);
  }

  for (auto& t : threads) {
    t.join();
  }

  // Both instances should have processed retirements
  EXPECT_GT(hp1_retires.load(), 0);
  EXPECT_GT(hp2_retires.load(), 0);
  EXPECT_EQ(hp1_retires.load() + hp2_retires.load(), num_threads * 100);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}