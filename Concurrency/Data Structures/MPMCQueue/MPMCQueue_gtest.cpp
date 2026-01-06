#include <gtest/gtest.h>

#include <atomic>
#include <thread>
#include <unordered_set>
#include <vector>

#include "MPMCQueue.h"

TEST(MPMCQueueTest, Constructor) { MPMCQueue<int> queue(10); }

TEST(MPMCQueueTest, NonConBasicOperations) {
  MPMCQueue<int> queue(10);

  auto result = queue.pop();
  ASSERT_FALSE(result.has_value());

  queue.push(1);
  result = queue.pop();
  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(*result, 1);

  ASSERT_FALSE(queue.pop().has_value());
}

TEST(MPMCQueueTest, NonConFillToCapacity) {
  int size = 10;
  MPMCQueue<int> queue(size);

  for (int i = 0; i < size - 1; i++) {
    queue.push(i);
  }

  // Queue should be full (capacity - 1 usable slots in ring buffer)
  ASSERT_FALSE(queue.try_push(999));

  for (int i = 0; i < size - 1; i++) {
    auto val = queue.pop();
    ASSERT_TRUE(val.has_value());
    ASSERT_EQ(*val, i);
  }

  ASSERT_TRUE(queue.empty());
}

TEST(MPMCQueueTest, NonConWrapAround) {
  const size_t capacity = 10;
  MPMCQueue<int> queue(capacity);

  ASSERT_TRUE(queue.empty());

  for (int cycle = 0; cycle < 3; ++cycle) {
    for (size_t i = 0; i < capacity - 1; ++i) {
      queue.push(static_cast<int>(i));
    }

    ASSERT_FALSE(queue.try_push(100000));

    for (size_t i = 0; i < capacity - 1; ++i) {
      auto val = queue.pop();
      ASSERT_TRUE(val.has_value());
      ASSERT_EQ(*val, static_cast<int>(i));
    }
  }

  ASSERT_TRUE(queue.empty());
}

TEST(MPMCQueueTest, TryPushTryPop) {
  MPMCQueue<int> queue(5);

  ASSERT_TRUE(queue.try_push(1));
  ASSERT_TRUE(queue.try_push(2));
  ASSERT_TRUE(queue.try_push(3));
  ASSERT_TRUE(queue.try_push(4));
  ASSERT_FALSE(queue.try_push(5));  // Full

  auto val = queue.try_pop();
  ASSERT_TRUE(val.has_value());
  ASSERT_EQ(*val, 1);

  val = queue.try_pop();
  ASSERT_TRUE(val.has_value());
  ASSERT_EQ(*val, 2);

  ASSERT_TRUE(queue.try_push(5));  // Space available now
}

TEST(MPMCQueueTest, SingleProducerSingleConsumer) {
  MPMCQueue<int> queue(1024);
  constexpr int NUM_ITEMS = 100000;

  std::thread producer([&queue]() {
    for (int i = 0; i < NUM_ITEMS; ++i) {
      queue.push(i);
    }
  });

  std::thread consumer([&queue]() {
    for (int i = 0; i < NUM_ITEMS; ++i) {
      auto item = queue.pop();
      while (!item) {
        std::this_thread::yield();
        item = queue.pop();
      }
      EXPECT_EQ(*item, i);
    }
  });

  producer.join();
  consumer.join();
  ASSERT_TRUE(queue.empty());
}

TEST(MPMCQueueTest, MultipleProducersSingleConsumer) {
  MPMCQueue<int> queue(1024);
  constexpr int NUM_PRODUCERS = 4;
  constexpr int ITEMS_PER_PRODUCER = 10000;
  constexpr int TOTAL_ITEMS = NUM_PRODUCERS * ITEMS_PER_PRODUCER;

  std::vector<std::thread> producers;
  for (int p = 0; p < NUM_PRODUCERS; ++p) {
    producers.emplace_back([&queue, p]() {
      for (int i = 0; i < ITEMS_PER_PRODUCER; ++i) {
        queue.push(p * ITEMS_PER_PRODUCER + i);
      }
    });
  }

  std::atomic<int> consumed{0};
  std::thread consumer([&queue, &consumed]() {
    while (consumed.load(std::memory_order_relaxed) < TOTAL_ITEMS) {
      auto item = queue.pop();
      if (item) {
        consumed.fetch_add(1, std::memory_order_relaxed);
      } else {
        std::this_thread::yield();
      }
    }
  });

  for (auto& t : producers) {
    t.join();
  }
  consumer.join();

  ASSERT_EQ(consumed.load(), TOTAL_ITEMS);
  ASSERT_TRUE(queue.empty());
}

TEST(MPMCQueueTest, SingleProducerMultipleConsumers) {
  MPMCQueue<int> queue(1024);
  constexpr int NUM_CONSUMERS = 4;
  constexpr int TOTAL_ITEMS = 40000;

  std::atomic<bool> done{false};
  std::atomic<int> consumed{0};

  std::thread producer([&queue, &done]() {
    for (int i = 0; i < TOTAL_ITEMS; ++i) {
      queue.push(i);
    }
    done.store(true, std::memory_order_release);
  });

  std::vector<std::thread> consumers;
  for (int c = 0; c < NUM_CONSUMERS; ++c) {
    consumers.emplace_back([&queue, &done, &consumed]() {
      while (!done.load(std::memory_order_acquire) || !queue.empty()) {
        auto item = queue.pop();
        if (item) {
          consumed.fetch_add(1, std::memory_order_relaxed);
        } else {
          std::this_thread::yield();
        }
      }
    });
  }

  producer.join();
  for (auto& t : consumers) {
    t.join();
  }

  ASSERT_EQ(consumed.load(), TOTAL_ITEMS);
}

TEST(MPMCQueueTest, MultipleProducersMultipleConsumers) {
  MPMCQueue<int> queue(1024);
  constexpr int NUM_PRODUCERS = 4;
  constexpr int NUM_CONSUMERS = 4;
  constexpr int ITEMS_PER_PRODUCER = 10000;
  constexpr int TOTAL_ITEMS = NUM_PRODUCERS * ITEMS_PER_PRODUCER;

  std::atomic<int> produced{0};
  std::atomic<int> consumed{0};

  std::vector<std::thread> producers;
  for (int p = 0; p < NUM_PRODUCERS; ++p) {
    producers.emplace_back([&queue, &produced]() {
      for (int i = 0; i < ITEMS_PER_PRODUCER; ++i) {
        queue.push(i);
        produced.fetch_add(1, std::memory_order_relaxed);
      }
    });
  }

  std::vector<std::thread> consumers;
  for (int c = 0; c < NUM_CONSUMERS; ++c) {
    consumers.emplace_back([&queue, &consumed, &produced]() {
      while (consumed.load(std::memory_order_relaxed) < TOTAL_ITEMS) {
        auto item = queue.pop();
        if (item) {
          consumed.fetch_add(1, std::memory_order_relaxed);
        } else {
          std::this_thread::yield();
        }
      }
    });
  }

  for (auto& t : producers) {
    t.join();
  }
  for (auto& t : consumers) {
    t.join();
  }

  ASSERT_EQ(produced.load(), TOTAL_ITEMS);
  ASSERT_EQ(consumed.load(), TOTAL_ITEMS);
}

TEST(MPMCQueueTest, TryPushContention) {
  MPMCQueue<int> queue(100);
  constexpr int NUM_THREADS = 8;
  constexpr int ATTEMPTS_PER_THREAD = 10000;

  std::atomic<int> successful_pushes{0};

  std::vector<std::thread> threads;
  for (int t = 0; t < NUM_THREADS; ++t) {
    threads.emplace_back([&queue, &successful_pushes]() {
      for (int i = 0; i < ATTEMPTS_PER_THREAD; ++i) {
        if (queue.try_push(i)) {
          successful_pushes.fetch_add(1, std::memory_order_relaxed);
        }
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  // Drain the queue and verify count
  int drained = 0;
  while (queue.pop()) {
    drained++;
  }

  ASSERT_EQ(drained, successful_pushes.load());
}
