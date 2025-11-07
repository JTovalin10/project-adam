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
