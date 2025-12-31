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

TEST(CGStack, WaitAndPop) {
  CGStack<int> stack;
  std::atomic<bool> popped{false};
  std::atomic<int> value{0};

  // Start consumer thread that waits
  std::thread consumer([&stack, &popped, &value]() {
    auto val = stack.wait_and_pop();  // Blocks until item available
    value = *val;
    popped = true;
  });

  // Give consumer time to start waiting
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // Consumer should be blocked
  EXPECT_FALSE(popped);

  // Producer pushes item
  stack.push(42);

  // Wait for consumer to wake up and pop
  consumer.join();

  // Verify consumer got the item
  EXPECT_TRUE(popped);
  EXPECT_EQ(value, 42);
}

TEST(CGStack, WaitAndPopMultipleConsumers) {
  CGStack<int> stack;
  std::atomic<int> total{0};
  std::mutex total_mutex;

  // Start 3 consumer threads
  std::vector<std::thread> consumers;
  for (int i = 0; i < 3; ++i) {
    consumers.emplace_back([&stack, &total, &total_mutex]() {
      auto val = stack.wait_and_pop();
      std::lock_guard<std::mutex> lock(total_mutex);
      total += *val;
    });
  }

  // Give consumers time to wait
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // Push 3 items
  stack.push(10);
  stack.push(20);
  stack.push(30);

  // Wait for all consumers
  for (auto& t : consumers) {
    t.join();
  }

  // Each consumer should have gotten one item
  EXPECT_EQ(total, 60);  // 10 + 20 + 30
}
TEST(CGStack, WaitAndPeek) {
  CGStack<int> stack;
  std::atomic<bool> peeked{false};
  std::atomic<int> value{0};

  // Start thread that waits to peek
  std::thread peeker([&stack, &peeked, &value]() {
    auto val = stack.wait_and_peek();  // Blocks until item available
    value = *val;
    peeked = true;
  });

  // Give peeker time to start waiting
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // Peeker should be blocked
  EXPECT_FALSE(peeked);

  // Push item
  stack.push(42);

  // Wait for peeker to wake up
  peeker.join();

  // Verify peeker saw the item
  EXPECT_TRUE(peeked);
  EXPECT_EQ(value, 42);

  // Item should STILL be in stack (peek doesn't remove)
  auto popped = stack.pop();
  ASSERT_NE(popped, nullptr);
  EXPECT_EQ(*popped, 42);
}

TEST(CGStack, WaitAndPeekMultiplePeekers) {
  CGStack<int> stack;
  std::atomic<int> peek_count{0};

  // Start 3 peeker threads
  std::vector<std::thread> peekers;
  for (int i = 0; i < 3; ++i) {
    peekers.emplace_back([&stack, &peek_count]() {
      auto val = stack.wait_and_peek();
      if (val && *val == 99) {
        peek_count++;
      }
    });
  }

  // Give peekers time to wait
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // Push one item
  stack.push(99);

  // Wait for all peekers
  for (auto& t : peekers) {
    t.join();
  }

  // All 3 should have peeked the same item
  EXPECT_EQ(peek_count, 3);

  // Item still in stack
  auto popped = stack.pop();
  ASSERT_NE(popped, nullptr);
  EXPECT_EQ(*popped, 99);
}

TEST(CGStack, MoveConstructor) {
  CGStack<int> s1;
  s1.push(10);
  s1.push(20);
  s1.push(30);

  // Move construct s2 from s1
  CGStack<int> s2(std::move(s1));

  // s2 should have the items
  EXPECT_EQ(*s2.pop(), 30);
  EXPECT_EQ(*s2.pop(), 20);
  EXPECT_EQ(*s2.pop(), 10);
  EXPECT_EQ(s2.pop(), nullptr);
}

TEST(CGStack, MoveAssignment) {
  CGStack<int> s1;
  s1.push(10);
  s1.push(20);

  CGStack<int> s2;
  s2.push(99);  // s2 has existing data

  // Move assign s1 to s2
  s2 = std::move(s1);

  // s2 should have s1's items (99 should be gone)
  EXPECT_EQ(*s2.pop(), 20);
  EXPECT_EQ(*s2.pop(), 10);
  EXPECT_EQ(s2.pop(), nullptr);
}

TEST(CGStack, MoveAssignmentSelfAssign) {
  CGStack<int> s;
  s.push(42);

  // Self-assignment (shouldn't crash)
  s = std::move(s);

  // Should still have the item
  EXPECT_EQ(*s.pop(), 42);
}
