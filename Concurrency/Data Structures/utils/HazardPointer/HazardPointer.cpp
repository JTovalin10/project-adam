#include "HazardPointer.h"
#include <algorithm>

template <typename T>
HazardPointer<T>::HazardPointer(size_t max_threads)
    : max_threads_(max_threads),
      retire_threshold_(2 * max_threads) {
  hazard_pointers_.resize(max_threads);
  for (auto& hp : hazard_pointers_) {
    hp.store(nullptr, std::memory_order_relaxed);
  }
  retire_lists_.resize(max_threads);
}

template <typename T>
HazardPointer<T>::~HazardPointer() {
  // TODO: Clean up remaining retired pointers
}

template <typename T>
void HazardPointer<T>::protect(T* ptr) {
  // TODO: Store ptr in this thread's hazard slot
  // Consider: What memory order ensures other threads see this?
}

template <typename T>
void HazardPointer<T>::release() {
  // TODO: Clear this thread's hazard slot
}

template <typename T>
void HazardPointer<T>::retire(T* ptr) {
  if (!ptr) return;

  // TODO: Add to retire list, scan if threshold reached
}

template <typename T>
size_t HazardPointer<T>::get_retired_count() const {
  size_t count = 0;
  for (const auto& retire_list : retire_lists_) {
    count += retire_list.pointers.size();
  }
  return count;
}

template <typename T>
size_t HazardPointer<T>::get_thread_index() {
  // TODO: Return this thread's unique index
  return 0;
}

template <typename T>
std::unordered_set<T*> HazardPointer<T>::get_protected_pointers() {
  std::unordered_set<T*> protected_set;

  // TODO: Scan all hazard slots and collect non-null pointers
  // Consider: What memory order do you need when reading other threads' hazard pointers?

  return protected_set;
}

template <typename T>
void HazardPointer<T>::scan_and_free() {
  // TODO: Get protected set, partition retire list, delete unprotected pointers
}
