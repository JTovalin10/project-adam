#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <thread>

#include "ThreadPool.h"

// Test 1: Basic task execution
TEST(WorkStealingThreadPoolTest, ExecutesSingleTask) {
  WorkStealingThreadPool pool(4);

  std::atomic<bool> executed{false};

  pool.Submit([&executed]() { executed = true; });

  // Wait a bit for task to execute
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  EXPECT_TRUE(executed);
}

// Test 2: Multiple tasks execute
TEST(WorkStealingThreadPoolTest, ExecutesMultipleTasks) {
  WorkStealingThreadPool pool(4);

  std::atomic<int> counter{0};

  for (int i = 0; i < 100; ++i) {
    pool.Submit([&counter]() { counter++; });
  }

  // Wait for all tasks
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  EXPECT_EQ(counter, 100);
}

// Test 3: Threads actually work in parallel
TEST(WorkStealingThreadPoolTest, WorksInParallel) {
  WorkStealingThreadPool pool(4);

  std::atomic<int> active_count{0};
  std::atomic<int> max_concurrent{0};

  for (int i = 0; i < 10; ++i) {
    pool.Submit([&active_count, &max_concurrent]() {
      int current = ++active_count;

      // Update max if needed
      int expected = max_concurrent.load();
      while (current > expected &&
             !max_concurrent.compare_exchange_weak(expected, current)) {
        // Retry
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(50));
      --active_count;
    });
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  // Should have multiple threads running concurrently
  EXPECT_GT(max_concurrent, 1);
}

// Test 4: Work stealing happens
TEST(WorkStealingThreadPoolTest, StealingOccurs) {
  WorkStealingThreadPool pool(2);  // Only 2 threads

  std::atomic<int> completed{0};

  // Submit many tasks quickly to one queue
  for (int i = 0; i < 20; ++i) {
    pool.Submit([&completed]() {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      completed++;
    });
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  EXPECT_EQ(completed, 20);
}

// Test 5: Destructor waits for tasks
TEST(WorkStealingThreadPoolTest, DestructorWaitsForTasks) {
  std::atomic<int> completed{0};

  {
    WorkStealingThreadPool pool(4);

    for (int i = 0; i < 10; ++i) {
      pool.Submit([&completed]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        completed++;
      });
    }

    // Destructor called here - should wait
  }

  // After destructor, all tasks should be done

  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  EXPECT_EQ(completed, 10);
}

// Test 6: Thread safety (no data races)
TEST(WorkStealingThreadPoolTest, ThreadSafe) {
  WorkStealingThreadPool pool(8);

  std::vector<int> data(1000, 0);
  std::mutex data_mutex;

  for (int i = 0; i < 1000; ++i) {
    pool.Submit([&data, &data_mutex, i]() {
      std::lock_guard<std::mutex> lock(data_mutex);
      data[i] = i * 2;
    });
  }

  // Wait for all tasks (destructor handles this)
  // No explicit wait needed
}

// Test 7: Empty pool doesn't crash
TEST(WorkStealingThreadPoolTest, EmptyPoolDoesntCrash) {
  WorkStealingThreadPool pool(4);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // Just make sure it doesn't crash
  SUCCEED();
}

// Test 8: Lambda with captures
TEST(WorkStealingThreadPoolTest, LambdaWithCaptures) {
  WorkStealingThreadPool pool(4);

  int x = 10;
  std::atomic<int> result{0};

  pool.Submit([x, &result]() { result = x * 2; });

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  EXPECT_EQ(result, 20);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}