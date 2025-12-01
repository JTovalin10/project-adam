/*
 * GOOGLE TEST (GTEST) INTRODUCTION
 * ==================================
 * Google Test is a C++ testing framework that helps you write unit tests.
 *
 * KEY CONCEPTS:
 * 1. TEST() macro: Defines a test case with a test suite name and test name
 *    Format: TEST(TestSuiteName, TestName) { ... }
 *
 * 2. ASSERT_ macros: Fail immediately and stop if condition is false
 *    Examples: ASSERT_EQ, ASSERT_NE, ASSERT_TRUE, ASSERT_FALSE
 *
 * 3. EXPECT_ macros: Continue testing even if condition is false
 *    Examples: EXPECT_EQ, EXPECT_NE, EXPECT_TRUE, EXPECT_FALSE
 *
 * 4. main() function: GTEST_MAIN_ creates a main that runs all tests
 *
 * HOW TO RUN:
 * 1. Compile: make test (or similar command)
 * 2. Run: ./Vector_test (or whatever your executable name is)
 *
 * READING THIS TEST:
 * - This tests the push_back() function on a Vector
 * - It verifies that elements are added correctly and size/capacity work
 */

#include "Vector.h"  // Our Vector class that we're testing
#include "gtest/gtest.h"  // Google Test framework - provides TEST, ASSERT, EXPECT macros

TEST(VectorTest, DefaultConstructorCreatesEmptyVector) {
  Vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, OperatorBrackerRead) {
  Vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_THROW(vec[-1], std::out_of_range);
  EXPECT_THROW(vec[3], std::out_of_range);
}

TEST(VectorTest, CopyConstructor) {
  // ARRANGE: Create vec1 and populate it using push_back()
  // =====================================================
  Vector<int> vec1;
  vec1.push_back(1);
  vec1.push_back(2);
  vec1.push_back(3);
  // Now vec1 contains: [1, 2, 3]

  // ACT: Use the copy constructor to create vec2
  // ============================================
  Vector<int> vec2(vec1);  // Copy constructor: creates new vector from vec1

  // ASSERT: Verify the copy has same size, capacity, and elements
  // ============================================================
  EXPECT_EQ(vec2.size(), vec1.size());          // Should be 3
  EXPECT_EQ(vec2.capacity(), vec1.capacity());  // Should be 10
  EXPECT_FALSE(vec2.empty());                   // Should not be empty

  // Verify elements were copied correctly
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
}

TEST(VectorTest, OperatorConstBrackerRead) {
  Vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  const Vector<int> const_vec = vec;
  EXPECT_EQ(const_vec[0], 1);
  EXPECT_EQ(const_vec[1], 2);
  EXPECT_EQ(const_vec[2], 3);
  EXPECT_THROW(const_vec[-1], std::out_of_range);
  EXPECT_THROW(const_vec[3], std::out_of_range);
}

TEST(VectorTest, AssignmentOperator) {
  // ARRANGE: Create two vectors with different data
  // ===============================================
  Vector<int> vec1;
  vec1.push_back(1);
  vec1.push_back(2);
  vec1.push_back(3);
  vec1.push_back(4);
  vec1.push_back(5);
  // vec1 contains: [1, 2, 3, 4, 5]

  Vector<int> vec2;
  vec2.push_back(10);
  vec2.push_back(11);
  vec2.push_back(12);
  vec2.push_back(13);
  vec2.push_back(14);
  vec2.push_back(15);
  vec2.push_back(16);
  vec2.push_back(17);
  vec2.push_back(18);
  vec2.push_back(19);
  vec2.push_back(20);
  // vec2 contains: [10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]

  // ACT: Test the assignment operator
  // =================================
  vec1 = vec2;  // Copy vec2's data into vec1 using operator=

  // ASSERT: Verify vec1 now contains vec2's data
  // =============================================
  EXPECT_EQ(vec1.size(), vec2.size());  // Should both be 11

  // Verify all elements were copied
  EXPECT_EQ(vec1[0], 10);
  EXPECT_EQ(vec1[1], 11);
  EXPECT_EQ(vec1[2], 12);
  EXPECT_EQ(vec1[3], 13);
  EXPECT_EQ(vec1[4], 14);
  EXPECT_EQ(vec1[5], 15);
  EXPECT_EQ(vec1[6], 16);
  EXPECT_EQ(vec1[7], 17);
  EXPECT_EQ(vec1[8], 18);
  EXPECT_EQ(vec1[9], 19);
  EXPECT_EQ(vec1[10], 20);
}

TEST(VectorTest, AtFunction) {
  Vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(1), 2);
  EXPECT_EQ(vec.at(2), 3);
  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(3), std::out_of_range);
}

TEST(VectorTest, ConstAtFunction) {
  Vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  const Vector<int> const_vec = vec;
  EXPECT_EQ(const_vec.at(0), 1);
  EXPECT_EQ(const_vec.at(1), 2);
  EXPECT_EQ(const_vec.at(2), 3);
  EXPECT_THROW(const_vec.at(-1), std::out_of_range);
  EXPECT_THROW(const_vec.at(3), std::out_of_range);
}

TEST(VectorTest, SizeFunction) {
  Vector<int> vec;
  vec.push_back(1);
  EXPECT_EQ(vec.size(), 1);
  vec.push_back(2);
  EXPECT_EQ(vec.size(), 2);
  vec.push_back(3);
  EXPECT_EQ(vec.size(), 3);
}

TEST(VectorTest, CapacityFunction) {
  Vector<int> vec;
  EXPECT_EQ(vec.capacity(), 10);
  for (int i = 0; i <= 10; i++) {
    vec.push_back(i);
  }
  EXPECT_EQ(vec.capacity(), 20);
}

TEST(VectorTest, EmptyFunction) {
  Vector<int> vec;
  EXPECT_TRUE(vec.empty());
  vec.push_back(1);
  EXPECT_FALSE(vec.empty());
}

TEST(VectorTest, PushBackFunction) {
  Vector<int> vec;
  for (int i = 0; i < 10; i++) {
    vec.push_back(i);
    EXPECT_EQ(vec.size(), i + 1);
  }
  EXPECT_EQ(vec[0], 0);
  EXPECT_EQ(vec[1], 1);
  EXPECT_EQ(vec[2], 2);
  EXPECT_EQ(vec[3], 3);
  EXPECT_EQ(vec[4], 4);
  EXPECT_EQ(vec[5], 5);
  EXPECT_EQ(vec[6], 6);
  EXPECT_EQ(vec[7], 7);
  EXPECT_EQ(vec[8], 8);
  EXPECT_EQ(vec[9], 9);

  EXPECT_EQ(vec.size(), vec.capacity());
  vec.push_back(10);
  EXPECT_EQ(vec.capacity(), 20);
  EXPECT_EQ(vec.size(), 11);
  EXPECT_EQ(vec[10], 10);
}

TEST(VectorTest, PopBackFunction) {
  Vector<int> vec;

  EXPECT_THROW(vec.pop_back(), std::out_of_range);

  for (int i = 0; i < 3; i++) {
    vec.push_back(i);
  }
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 0);
  EXPECT_EQ(vec[1], 1);
  EXPECT_EQ(vec[2], 2);
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], 0);
  EXPECT_EQ(vec[1], 1);
  vec.pop_back();
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], 0);

  // Pop the last element - now size should be 0
  vec.pop_back();
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());  // Vector should be empty

  // Trying to pop_back on empty vector should throw
  EXPECT_THROW(vec.pop_back(), std::out_of_range);
}

TEST(VectorTest, InsertFunction) {
  // TEST: Insert into empty vector should work (index = 0)
  Vector<int> vec;
  EXPECT_THROW(vec.insert(1, 1), std::out_of_range);
  vec.insert(1, 0);
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], 1);

  // TEST: Insert in the middle
  vec.push_back(2);
  vec.push_back(3);
  // Now vec = [1, 2, 3]
  EXPECT_EQ(vec.size(), 3);

  vec.insert(10, 1);  // Insert at index 1
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 10);
  EXPECT_EQ(vec[2], 2);
  EXPECT_EQ(vec[3], 3);

  // TEST: Insert at the end
  vec.insert(99, vec.size());  // Insert at index 4 (the end)
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[4], 99);

  // TEST: Insert at invalid index
  EXPECT_THROW(vec.insert(12, vec.size() + 1), std::out_of_range);
}

TEST(VectorTest, setFunction) {
  Vector<int> vec;
  EXPECT_THROW(vec.set(1, 1), std::out_of_range);
  for (int i = 0; i < 3; i++) {
    vec.push_back(i);
  }
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 0);
  EXPECT_EQ(vec[1], 1);
  EXPECT_EQ(vec[2], 2);
  vec.set(10, 1);
  EXPECT_EQ(vec[1], 10);
  EXPECT_EQ(vec[2], 2);
}

TEST(VectorTest, RemoveFunction) {
  Vector<int> vec;
  EXPECT_THROW(vec.remove(0), std::out_of_range);
  for (int i = 0; i < 3; i++) {
    vec.push_back(i);
  }
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 0);
  EXPECT_EQ(vec[1], 1);
  EXPECT_EQ(vec[2], 2);
  vec.remove(1);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], 0);
  EXPECT_EQ(vec[1], 2);
  vec.remove(0);
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], 2);
  vec.remove(0);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
  EXPECT_THROW(vec.remove(0), std::out_of_range);
}

TEST(VectorTest, IteratorBegin) {
  // ARRANGE: Create a vector with data
  Vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);

  // ACT: Test basic iterator functionality
  Vector<int>::iterator it = vec.begin();

  // ASSERT: Verify dereferencing and incrementing works
  EXPECT_EQ(*it, 10);  // First element
  ++it;
  EXPECT_EQ(*it, 20);  // Second element
  ++it;
  EXPECT_EQ(*it, 30);  // Third element
  ++it;

  // After incrementing past the last element, iterator equals end()
  EXPECT_EQ(it, vec.end());
}

TEST(VectorTest, IteratorModification) {
  // ARRANGE: Create vector with data
  Vector<int> vec;
  vec.push_back(100);
  vec.push_back(200);
  vec.push_back(300);

  // ACT: Modify element through iterator
  Vector<int>::iterator it = vec.begin();
  *it = 999;  // Modify through iterator

  // ASSERT: Original vector is changed
  EXPECT_EQ(vec[0], 999);
  EXPECT_EQ(*it, 999);
}

TEST(VectorTest, IteratorEmptyVector) {
  // ARRANGE: Empty vector
  Vector<int> vec;

  // ASSERT: begin() should equal end() for empty vector
  EXPECT_EQ(vec.begin(), vec.end());
}

TEST(VectorTest, IteratorEndFunction) {
  // ARRANGE: Create a vector with data
  Vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);

  // ACT: Get the end iterator
  Vector<int>::iterator end_it = vec.end();

  // ASSERT: end() points one past the last element
  // We can't dereference end() safely, but we can check:
  // 1. end() is NOT equal to begin() for non-empty vector
  EXPECT_NE(vec.begin(), end_it);

  // 2. Decrementing from end() should give us the last element
  --end_it;
  EXPECT_EQ(*end_it, 30);  // Last element (index 2)

  // 3. Decrement once more -> second element
  --end_it;
  EXPECT_EQ(*end_it, 20);  // Second element (index 1)

  // 4. Decrement once more -> first element
  --end_it;
  EXPECT_EQ(*end_it, 10);  // First element (index 0)

  // 5. end_it should now equal begin() (we can't decrement further)
  EXPECT_EQ(end_it, vec.begin());
}
