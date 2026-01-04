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
