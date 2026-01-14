#ifndef HEAPSORT_H_
#define HEAPSORT_H_

#include <algorithm>
#include <iterator>
#include <type_traits>
#include <utility>

namespace HeapSortTools {};

template <typename Iter>
void HeapSort(Iter begin, Iter end) {
  static_assert(
      std::is_same_v<typename std::iterator_traits<Iter>::iterator_traits,
                     typename std::random_access_iterator_tag>,
      "HeapSort requires random access iterator");
}

#endif  // HEAPSORT_H_
