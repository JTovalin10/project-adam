#include "SkipList.h"
#include "gtest/gtest.h"

TEST(SkipListTest, empty_constructor) {
  SkipList<int, int> sl;
  ASSERT_EQ(sl.size(), 0);
  ASSERT_TRUE(sl.empty());
}

TEST(SkipListTest, parameter_constructor) {
  SkipList<int, int> sl(10, 10);
  ASSERT_EQ(sl.size(), 0);
  ASSERT_TRUE(sl.empty());
}

TEST(SkipListTest, copy_constructor) {
  SkipList<int, int> sl;
  sl.insert(1, 1);
  sl.insert(2, 2);

  SkipList<int, int> sl2 = sl;
  ASSERT_FALSE(sl2.empty());
  ASSERT_TRUE(sl2.contains(1));
  ASSERT_TRUE(sl2.contains(2));
  ASSERT_EQ(sl2.size(), 2);

  ASSERT_FALSE(sl.empty());
  ASSERT_TRUE(sl.contains(1));
  ASSERT_TRUE(sl.contains(2));
  ASSERT_EQ(sl.size(), 2);
}

TEST(SkipListTest, move_constructor) {
  SkipList<int, int> sl;
  sl.insert(1, 1);
  sl.insert(2, 2);

  SkipList<int, int> sl2 = std::move(sl);
  ASSERT_FALSE(sl2.empty());
  ASSERT_TRUE(sl2.contains(1));
  ASSERT_TRUE(sl2.contains(2));
  ASSERT_EQ(sl2.size(), 2);

  ASSERT_TRUE(sl.empty());
  ASSERT_FALSE(sl.contains(1));
  ASSERT_FALSE(sl.contains(2));
  ASSERT_EQ(sl.size(), 0);
}