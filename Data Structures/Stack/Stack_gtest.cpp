#include <utility>

#include "Stack.h"
#include "gtest/gtest.h"

TEST(stack_test, default_constructor) { Stack<int> stack; }

TEST(stack_test, copy_constructor) {
  Stack<int> s1;
  s1.push(1);

  Stack<int> s2 = s1;
  ASSERT_EQ(s2.top(), 1);
}

TEST(stack_test, move_constructor) {
  Stack<int> s1;
  s1.push(1);

  Stack<int> s2 = std::move(s1);
  ASSERT_EQ(s2.top(), 1);

  ASSERT_EQ(s1.size(), 0);
  ASSERT_THROW(s1.top(), std::out_of_range);
}

TEST(stack_test, copy_assignment_constructor) {
  Stack<int> s1;
  s1.push(1);

  Stack<int> s2;
  s2.push(2);
  s2 = s1;
  ASSERT_EQ(s2.top(), 1);
  s2.pop();
  ASSERT_THROW(s2.pop(), std::out_of_range);
}

TEST(stack_test, move_assignment_constructor) {
  Stack<int> s1;
  s1.push(0);
  s1.push(1);
  s1.push(2);

  Stack<int> s2;
  s2.push(10);
  s2.push(20);
  s2.push(30);

  s2 = std::move(s1);
  ASSERT_EQ(s2.top(), 2);
  s2.pop();
  ASSERT_EQ(s2.top(), 1);
  s2.pop();
  ASSERT_EQ(s2.top(), 0);
}

TEST(stack_test, pop) {
  Stack<int> s;
  s.push(0);
  s.push(1);
  s.push(2);

  ASSERT_EQ(s.top(), 2);
  s.pop();
  ASSERT_EQ(s.top(), 1);
  s.pop();
  ASSERT_EQ(s.top(), 0);
}

TEST(stack_test, const_top) {
  Stack<int> s;
  s.push(0);
  s.push(1);
  s.push(2);

  const Stack<int> s2 = s;
  ASSERT_EQ(s2.top(), 2);
}

TEST(stack_test, empty) {
  Stack<int> s;
  ASSERT_TRUE(s.empty());
  s.push(1);
  ASSERT_FALSE(s.empty());
  s.pop();
  ASSERT_TRUE(s.empty());
}

TEST(stack_test, size) {
  Stack<int> s;
  ASSERT_EQ(s.size(), 0);
  s.push(1);
  ASSERT_EQ(s.size(), 1);
  s.pop();
  ASSERT_EQ(s.size(), 0);
}
