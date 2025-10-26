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

#include "gtest/gtest.h"  // Google Test framework - provides TEST, ASSERT, EXPECT macros
#include "Vector.h"        // Our Vector class that we're testing

TEST(VectorTest, DefaultConstructorCreatesEmptyVector) {
    Vector<int> vec;

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 10);
    EXPECT_TRUE(vec.empty());
}

// TEST() macro creates a new test case
// First parameter: Test Suite name (like a category)
// Second parameter: Test name (describes what this specific test does)
TEST(VectorTest, PushBackAddsElement) {
    // ARRANGE (Setup): Create objects and variables needed for the test
    // =================================================================
    
    // Create an empty Vector of integers
    // This tests our default constructor: Vector()
    Vector<int> vec;
    
    // ACT (Execute): Run the function we're testing
    // ==============================================
    
    // Test push_back: adds element to end of vector
    // This is the function we're verifying works correctly
    vec.push_back(42);    // Add first element
    vec.push_back(100);   // Add second element
    vec.push_back(7);     // Add third element
    
    // ASSERT (Verify): Check that the results are correct
    // ====================================================
    
    // EXPECT_EQ: Checks if two values are equal
    // If they're NOT equal, test fails and prints error message
    // Expected value goes first, actual value goes second
    EXPECT_EQ(vec.size(), 3);  // We added 3 elements, so size should be 3
    
    // Verify each element was added to the correct position
    // array_[0] should contain 42
    EXPECT_EQ(vec[0], 42);     // First element at index 0
    EXPECT_EQ(vec[1], 100);    // Second element at index 1
    EXPECT_EQ(vec[2], 7);      // Third element at index 2
    
    // empty() should return false since we have elements
    EXPECT_FALSE(vec.empty()); // EXPECT_FALSE checks the value is false
    
    // Capacity should be at least 10 (initial_capacity from Vector.h)
    // Since we added 3 elements (which is < 10), capacity should still be 10
    EXPECT_GE(vec.capacity(), 10); // EXPECT_GE = "greater than or equal"
    
    // If all ASSERT/EXPECT checks pass, the test passes! ✅
}

// When you link with -lgtest_main (in the makefile), Google Test automatically
// provides the main() function for you. You don't need to write one yourself!
// This is the simplest way to use Google Test.
