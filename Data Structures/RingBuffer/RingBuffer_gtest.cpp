#include "RingBuffer.h"
#include "gtest/gtest.h"

TEST(RingBufferTest, empty_constructor) {
  RingBuffer<int> rb;
  ASSERT_EQ(rb.size(), 0);
  ASSERT_EQ(rb.capacity(), 10);
  ASSERT_TRUE(rb.empty());
  ASSERT_FALSE(rb.full());
}

TEST(RingBufferTest, explicit_constructor) { 
  RingBuffer<int> rb(100);
  ASSERT_EQ(rb.size(), 0);
  ASSERT_EQ(rb.capacity(), 100);
  ASSERT_TRUE(rb.empty());
  ASSERT_FALSE(rb.full());
}

TEST(RingBufferTest, copy_constructor) {
  RingBuffer<int> rb(100);
  RingBuffer<int> rb2 = rb;

  ASSERT_EQ(rb2.capacity(), 100);
  ASSERT_EQ(rb2.size(), 0);
  ASSERT_TRUE(rb2.empty());
  ASSERT_FALSE(rb2.full());

  RingBuffer<int> test(100);
  test.push(1);
  RingBuffer<int>test2 = test;

  ASSERT_EQ(test2.capacity(), 100);
  ASSERT_EQ(test2.size(), 1);
  ASSERT_FALSE(test2.empty());
  ASSERT_FALSE(test2.full());
  ASSERT_EQ(test2.front().value(), 1);
  ASSERT_EQ(test2.back().value(), 1);
}

TEST(RingBufferTest, move_constructor) {
  RingBuffer<int> rb(100);
  RingBuffer<int> rb2 = std::move(rb);

  ASSERT_EQ(rb2.capacity(), 100);
  ASSERT_EQ(rb2.size(), 0);
  ASSERT_TRUE(rb2.empty());
  ASSERT_FALSE(rb2.full());

  ASSERT_EQ(rb.capacity(), 0);
  ASSERT_EQ(rb.size(), 0);
  ASSERT_TRUE(rb2.empty());

  RingBuffer<int> test(100);
  test.push(1);
  RingBuffer<int>test2 = std::move(test);

  ASSERT_EQ(test2.capacity(), 100);
  ASSERT_EQ(test2.size(), 1);
  ASSERT_FALSE(test2.empty());
  ASSERT_FALSE(test2.full());
  ASSERT_EQ(test2.front().value(), 1);
  ASSERT_EQ(test2.back().value(), 1);

  ASSERT_EQ(test.capacity(), 0);
  ASSERT_EQ(test.size(), 0);
  ASSERT_TRUE(test.empty());
  ASSERT_EQ(test.front(), std::nullopt);
  ASSERT_EQ(test.back(), std::nullopt);
  ASSERT_EQ(test.pop(), std::nullopt);
  test.push(1);
  ASSERT_TRUE(test.empty());
}

TEST(RingBufferTest, copy_assignment_operator) {
  RingBuffer<int> rb(100);
  RingBuffer<int> rb2;
  rb2.push(100);
  rb2 = rb;

  ASSERT_EQ(rb2.capacity(), 100);
  ASSERT_EQ(rb2.size(), 0);
  ASSERT_TRUE(rb2.empty());
  ASSERT_FALSE(rb2.full());

  RingBuffer<int> test(100);
  test.push(1);
  RingBuffer<int>test2;
  test2.push(-100);
  test2 = test;

  ASSERT_EQ(test2.capacity(), 100);
  ASSERT_EQ(test2.size(), 1);
  ASSERT_FALSE(test2.empty());
  ASSERT_FALSE(test2.full());
  ASSERT_EQ(test2.front().value(), 1);
  ASSERT_EQ(test2.back().value(), 1);
}

TEST(RingBufferTest, move_assignment_operator) {
  RingBuffer<int> rb(100);
  RingBuffer<int> rb2;
  rb2 = std::move(rb);

  ASSERT_EQ(rb2.capacity(), 100);
  ASSERT_EQ(rb2.size(), 0);
  ASSERT_TRUE(rb2.empty());
  ASSERT_FALSE(rb2.full());

  ASSERT_EQ(rb.capacity(), 0);
  ASSERT_EQ(rb.size(), 0);
  ASSERT_TRUE(rb2.empty());
  ASSERT_EQ(rb.front(), std::nullopt);
  ASSERT_EQ(rb.back(), std::nullopt);
  rb.push(100);
  ASSERT_TRUE(rb.empty());

  RingBuffer<int> test(100);
  test.push(1);
  RingBuffer<int>test2;
  test2 = std::move(test);

  ASSERT_EQ(test2.capacity(), 100);
  ASSERT_EQ(test2.size(), 1);
  ASSERT_FALSE(test2.empty());
  ASSERT_FALSE(test2.full());
  ASSERT_EQ(test2.front().value(), 1);
  ASSERT_EQ(test2.back().value(), 1);

  ASSERT_EQ(test.capacity(), 0);
  ASSERT_EQ(test.size(), 0);
  ASSERT_TRUE(test.empty());
  ASSERT_EQ(test.front(), std::nullopt);
  ASSERT_EQ(test.back(), std::nullopt);
  ASSERT_EQ(test.pop(), std::nullopt);
  test.push(1);
  ASSERT_TRUE(test.empty());
}

TEST(RingBufferTest, push) {
  RingBuffer<int> r;
  ASSERT_EQ(r.size(), 0);
  r.push(0);
  ASSERT_EQ(r.size(), 1);
  ASSERT_EQ(r.front().value(), 0);
  ASSERT_EQ(r.back().value(), 0);

  r.push(1);
  ASSERT_EQ(r.size(), 2);
  ASSERT_EQ(r.front().value(), 0);
  ASSERT_EQ(r.back().value(), 1);
}

TEST(RingBufferTest, push_overwrite) {
  RingBuffer<int> r(3);
  r.push(1);
  r.push(2);
  r.push(3);
  ASSERT_TRUE(r.full());
  ASSERT_EQ(r.size(), 3);

  r.push(4);
  ASSERT_TRUE(r.full());
  ASSERT_EQ(r.size(), 3);

  // front() should now be 2 as 1 was overwritten
  ASSERT_EQ(r.front().value(), 2);
  ASSERT_EQ(r.back().value(), 4);

  ASSERT_EQ(r.pop().value(), 2);
  ASSERT_EQ(r.pop().value(), 3);
  ASSERT_EQ(r.pop().value(), 4);
  ASSERT_TRUE(r.empty());
}

TEST(RingBufferTest, Multiple_overwrites) {
  RingBuffer<int> rb(3);

  rb.push(1);
  rb.push(2);
  rb.push(3);
  
  rb.push(4);
  rb.push(5);
  rb.push(6);

  ASSERT_EQ(rb.pop().value(), 4);
  ASSERT_EQ(rb.pop().value(), 5);
  ASSERT_EQ(rb.pop().value(), 6);
}

TEST(RingBufferTest, pop) {
  RingBuffer<int> r;
  r.push(0);
  ASSERT_EQ(r.front().value(), 0);
  ASSERT_EQ(r.back().value(), 0);
  r.push(1);
  ASSERT_EQ(r.front().value(), 0);
  ASSERT_EQ(r.back().value(), 1);
  ASSERT_EQ(r.size(), 2);

  ASSERT_EQ(r.pop().value(), 0);
  ASSERT_EQ(r.front().value(), 1);
  ASSERT_EQ(r.size(), 1);

  ASSERT_EQ(r.pop().value(), 1);
  ASSERT_EQ(r.front(), std::nullopt);
  ASSERT_EQ(r.pop(), std::nullopt);
  ASSERT_EQ(r.size(), 0);
}

TEST(RingBufferTest, front) {
  RingBuffer<int> r;
  ASSERT_EQ(r.front(), std::nullopt);
  for (int i = 0; i < 3; i++) {
    r.push(i);
  }
  ASSERT_EQ(r.front().value(), 0);
  r.pop();
  ASSERT_EQ(r.front().value(), 1);
  r.pop();
  ASSERT_EQ(r.front().value(), 2);
  r.pop();
  ASSERT_EQ(r.front(), std::nullopt);
}

TEST(RingBufferTest, back) {
  RingBuffer<int> r;
  ASSERT_EQ(r.back(), std::nullopt);
  r.push(0);

  ASSERT_EQ(r.back().value(), 0);
  r.push(1);
  ASSERT_EQ(r.back().value(), 1);
  r.push(2);
  ASSERT_EQ(r.back().value(), 2);
  for (int i = 0; i < 3; i++) {
    r.pop();
  }
  ASSERT_EQ(r.back(), std::nullopt);
}

TEST(RingBufferTest, empty) {
  RingBuffer<int> r;
  ASSERT_TRUE(r.empty());
  r.push(1);
  ASSERT_FALSE(r.empty());
  r.pop();
  ASSERT_TRUE(r.empty());
}

TEST(RingBufferTest, full) {
  RingBuffer<int> r; // capqacity 10
  ASSERT_FALSE(r.full());
  for (int i = 0; i < 10; i++) {
    r.push(i);
  }
  ASSERT_EQ(r.size(), 10);
  ASSERT_TRUE(r.full());
  r.pop();
  ASSERT_FALSE(r.full());
}

TEST(RingBufferTest, size) {
  RingBuffer<int> r;
  ASSERT_EQ(r.size(), 0);
  r.push(0);
  ASSERT_EQ(r.size(), 1);
  for (int i = 0; i < 3; i++) {
    r.push(i);
  }
  ASSERT_EQ(r.size(), 4);
}

TEST(RingBufferTest, capacity) {
  RingBuffer<int> r;
  ASSERT_EQ(r.capacity(), 10);

  RingBuffer<int> r2(100);
  ASSERT_EQ(r2.capacity(), 100);

  RingBuffer<int> r3(1000);
  ASSERT_EQ(r3.capacity(), 1000);
}

TEST(RingBufferTest, clear) {
  RingBuffer<int> r(100);
  for (int i = 0; i < 100; i++) {
    r.push(i);
  }
  ASSERT_EQ(r.size(), 100);
  r.clear();
  ASSERT_EQ(r.size(), 0);

  ASSERT_EQ(r.front(), std::nullopt);
  ASSERT_EQ(r.back(), std::nullopt);
}

