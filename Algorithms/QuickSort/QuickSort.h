#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include <iterator>
#include <type_traits>
#include <utility>

namespace QuickSortTools {
template <typename Iter>
Iter partition(Iter begin, Iter end) {
  auto pivot_val = *(begin + (end - begin) / 2);

  auto i = begin;
  auto j = end - 1;

  while (i <= j) {
    while (*i < pivot_val) ++i;
    while (*j > pivot_val) --j;

    if (i >= j) return j;

    if (i <= j) {
      std::swap(*i, *j);
      ++i;
      --j;
    }
  }
  return i;
}
}  // namespace QuickSortTools

template <typename Iter>
void quicksort(Iter begin, Iter end) {
  // check to ensure the client passes random access iterators
  static_assert(
      std::is_same_v<typename std::iterator_traits<Iter>::iterator_category,
                     std::random_access_iterator_tag>,
      "quicksort requires random access iterators");

  // check if it is out of bounds
  if (begin >= end || (begin + 1) >= end) {
    return;
  }
  // get the mid, next, and prev points
  auto part = QuickSortTools::partition(begin, end);
  quicksort(begin, part);
  quicksort(part + 1, end);
}

#endif  // QUICKSORT_H_
