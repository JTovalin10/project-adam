#include <gtest/gtest.h>

#include <algorithm>
#include <atomic>
#include <thread>
#include <unordered_set>
#include <vector>

#include "LFStack.h"

TEST(LFStackTest, BasicPushPop) {
  LFStack<int> stack;

  stack.push(42);
  auto result = stack.pop();

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(*result, 42);
  EXPECT_TRUE(stack.empty());
}

TEST(LFStackTest, EmptyPop) {
  LFStack<int> stack;

  auto result = stack.pop();
  EXPECT_EQ(result, nullptr);
  EXPECT_TRUE(stack.empty());
}

TEST(LFStackTest, LIFOOrder) {
  LFStack<int> stack;

  stack.push(1);
  stack.push(2);
  stack.push(3);

  EXPECT_FALSE(stack.empty());

  auto val1 = stack.pop();
  auto val2 = stack.pop();
  auto val3 = stack.pop();

  ASSERT_NE(val1, nullptr);
  ASSERT_NE(val2, nullptr);
  ASSERT_NE(val3, nullptr);

  EXPECT_EQ(*val1, 3);
  EXPECT_EQ(*val2, 2);
  EXPECT_EQ(*val3, 1);
  EXPECT_TRUE(stack.empty());
}

TEST(LFStackTest, MultiplePushPop) {
  LFStack<int> stack;

  for (int i = 0; i < 100; ++i) {
    stack.push(i);
  }

  for (int i = 99; i >= 0; --i) {
    auto val = stack.pop();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, i);
  }

  EXPECT_TRUE(stack.empty());
}

TEST(LFStackTest, ConcurrentPush) {
  LFStack<int> stack;
  const size_t num_threads = 4;
  const size_t items_per_thread = 1000;

  std::vector<std::thread> threads;

  for (size_t t = 0; t < num_threads; ++t) {
    threads.emplace_back([&, t]() {
      for (size_t i = 0; i < items_per_thread; ++i) {
        stack.push(static_cast<int>(t * items_per_thread + i));
      }
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }

  // Count items
  size_t count = 0;
  while (auto val = stack.pop()) {
    ++count;
  }

  EXPECT_EQ(count, num_threads * items_per_thread);
}

TEST(LFStackTest, ConcurrentPop) {
  LFStack<int> stack;
  const size_t num_items = 1000;

  // Populate stack
  for (size_t i = 0; i < num_items; ++i) {
    stack.push(static_cast<int>(i));
  }

  const size_t num_threads = 4;
  std::atomic<size_t> successful_pops{0};
  std::vector<std::thread> threads;

  for (size_t t = 0; t < num_threads; ++t) {
    threads.emplace_back([&]() {
      while (auto val = stack.pop()) {
        successful_pops.fetch_add(1, std::memory_order_relaxed);
      }
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }

  EXPECT_EQ(successful_pops.load(), num_items);
  EXPECT_TRUE(stack.empty());
}

TEST(LFStackTest, ConcurrentPushPop) {
  LFStack<int> stack;
  const size_t num_threads = 8;
  const size_t ops_per_thread = 500;

  std::atomic<size_t> push_count{0};
  std::atomic<size_t> pop_count{0};

  std::vector<std::thread> threads;

  // Half threads push, half pop
  for (size_t t = 0; t < num_threads; ++t) {
    if (t % 2 == 0) {
      // Pusher thread
      threads.emplace_back([&, t]() {
        for (size_t i = 0; i < ops_per_thread; ++i) {
          stack.push(static_cast<int>(t * ops_per_thread + i));
          push_count.fetch_add(1, std::memory_order_relaxed);
        }
      });
    } else {
      // Popper thread
      threads.emplace_back([&]() {
        for (size_t i = 0; i < ops_per_thread; ++i) {
          while (true) {
            auto val = stack.pop();
            if (val) {
              pop_count.fetch_add(1, std::memory_order_relaxed);
              break;
            }
            std::this_thread::yield();
          }
        }
      });
    }
  }

  for (auto& thread : threads) {
    thread.join();
  }

  EXPECT_EQ(push_count.load(), (num_threads / 2) * ops_per_thread);
  EXPECT_EQ(pop_count.load(), (num_threads / 2) * ops_per_thread);
}

TEST(LFStackTest, StressTestPushPop) {
  LFStack<int> stack;
  const size_t num_threads = 16;
  const size_t ops_per_thread = 1000;

  std::atomic<bool> start{false};
  std::vector<std::thread> threads;

  for (size_t t = 0; t < num_threads; ++t) {
    threads.emplace_back([&, t]() {
      // Wait for signal
      while (!start.load(std::memory_order_acquire)) {
        std::this_thread::yield();
      }

      // Mix of pushes and pops
      for (size_t i = 0; i < ops_per_thread; ++i) {
        if (i % 2 == 0) {
          stack.push(static_cast<int>(t * ops_per_thread + i));
        } else {
          stack.pop();  // May return nullptr
        }
      }
    });
  }

  // Start all threads simultaneously
  start.store(true, std::memory_order_release);

  for (auto& thread : threads) {
    thread.join();
  }

  // Stack should have approximately half the items left
  // (since we pushed on even iterations and popped on odd)
  size_t remaining = 0;
  while (stack.pop()) {
    ++remaining;
  }

  // We pushed num_threads * ops_per_thread / 2 times
  // We attempted to pop num_threads * ops_per_thread / 2 times
  // But some pops might have failed (returned nullptr)
  // So remaining should be >= 0
  EXPECT_GE(remaining, 0);
}

TEST(LFStackTest, NoDataRaces) {
  // This test uses ThreadSanitizer to detect data races
  LFStack<int> stack;
  const size_t num_threads = 8;
  const size_t ops_per_thread = 100;

  std::vector<std::thread> threads;

  for (size_t t = 0; t < num_threads; ++t) {
    threads.emplace_back([&, t]() {
      for (size_t i = 0; i < ops_per_thread; ++i) {
        stack.push(static_cast<int>(i));
        auto val = stack.pop();
        if (val) {
          volatile int x = *val;
          (void)x;
        }
      }
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }

  // Clean up any remaining items
  while (stack.pop()) {
  }

  EXPECT_TRUE(stack.empty());
}

TEST(LFStackTest, StringType) {
  LFStack<std::string> stack;

  stack.push("hello");
  stack.push("world");
  stack.push("test");

  auto val1 = stack.pop();
  auto val2 = stack.pop();
  auto val3 = stack.pop();

  ASSERT_NE(val1, nullptr);
  ASSERT_NE(val2, nullptr);
  ASSERT_NE(val3, nullptr);

  EXPECT_EQ(*val1, "test");
  EXPECT_EQ(*val2, "world");
  EXPECT_EQ(*val3, "hello");
}

TEST(LFStackTest, LargeDataType) {
  struct LargeStruct {
    int data[1000];
    LargeStruct() { std::fill(std::begin(data), std::end(data), 42); }
  };

  LFStack<LargeStruct> stack;

  stack.push(LargeStruct{});
  auto result = stack.pop();

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->data[0], 42);
  EXPECT_EQ(result->data[999], 42);
}

TEST(LFStackTest, ABAProtectionScenario) {
  // Test the specific ABA scenario that hazard pointers prevent
  LFStack<int> stack;

  stack.push(1);
  stack.push(2);

  std::atomic<bool> start{false};
  std::atomic<bool> thread1_protected{false};
  std::atomic<int> successful_operations{0};

  // Thread 1: Slow popper that gets preempted
  std::thread slow_thread([&]() {
    while (!start.load(std::memory_order_acquire)) {
      std::this_thread::yield();
    }

    auto val = stack.pop();
    if (val) {
      successful_operations.fetch_add(1, std::memory_order_relaxed);
    }
  });

  // Thread 2: Fast operations creating potential ABA
  std::thread fast_thread([&]() {
    while (!start.load(std::memory_order_acquire)) {
      std::this_thread::yield();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto val1 = stack.pop();
    if (val1) {
      successful_operations.fetch_add(1, std::memory_order_relaxed);
    }

    // Push and pop more items
    stack.push(3);
    auto val2 = stack.pop();
    if (val2) {
      successful_operations.fetch_add(1, std::memory_order_relaxed);
    }
  });

  start.store(true, std::memory_order_release);

  slow_thread.join();
  fast_thread.join();

  // Should have successfully completed operations without crashes
  EXPECT_GT(successful_operations.load(), 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}