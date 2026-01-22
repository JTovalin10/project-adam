#include <gtest/gtest.h>

#include <vector>

#include "move.h"

TEST(movetest, lvalue) {
  int x = 1;
  int y = slime::move(x);
  ASSERT_EQ(y, 1);
  ASSERT_EQ(y, 1);
}

TEST(movetest, rvalue) {
  int x = slime::move(1);
  ASSERT_EQ(x, 1);
  std::vector<int> p{1};
  std::vector<int> test = slime::move(p);
  ASSERT_EQ(test[0], 1);
}

TEST(movetest, rvalueReference) {
  const int x = 1;
  auto& y = slime::move(x);
  ASSERT_EQ(y, 1);
}

TEST(movetest, noncopyabletype) {
  struct test {
    bool moved_from{false};
    test() = default;
    test(const test&) = delete;
    test(test&&) { moved_from = true; }
  };
  test a;
  test b = slime::move(a);
  ASSERT_TRUE(b.moved_from);
}

TEST(movetest, array) {
  int arr[3] = {0, 1, 2};
  auto&& arr2 = slime::move(arr);
  ASSERT_EQ(arr2[0], 0);
  ASSERT_EQ(arr2[1], 1);
  ASSERT_EQ(arr2[2], 2);
}
