#include "Hash_Table.h"
#include "gtest/gtest.h"

TEST(HashTableTest, default_constructor) {
  HashTable<int, int> ht;
  ASSERT_EQ(ht.size(), 0);
  ASSERT_TRUE(ht.empty());
  ASSERT_EQ(ht.load_factor(), 0.0);
  ASSERT_EQ(ht.max_load_factor(), 0.75);
}

TEST(HashTableTest, copy_constructor) {
  HashTable<int, int> ht;
  for (int i = 0; i < 3; i++) {
    ht.insert(i, i);
  }
  ASSERT_FALSE(ht.empty());
  ASSERT_EQ(ht.size(), 3);
  ASSERT_EQ(ht.at(0), 0);
  ASSERT_EQ(ht.at(1), 1);
  ASSERT_EQ(ht.at(2), 2);

  HashTable<int, int> other = ht;
  ASSERT_FALSE(other.empty());
  ASSERT_EQ(other.size(), 3);
  ASSERT_EQ(other.at(0), 0);
  ASSERT_EQ(other.at(1), 1);
  ASSERT_EQ(other.at(2), 2);
}

TEST(HashTableTest, move_copy_constructor) {
  HashTable<int, int> ht;
  for (int i = 0; i < 3; i++) {
    ht.insert(i, i);
  }
  ASSERT_FALSE(ht.empty());
  ASSERT_EQ(ht.size(), 3);
  ASSERT_EQ(ht.at(0), 0);
  ASSERT_EQ(ht.at(1), 1);
  ASSERT_EQ(ht.at(2), 2);

  HashTable<int, int> other = std::move(ht);
  ASSERT_FALSE(other.empty());
  ASSERT_EQ(other.size(), 3);
  ASSERT_EQ(other.at(0), 0);
  ASSERT_EQ(other.at(1), 1);
  ASSERT_EQ(other.at(2), 2);

  ASSERT_TRUE(ht.empty());
  ASSERT_EQ(ht.size(), 0);
}

TEST(HashTableTest, copy_assignment_operator) {
  HashTable<int, int> ht;
  for (int i = 0; i < 3; i++) {
    ht.insert(i, i);
  }

  HashTable<int, int> ht2;
  for (int i = 3; i < 6; i++) {
    ht.insert(i, i);
  }
  ht2 = ht;
  ASSERT_EQ(ht2[0], 0);
  ASSERT_EQ(ht2[1], 1);
  ASSERT_EQ(ht2[2], 2);
}

TEST(HashTableTest, move_assignment_operator) {
  HashTable<int, int> ht;
  for (int i = 0; i < 3; i++) {
    ht.insert(i, i);
  }

  HashTable<int, int> ht2;
  for (int i = 3; i < 6; i++) {
    ht.insert(i, i);
  }
  ht2 = std::move(ht);
  ASSERT_EQ(ht2[0], 0);
  ASSERT_EQ(ht2[1], 1);
  ASSERT_EQ(ht2[2], 2);

  ASSERT_TRUE(ht.empty());
  ASSERT_EQ(ht.size(), 0);
}

TEST(HashTableTest, empty) {
  HashTable<int, int> ht;
  ASSERT_TRUE(ht.empty());
  ht.insert(1, 1);
  ASSERT_FALSE(ht.empty());
}

TEST(HashTableTest, size) {
  HashTable<int, int> ht;
  ASSERT_EQ(ht.size(), 0);
  ht.insert(0, 0);
  ASSERT_EQ(ht.size(), 1);
  ht.insert(1, 1);
  ASSERT_EQ(ht.size(), 2);
}

TEST(HashTableTest, insert) {
  HashTable<int, int> ht;
  for (int i = 0; i < 3; i++) {
    ht.insert(i, i);
  }
  ASSERT_FALSE(ht.empty());
  ASSERT_EQ(ht.size(), 3);
  ASSERT_EQ(ht[0], 0);
  ASSERT_EQ(ht[1], 1);
  ASSERT_EQ(ht[2], 2);
  ht.insert(0, 100);
  ASSERT_EQ(ht[0], 0);
}

TEST(HashTableTest, insert_or_assign) {
  HashTable<int, int> ht;
  for (int i = 0; i < 3; i++) {
    ht.insert_or_assign(i, i);
  }
  ASSERT_FALSE(ht.empty());
  ASSERT_EQ(ht.size(), 3);
  ASSERT_EQ(ht[0], 0);
  ASSERT_EQ(ht[1], 1);
  ASSERT_EQ(ht[2], 2);
  ht.insert_or_assign(0, 100);
  ASSERT_EQ(ht[0], 100);
}





