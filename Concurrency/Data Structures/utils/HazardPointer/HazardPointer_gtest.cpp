#include "HazardPointer.h"
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <atomic>

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

TEST(HazardPointerTest, RetireUnprotected) {
  HazardPointer<TestNode> hp(1);

  for (int i = 0; i < 10; ++i) {
    hp.retire(new TestNode(i));
  }

  // After scan, all should be deleted
  EXPECT_EQ(hp.get_retired_count(), 0);
}

TEST(HazardPointerTest, ProtectPreventsReclaim) {
  HazardPointer<TestNode> hp(2);
  TestNode* node = new TestNode(99);

  hp.protect(node);
  hp.retire(node);

  // Node should still be in retire list (protected)
  EXPECT_GT(hp.get_retired_count(), 0);

  hp.release();

  // Trigger another scan
  for (int i = 0; i < 10; ++i) {
    hp.retire(new TestNode(i));
  }

  EXPECT_EQ(hp.get_retired_count(), 0);
}

TEST(HazardPointerTest, MultiThreadedProtectRetire) {
  const size_t num_threads = 4;
  const size_t ops_per_thread = 1000;

  HazardPointer<TestNode> hp(num_threads);
  std::atomic<size_t> operations_completed{0};

  auto worker = [&]() {
    for (size_t i = 0; i < ops_per_thread; ++i) {
      TestNode* node = new TestNode(i);
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
    shared_nodes.push_back(new TestNode(i));
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
        TestNode* new_node = new TestNode(thread_id);
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

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
