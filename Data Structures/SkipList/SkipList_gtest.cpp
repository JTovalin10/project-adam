#include "SkipList.h"
#include "gtest/gtest.h"

TEST(SkipListTest, empty_constructor) {
  SkipList<int, int> sl;
  ASSERT_EQ(sl.size(), 0);
  ASSERT_TRUE(sl.empty());
}

TEST(SkipListTest, parameter_constructor) {
  SkipList<int, int> sl(10, 0.5);
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

TEST(SkipListTest, copy_assignment_constructor) {
  SkipList<int, int> sl;
  sl.insert(1, 1);
  sl.insert(2, 2);

  SkipList<int, int> sl2;
  sl2.insert(3, 3);
  sl2.insert(4, 4);

  sl2 = sl;

  ASSERT_FALSE(sl2.empty());
  ASSERT_EQ(sl2.size(), 2);
  ASSERT_TRUE(sl2.contains(1));
  ASSERT_TRUE(sl2.contains(2));
  ASSERT_FALSE(sl2.contains(3));
  ASSERT_FALSE(sl2.contains(4));

  ASSERT_FALSE(sl.empty());
  ASSERT_TRUE(sl.contains(1));
  ASSERT_TRUE(sl.contains(2));
  ASSERT_EQ(sl.size(), 2);
}

TEST(SkipListTest, make_assignment_operator) {
  SkipList<int, int> sl;
  sl.insert(1, 1);
  sl.insert(2, 2);

  SkipList<int, int> sl2;
  sl2.insert(3, 3);
  sl2.insert(4, 4);

  sl2 = std::move(sl);

  ASSERT_FALSE(sl2.empty());
  ASSERT_EQ(sl2.size(), 2);
  ASSERT_TRUE(sl2.contains(1));
  ASSERT_TRUE(sl2.contains(2));
  ASSERT_FALSE(sl2.contains(3));
  ASSERT_FALSE(sl2.contains(4));

  ASSERT_TRUE(sl.empty());
  ASSERT_FALSE(sl.contains(1));
  ASSERT_FALSE(sl.contains(2));
  ASSERT_EQ(sl.size(), 0);
}

TEST(SkipListTest, insert) {
  SkipList<int, int> sl;

  sl.insert(1, 1);
  sl.insert(2, 2);
  sl.insert(3, 3);

  ASSERT_EQ(sl.find(1), 1);
  ASSERT_EQ(sl.find(2), 2);
  ASSERT_EQ(sl.find(3), 3);
  sl.insert(1, 10);
  sl.insert(2, 20);
  sl.insert(3, 30);
  ASSERT_EQ(sl.find(1), 10);
  ASSERT_EQ(sl.find(2), 20);
  ASSERT_EQ(sl.find(3), 30);
}