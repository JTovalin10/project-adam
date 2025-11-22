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

TEST(SkipListTest, move_assignment_operator) {
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

  // ensure move doesnt crash on insert or remove
  sl.insert(1, 1);
  ASSERT_EQ(sl.find(1), std::nullopt);
  ASSERT_FALSE(sl.remove(1));
}

TEST(SkipListTest, insert) {
  SkipList<int, int> sl;

  sl.insert(1, 1);
  sl.insert(2, 2);
  sl.insert(3, 3);
  sl.insert(-10000, 100);

  ASSERT_EQ(sl.find(1), 1);
  ASSERT_EQ(sl.find(2), 2);
  ASSERT_EQ(sl.find(3), 3);
  ASSERT_EQ(sl.find(-10000), 100);
  ASSERT_EQ(sl.size(), 4);
  sl.insert(1, 10);
  sl.insert(2, 20);
  sl.insert(3, 30);
  ASSERT_EQ(sl.find(1), 10);
  ASSERT_EQ(sl.find(2), 20);
  ASSERT_EQ(sl.find(3), 30);
  ASSERT_EQ(sl.size(), 4);

  ASSERT_EQ(sl.find(4), std::nullopt);
  ASSERT_FALSE(sl.find(5).has_value());
}

TEST(SkipListTest, remove) {
  SkipList<int, int> sl;
  ASSERT_FALSE(sl.remove(1));
  for (int i = 0; i < 3; i++) {
    sl.insert(i, i);
  }
  ASSERT_TRUE(sl.remove(2));
  ASSERT_EQ(sl.size(), 2);
  ASSERT_FALSE(sl.contains(2));

  ASSERT_TRUE(sl.remove(0));
  ASSERT_EQ(sl.size(), 1);
  ASSERT_FALSE(sl.contains(0));

  ASSERT_TRUE(sl.remove(1));
  ASSERT_EQ(sl.size(), 0);
  ASSERT_FALSE(sl.contains(0));

  // remove the middle
  for (int i = 0; i < 3; i++) {
    sl.insert(i, i);
  }
  ASSERT_TRUE(sl.remove(1));
  ASSERT_TRUE(sl.contains(0));
  ASSERT_TRUE(sl.contains(2));  // ensure it didnt break the structure
}

TEST(SkipListTest, find) {
  SkipList<int, int> sl;
  ASSERT_FALSE(sl.find(-1));
  for (int i = 0; i < 3; i++) {
    sl.insert(i, i);
  }
  ASSERT_FALSE(sl.find(-1));
  ASSERT_TRUE(sl.find(0));
  ASSERT_TRUE(sl.find(1));
  ASSERT_TRUE(sl.find(2));
  ASSERT_FALSE(sl.find(3));
}

TEST(SkipListTest, contains) {
  SkipList<int, int> sl;
  ASSERT_FALSE(sl.contains(-1));
  ASSERT_FALSE(sl.contains(0));

  sl.insert(1, 1);
  sl.insert(2, 2);
  sl.insert(3, 3);

  ASSERT_TRUE(sl.contains(1));
  ASSERT_TRUE(sl.contains(2));
  ASSERT_TRUE(sl.contains(3));

  ASSERT_FALSE(sl.contains(4));
}

TEST(SkipListTest, size) {
  SkipList<int, int> sl;
  ASSERT_EQ(sl.size(), 0);
  sl.insert(1, 1);

  ASSERT_EQ(sl.size(), 1);
  sl.insert(2, 2);

  ASSERT_EQ(sl.size(), 2);
  sl.insert(3, 3);
  ASSERT_EQ(sl.size(), 3);
}

TEST(SkipListTest, empty) {
  SkipList<int, int> sl;
  ASSERT_TRUE(sl.empty());
  sl.insert(1, 1);
  ASSERT_FALSE(sl.empty());
  SkipList<int, int> sl2 = std::move(sl);
  ASSERT_TRUE(sl.empty());
}

TEST(SkipListTest, clear) {
  SkipList<int, int> sl;
  for (int i = 0; i < 3; i++) {
    sl.insert(i, i);
  }
  sl.clear();
  ASSERT_EQ(sl.size(), 0);
  ASSERT_TRUE(sl.empty());
  sl.insert(1, 1);
  ASSERT_TRUE(sl.contains(1));

  // ensure no seg fault after move
  for (int i = 0; i < 3; i++) {
    sl.insert(i, i);
  }
  SkipList<int, int> sl2 = std::move(sl);
  sl.clear();
  // if we try to insert on a moved
}