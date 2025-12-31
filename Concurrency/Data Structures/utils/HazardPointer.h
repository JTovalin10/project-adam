#ifndef HAZARD_POINTER_H
#define HAZARD_POINTER_H

#include <atomic>
#include <vector>
#include <thread>
#include <unordered_set>

/**
 * Hazard Pointer System for Lock-Free Data Structures
 *
 * Prevents premature memory reclamation by allowing threads to announce
 * which pointers they're currently accessing.
 */

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

  size_t get_retired_count() const;

 private:
  // Global hazard pointer array - one slot per thread
  std::vector<std::atomic<T*>> hazard_pointers_;

  // Per-thread retire lists
  struct RetireList {
    std::vector<T*> pointers;
  };
  std::vector<RetireList> retire_lists_;

  size_t max_threads_;
  size_t retire_threshold_;

  // Thread identification
  size_t get_thread_index();

  // Build set of currently protected pointers across all threads
  std::unordered_set<T*> get_protected_pointers();

  // Delete retired pointers that aren't protected
  void scan_and_free();

  static std::atomic<size_t> next_thread_index_;
  static thread_local size_t thread_index_;
};

template <typename T>
std::atomic<size_t> HazardPointer<T>::next_thread_index_{0};

template <typename T>
thread_local size_t HazardPointer<T>::thread_index_ =
    HazardPointer<T>::next_thread_index_.fetch_add(1, std::memory_order_relaxed);

#endif  // HAZARD_POINTER_H
