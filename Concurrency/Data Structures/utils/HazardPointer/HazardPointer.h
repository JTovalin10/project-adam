#ifndef HAZARD_POINTER_H
#define HAZARD_POINTER_H

#include <algorithm>
#include <atomic>
#include <memory>
#include <stdexcept>
#include <thread>
#include <unordered_set>
#include <vector>

static const auto MAX_THREADS = std::thread::hardware_concurrency();

template <typename T>
class HazardPointer {
 public:
  explicit HazardPointer(size_t max_threads);
  ~HazardPointer();

  HazardPointer(const HazardPointer&) = delete;
  HazardPointer& operator=(const HazardPointer&) = delete;

  void protect(T* ptr);
  void release();
  void retire(T* ptr);

  size_t get_retired_count() const { return thread_data_.retire_list.size(); }

 private:
  struct HPRecord {
    std::atomic<T*> ptr{nullptr};
    std::atomic<std::thread::id> owner{};
  };

  // Use unique_ptr array since atomics aren't movable
  std::unique_ptr<HPRecord[]> hazard_pointers_;

  struct ThreadLocalData {
    std::vector<T*> retire_list;
  };
  static thread_local ThreadLocalData thread_data_;

  size_t max_threads_;
  size_t retire_threshold_;

  size_t acquire_slot();
  std::unordered_set<T*> get_protected_pointers();
  void scan_and_free();
};

template <typename T>
thread_local
    typename HazardPointer<T>::ThreadLocalData HazardPointer<T>::thread_data_;

template <typename T>
HazardPointer<T>::HazardPointer(size_t num_threads) {
  if (MAX_THREADS == 0 || num_threads < MAX_THREADS) {
    max_threads_ = num_threads;
  } else {
    max_threads_ = MAX_THREADS;
  }
  retire_threshold_ = 2 * max_threads_;

  // Allocate array directly - no resize needed
  hazard_pointers_ = std::make_unique<HPRecord[]>(max_threads_);
}

template <typename T>
HazardPointer<T>::~HazardPointer() {
  // Clean up any remaining retired pointers in this thread's list
  for (auto* ptr : thread_data_.retire_list) {
    delete ptr;
  }
  thread_data_.retire_list.clear();
}

template <typename T>
size_t HazardPointer<T>::acquire_slot() {
  auto this_id = std::this_thread::get_id();

  // First pass: check if we already own a slot
  for (size_t i = 0; i < max_threads_; ++i) {
    if (hazard_pointers_[i].owner.load(std::memory_order_relaxed) == this_id) {
      return i;
    }
  }

  // Second pass: try to acquire an empty slot
  for (size_t i = 0; i < max_threads_; ++i) {
    std::thread::id expected{};
    if (hazard_pointers_[i].owner.compare_exchange_strong(
            expected, this_id, std::memory_order_acq_rel)) {
      return i;
    }
  }

  // No slots available
  throw std::runtime_error("No hazard pointer slots available");
}

template <typename T>
void HazardPointer<T>::protect(T* ptr) {
  size_t idx = acquire_slot();
  hazard_pointers_[idx].ptr.store(ptr, std::memory_order_release);
}

template <typename T>
void HazardPointer<T>::release() {
  auto this_id = std::this_thread::get_id();

  for (size_t i = 0; i < max_threads_; ++i) {
    if (hazard_pointers_[i].owner.load(std::memory_order_relaxed) == this_id) {
      hazard_pointers_[i].ptr.store(nullptr, std::memory_order_release);
      return;
    }
  }
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
  std::unordered_set<T*> protected_set;

  for (size_t i = 0; i < max_threads_; ++i) {
    T* ptr = hazard_pointers_[i].ptr.load(std::memory_order_acquire);
    if (ptr != nullptr) {
      protected_set.insert(ptr);
    }
  }
  return protected_set;
}

template <typename T>
void HazardPointer<T>::scan_and_free() {
  std::unordered_set<T*> protected_ptrs = get_protected_pointers();

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

#endif  // HAZARD_POINTER_H
