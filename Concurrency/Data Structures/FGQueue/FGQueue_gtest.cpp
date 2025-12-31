#include <gtest/gtest.h>

#include <atomic>
#include <thread>
#include <vector>

#include "FGQueue.h"

// Basic operations
TEST(FGQueue, PushPop) {
  FGQueue<int> q;
  q.push(42);
  auto val = q.try_pop();
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, 42);
}

TEST(FGQueue, PopEmpty) {
  FGQueue<int> q;
  EXPECT_EQ(q.try_pop(), nullptr);
}

TEST(FGQueue, FIFO) {
  FGQueue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);

  auto v1 = q.try_pop();
  auto v2 = q.try_pop();
  auto v3 = q.try_pop();

  ASSERT_NE(v1, nullptr);
  ASSERT_NE(v2, nullptr);
  ASSERT_NE(v3, nullptr);

  EXPECT_EQ(*v1, 1);
  EXPECT_EQ(*v2, 2);
  EXPECT_EQ(*v3, 3);
  EXPECT_EQ(q.try_pop(), nullptr);
}

TEST(FGQueue, MultiplePushPop) {
  FGQueue<int> q;

  for (int i = 0; i < 100; ++i) {
    q.push(i);
  }

  for (int i = 0; i < 100; ++i) {
    auto val = q.try_pop();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, i);
  }

  EXPECT_EQ(q.try_pop(), nullptr);
}

// Concurrent tests
TEST(FGQueue, ConcurrentPush) {
  FGQueue<int> q;
  const int num_threads = 4;
  const int pushes_per_thread = 1000;

  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; ++i) {
    threads.emplace_back([&q, pushes_per_thread]() {
      for (int j = 0; j < pushes_per_thread; ++j) {
        q.push(j);
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  // Count total items
  int count = 0;
  while (q.try_pop() != nullptr) {
    count++;
  }
  EXPECT_EQ(count, num_threads * pushes_per_thread);
}

TEST(FGQueue, ConcurrentPushPop) {
  FGQueue<int> q;
  std::atomic<int> push_count{0};
  std::atomic<int> pop_count{0};
  const int operations = 10000;

  // 2 producer threads
  std::vector<std::thread> threads;
  for (int i = 0; i < 2; ++i) {
    threads.emplace_back([&q, &push_count, operations]() {
      for (int j = 0; j < operations; ++j) {
        q.push(j);
        push_count++;
      }
    });
  }

  // 2 consumer threads
  for (int i = 0; i < 2; ++i) {
    threads.emplace_back([&q, &pop_count, operations]() {
      for (int j = 0; j < operations; ++j) {
        while (!q.try_pop()) {
          std::this_thread::yield();
        }
        pop_count++;
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  EXPECT_EQ(push_count, 2 * operations);
  EXPECT_EQ(pop_count, 2 * operations);
  EXPECT_EQ(q.try_pop(), nullptr);
}

TEST(FGQueue, ProducerConsumer) {
  FGQueue<int> q;
  std::atomic<bool> done{false};
  std::atomic<int> total{0};

  // Producer
  std::thread producer([&q, &done]() {
    for (int i = 1; i <= 100; ++i) {
      q.push(i);
      std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    done = true;
  });

  // Consumer
  std::thread consumer([&q, &done, &total]() {
    while (!done || q.try_pop() != nullptr) {
      auto val = q.try_pop();
      if (val) {
        total += *val;
      }
    }
  });

  producer.join();
  consumer.join();

  // Sum of 1 to 100 = 5050
  EXPECT_EQ(total, 5050);
}

TEST(FGQueue, StressTest) {
  FGQueue<int> q;
  const int num_producers = 4;
  const int num_consumers = 4;
  const int items_per_producer = 1000;

  std::atomic<int> produced{0};
  std::atomic<int> consumed{0};

  std::vector<std::thread> threads;

  // Producers
  for (int i = 0; i < num_producers; ++i) {
    threads.emplace_back([&q, &produced, items_per_producer]() {
      for (int j = 0; j < items_per_producer; ++j) {
        q.push(j);
        produced++;
      }
    });
  }

  // Consumers
  for (int i = 0; i < num_consumers; ++i) {
    threads.emplace_back(
        [&q, &consumed, &produced, num_producers, items_per_producer]() {
          while (consumed < num_producers * items_per_producer) {
            auto val = q.try_pop();
            if (val) {
              consumed++;
            } else {
              std::this_thread::yield();
            }
          }
        });
  }

  for (auto& t : threads) {
    t.join();
  }

  EXPECT_EQ(produced, num_producers * items_per_producer);
  EXPECT_EQ(consumed, num_producers * items_per_producer);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
