#include <gtest/gtest.h>

#include <thread>

#include "SPSCQueue.h"

TEST(SPSCQueueTest, constructor) { SPSCQueue<int> test(1); }

TEST(SPSCQUeueTest, non_con_basic_operations) {
  SPSCQueue<int> test(10);

  auto result = test.try_pop();
  ASSERT_EQ(result, nullptr);
  ASSERT_TRUE(test.push(1));
  result = test.try_pop();
  ASSERT_EQ(*result, 1);

  ASSERT_EQ(test.try_pop(), nullptr);
}

TEST(SPSCQueueTest, simple_push_pop) {
  SPSCQueue<int> queue(10);
  std::thread producer([&queue]() {
    for (int i{}; i < 5; i++) {
      queue.push(i);
    }
  });

  std::thread consumer([&queue]() {
    for (int i{}; i < 5; i++) {
      auto result = queue.try_pop();
      if (result) {
        EXPECT_EQ(*result, i);
      }
    }
  });
  if (producer.joinable()) {
    producer.join();
  }
  if (consumer.joinable()) {
    consumer.join();
  }
}

TEST(SPSCQueueTest, non_con_fill_to_capacity) {
  int size = 10;
  SPSCQueue<int> test(size);

  for (int i{}; i < size - 1; i++) {
    ASSERT_TRUE(test.push(i));
  }

  ASSERT_FALSE(test.push(999));

  for (int i{}; i < size - 1; i++) {
    auto val = test.try_pop();
    ASSERT_NE(val, nullptr);
    ASSERT_EQ(*val, i);
  }
  ASSERT_TRUE(test.empty());
}

TEST(SPSCQueueTest, non_con_wrap_around) {
  const size_t capacity{10};
  SPSCQueue<int> queue(capacity);

  ASSERT_TRUE(queue.empty());

  for (int cycle{0}; cycle < 3; ++cycle) {
    for (size_t i{0}; i < capacity - 1; ++i) {
      ASSERT_TRUE(queue.push(i));
    }

    ASSERT_FALSE(queue.push(100000));

    // drain in
    for (size_t i{}; i < capacity - 1; ++i) {
      auto val = queue.try_pop();
      ASSERT_NE(val, nullptr);
      ASSERT_EQ(*val, i);
    }
  }
  ASSERT_TRUE(queue.empty());
}

TEST(SPSCQueueTest, non_con_move_only_type) {
  SPSCQueue<std::unique_ptr<int>> queue(5);

  queue.push(std::make_unique<int>(42));
  queue.push(std::make_unique<int>(99));

  auto val1 = queue.try_pop();
  ASSERT_NE(val1, nullptr);
  ASSERT_EQ(**val1, 42);

  auto val2 = queue.try_pop();
  ASSERT_EQ(**val2, 99);

  ASSERT_TRUE(queue.empty());
}

TEST(SPSCQueueTest, concurrent_single_producer_consumer) {
  SPSCQueue<int> queue(1024);
  constexpr int NUM_ITEMS = 100000;
  std::atomic<bool> done{false};

  // Producer thread
  std::thread producer([&]() {
    for (int i = 0; i < NUM_ITEMS; ++i) {
      while (!queue.push(i)) {
        std::this_thread::yield();
      }
    }
    done.store(true, std::memory_order_release);
  });

  // Consumer thread
  std::thread consumer([&]() {
    int expected = 0;
    while (expected < NUM_ITEMS) {
      auto val = queue.try_pop();
      if (val) {
        ASSERT_EQ(*val, expected);
        expected++;
      } else {
        std::this_thread::yield();
      }
    }
  });

  producer.join();
  consumer.join();
  ASSERT_TRUE(queue.empty());
}
