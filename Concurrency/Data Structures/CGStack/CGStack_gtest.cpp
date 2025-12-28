#include <gtest/gtest.h>

#include <thread>

#include "CGStack.h"

// Basic operations
TEST(CGStack, PushPop) {
  CGStack<int> s;
  s.push(42);
  auto val = s.pop();
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, 42);
}

TEST(CGStack, PopEmpty) {
  CGStack<int> s;
  EXPECT_EQ(s.pop(), nullptr);
}

TEST(CGStack, Peek) {
  CGStack<int> s;
  s.push(10);
  auto val = s.peek();
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, 10);
  // still there after peek
  EXPECT_NE(s.pop(), nullptr);
}

TEST(CGStack, LIFO) {
  CGStack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(*s.pop(), 3);
  EXPECT_EQ(*s.pop(), 2);
  EXPECT_EQ(*s.pop(), 1);
}

// Concurrency test
TEST(CGStack, ConcurrentPush) {
  CGStack<int> s;
  const int num_threads = 4;
  const int pushes_per_thread = 1000;

  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; i++) {
    threads.emplace_back([&s, pushes_per_thread]() {
      for (int j = 0; j < pushes_per_thread; j++) {
        s.push(j);
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  // pop everything, count
  int count = 0;
  while (s.pop() != nullptr) {
    count++;
  }
  EXPECT_EQ(count, num_threads * pushes_per_thread);
}
