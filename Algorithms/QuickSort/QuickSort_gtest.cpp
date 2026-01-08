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
