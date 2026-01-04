#ifndef HAZARD_POINTER_H
#define HAZARD_POINTER_H

#include <algorithm>
#include <atomic>
#include <stdexcept>
#include <thread>
#include <unordered_set>
#include <vector>

/**
 * Hazard Pointer System for Lock-Free Data Structures
 *
 * Prevents premature memory reclamation by allowing threads to announce
 * which pointers they're currently accessing.
 */

static const auto MAX_THREADS = std::thread::hardware_concurrency();

template <typename T>
class HazardPointer {
 public:
  explicit HazardPointer(size_t max_threads);

  ~HazardPointer();

  HazardPointer(const HazardPointer&) = delete;
  HazardPointer& operator=(const HazardPointer&) = delete;

  /**
   * Announce that this thread is accessing ptr
   * Must re-verify ptr hasn't changed after calling this
   */
  void protect(T* ptr);

  /**
   * Clear this thread's protection
   */
  void release();

  /**
   * Add ptr to retire list for eventual deletion
   * May trigger scan and reclamation if threshold reached
   */
  void retire(T* ptr);

  // Add to public section of HazardPointer class
  size_t get_retired_count() const { return thread_data_.retire_list.size(); }

 private:
  // Global hazard pointer array - one slot per thread
  std::vector<std::atomic<T*>> hazard_pointers_;

  // Per-thread retire lists
  struct ThreadLocalData {
    std::vector<T*> retire_list;
  };
  static thread_local ThreadLocalData thread_data_;

  size_t max_threads_;
  size_t retire_threshold_;

  // Thread identification
  size_t get_thread_index() const {
    static std::atomic<size_t> counter{0};
    thread_local size_t id = counter.fetch_add(1, std::memory_order_relaxed);
    return id % max_threads_;
  }

  // Build set of currently protected pointers across all threads
  std::unordered_set<T*> get_protected_pointers();

  // Delete retired pointers that aren't protected
  void scan_and_free();
};

template <typename T>
HazardPointer<T>::HazardPointer(size_t num_threads) {
  // edge case where hardware_concurrency returns 0
  // also we want to choose the smaller of user num_hthreads and MAX_THREADS
  if (MAX_THREADS == 0 || num_threads < MAX_THREADS) {
    max_threads_ = num_threads;
  } else {
    max_threads_ = MAX_THREADS;
  }
  // retire_threshold is 2 * max_threads_ per concurrency in action
  retire_threshold_ = 2 * max_threads_;
  hazard_pointers_ = std::vector<std::atomic<T*>>(max_threads_);

  // Initialize each atomic to nullptr
  for (size_t i = 0; i < max_threads_; ++i) {
    hazard_pointers_[i].store(nullptr, std::memory_order_relaxed);
  }
}

template <typename T>
HazardPointer<T>::~HazardPointer() {
  for (auto& hp : hazard_pointers_) {
    hp.store(nullptr, std::memory_order_relaxed);
  }
}

template <typename T>
void HazardPointer<T>::protect(T* ptr) {
  const size_t thread_idx = get_thread_index();

  hazard_pointers_[thread_idx].store(ptr, std::memory_order_release);
}

template <typename T>
void HazardPointer<T>::retire(T* ptr) {
  thread_data_.retire_list.push_back(ptr);

  if (thread_data_.retire_list.size() >= retire_threshold_) {
    scan_and_free();
  }
}

template <typename T>
std::unordered_set<T*> HazardPointer<T>::get_protected_pointers() {
  std::unordered_set<T*> set;

  for (auto& hp : hazard_pointers_) {
    T* ptr = hp.load(std::memory_order_acquire);
    if (ptr != nullptr) {
      set.insert(ptr);
    }
  }
  return set;
}

template <typename T>
void HazardPointer<T>::scan_and_free() {
  const std::unordered_set<T*> protected_ptrs = get_protected_pointers();

  auto& my_list = thread_data_.retire_list;
  auto it = my_list.begin();
  while (it != my_list.end()) {
    if (protected_ptrs.find(*it) == protected_ptrs.end()) {
      delete *it;
      it = my_list.erase(it);
    } else {
      ++it;
    }
  }
}

template <typename T>
void HazardPointer<T>::release() {
  const size_t thread_idx = get_thread_index();

  hazard_pointers_[thread_idx].store(nullptr, std::memory_order_release);
}

// Define the thread_local static member
template <typename T>
thread_local
    typename HazardPointer<T>::ThreadLocalData HazardPointer<T>::thread_data_;

#endif  // HAZARD_POINTER_H
