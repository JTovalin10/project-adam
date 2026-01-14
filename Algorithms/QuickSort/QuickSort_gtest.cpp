#include <gtest/gtest.h>

#include <list>
#include <vector>

#include "QuickSort.h"

// passes properly uncomment the last line if you want to double check
TEST(QuickSortTest, static_assert_passes) {
  std::vector<int> vec = {1, 2, 3};
  quicksort(vec.begin(), vec.end());

  std::list<int> lst = {1, 2, 3};
  // quicksort(lst.begin(), lst.end());
}

TEST(QuickSortTest, one_loop) {
  std::vector<int> vec = {2, 1};
  quicksort(vec.begin(), vec.end());
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
}

TEST(QuickSortTest, two_loop) {
  std::vector<int> vec = {3, 2, 1};
  quicksort(vec.begin(), vec.end());
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
}
