#include <gtest/gtest.h>

#include "RedBlackTree.h"

// Basic construction and destruction
TEST(RedBlackTreeTest, DefaultConstruction) {
  RedBlackTree<int, std::string> tree;
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(), 0);
}

// Basic insertion
TEST(RedBlackTreeTest, SingleInsertion) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");
  EXPECT_FALSE(tree.empty());
  EXPECT_EQ(tree.size(), 1);
  EXPECT_TRUE(tree.contains(10));
}

TEST(RedBlackTreeTest, MultipleInsertions) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(20, "twenty");
  tree.insert(5, "five");

  EXPECT_EQ(tree.size(), 3);
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(5));
}

TEST(RedBlackTreeTest, DuplicateKeyUpdate) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(10, "TEN");

  EXPECT_EQ(tree.size(), 1);
  EXPECT_EQ(*tree.find(10), "TEN");
}

// Find and contains
TEST(RedBlackTreeTest, FindExistingKey) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(20, "twenty");

  std::string* value = tree.find(10);
  ASSERT_NE(value, nullptr);
  EXPECT_EQ(*value, "ten");
}

TEST(RedBlackTreeTest, FindNonExistingKey) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");

  std::string* value = tree.find(99);
  EXPECT_EQ(value, nullptr);
}

TEST(RedBlackTreeTest, ContainsKey) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");

  EXPECT_TRUE(tree.contains(10));
  EXPECT_FALSE(tree.contains(99));
}

// Removal tests
TEST(RedBlackTreeTest, RemoveSingleElement) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");

  EXPECT_TRUE(tree.remove(10));
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(), 0);
  EXPECT_FALSE(tree.contains(10));
}

TEST(RedBlackTreeTest, RemoveNonExistingKey) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");

  EXPECT_FALSE(tree.remove(99));
  EXPECT_EQ(tree.size(), 1);
}

TEST(RedBlackTreeTest, RemoveLeafNode) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(5, "five");
  tree.insert(15, "fifteen");

  EXPECT_TRUE(tree.remove(5));
  EXPECT_EQ(tree.size(), 2);
  EXPECT_FALSE(tree.contains(5));
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(15));
}

TEST(RedBlackTreeTest, RemoveNodeWithOneChild) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(5, "five");
  tree.insert(3, "three");

  EXPECT_TRUE(tree.remove(5));
  EXPECT_EQ(tree.size(), 2);
  EXPECT_FALSE(tree.contains(5));
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(3));
}

TEST(RedBlackTreeTest, RemoveNodeWithTwoChildren) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(5, "five");
  tree.insert(15, "fifteen");
  tree.insert(12, "twelve");
  tree.insert(18, "eighteen");

  EXPECT_TRUE(tree.remove(15));
  EXPECT_EQ(tree.size(), 4);
  EXPECT_FALSE(tree.contains(15));
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(12));
  EXPECT_TRUE(tree.contains(18));
}

TEST(RedBlackTreeTest, RemoveRoot) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(5, "five");
  tree.insert(15, "fifteen");

  EXPECT_TRUE(tree.remove(10));
  EXPECT_EQ(tree.size(), 2);
  EXPECT_FALSE(tree.contains(10));
  EXPECT_TRUE(tree.contains(5));
  EXPECT_TRUE(tree.contains(15));
}

// Clear
TEST(RedBlackTreeTest, Clear) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(20, "twenty");
  tree.insert(5, "five");

  tree.clear();
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(), 0);
}

// Copy constructor
TEST(RedBlackTreeTest, CopyConstructor) {
  RedBlackTree<int, std::string> tree1;
  tree1.insert(10, "ten");
  tree1.insert(20, "twenty");
  tree1.insert(5, "five");

  RedBlackTree<int, std::string> tree2(tree1);

  EXPECT_EQ(tree2.size(), 3);
  EXPECT_TRUE(tree2.contains(10));
  EXPECT_TRUE(tree2.contains(20));
  EXPECT_TRUE(tree2.contains(5));

  // Modify tree2, tree1 should be unchanged
  tree2.insert(30, "thirty");
  EXPECT_EQ(tree1.size(), 3);
  EXPECT_EQ(tree2.size(), 4);
}

// Move constructor
TEST(RedBlackTreeTest, MoveConstructor) {
  RedBlackTree<int, std::string> tree1;
  tree1.insert(10, "ten");
  tree1.insert(20, "twenty");

  RedBlackTree<int, std::string> tree2(std::move(tree1));

  EXPECT_EQ(tree2.size(), 2);
  EXPECT_TRUE(tree2.contains(10));
  EXPECT_TRUE(tree2.contains(20));

  EXPECT_TRUE(tree1.empty());
}

// Copy assignment
TEST(RedBlackTreeTest, CopyAssignment) {
  RedBlackTree<int, std::string> tree1;
  tree1.insert(10, "ten");
  tree1.insert(20, "twenty");

  RedBlackTree<int, std::string> tree2;
  tree2.insert(99, "ninety-nine");

  tree2 = tree1;

  EXPECT_EQ(tree2.size(), 2);
  EXPECT_TRUE(tree2.contains(10));
  EXPECT_TRUE(tree2.contains(20));
  EXPECT_FALSE(tree2.contains(99));
}

// Move assignment
TEST(RedBlackTreeTest, MoveAssignment) {
  RedBlackTree<int, std::string> tree1;
  tree1.insert(10, "ten");
  tree1.insert(20, "twenty");

  RedBlackTree<int, std::string> tree2;
  tree2 = std::move(tree1);

  EXPECT_EQ(tree2.size(), 2);
  EXPECT_TRUE(tree2.contains(10));
  EXPECT_TRUE(tree1.empty());
}

// Self-assignment
TEST(RedBlackTreeTest, SelfCopyAssignment) {
  RedBlackTree<int, std::string> tree;
  tree.insert(10, "ten");

  tree = tree;

  EXPECT_EQ(tree.size(), 1);
  EXPECT_TRUE(tree.contains(10));
}

// Stress test - sequential insertion
TEST(RedBlackTreeTest, SequentialInsertions) {
  RedBlackTree<int, int> tree;

  for (int i = 0; i < 100; i++) {
    tree.insert(i, i * 10);
  }

  EXPECT_EQ(tree.size(), 100);

  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(tree.contains(i));
    EXPECT_EQ(*tree.find(i), i * 10);
  }
}

// Stress test - random-ish insertions and deletions
TEST(RedBlackTreeTest, MixedOperations) {
  RedBlackTree<int, int> tree;

  // Insert 1-50
  for (int i = 1; i <= 50; i++) {
    tree.insert(i, i);
  }

  // Remove every other
  for (int i = 2; i <= 50; i += 2) {
    EXPECT_TRUE(tree.remove(i));
  }

  EXPECT_EQ(tree.size(), 25);

  // Check remaining
  for (int i = 1; i <= 50; i++) {
    if (i % 2 == 1) {
      EXPECT_TRUE(tree.contains(i));
    } else {
      EXPECT_FALSE(tree.contains(i));
    }
  }
}

// Empty tree operations
TEST(RedBlackTreeTest, RemoveFromEmptyTree) {
  RedBlackTree<int, std::string> tree;
  EXPECT_FALSE(tree.remove(10));
}

TEST(RedBlackTreeTest, FindInEmptyTree) {
  RedBlackTree<int, std::string> tree;
  EXPECT_EQ(tree.find(10), nullptr);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}