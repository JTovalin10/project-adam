#ifndef UTILS_SHARED_PTR_H_
#define UTILS_SHARED_PTR_H_

// Code comes from the implement shared_ptr coding challenge from getcracked.io
// this is my implementation of it

#include <cstddef>
#include <mutex>

namespace slime {
struct control_block {
  // we only want to consider shared_ptr count not weak_ptr
  size_t count_{0};
  // we can also use std::atomic
  mutable std::mutex mutex_;
  // no custom deleter

  void increment_count() {
    std::lock_guard lock(mutex_);
    count_++;
  }

  void decerement_count() {
    std::lock_guard lock(mutex_);
    count_--;
  }
};

template <typename T>
class shared_ptr {
 public:
  shared_ptr() : ptr_{nullptr}, block_(nullptr) {}

  shared_ptr(T* pointer) : ptr_(pointer), block_(new control_block) {
    block_->increment_count();
  }

  shared_ptr(const shared_ptr& other) noexcept
      : ptr_(other.ptr_), block_(other.block_) {
    if (block_) {
      block_->increment_count();
    }
  }

  shared_ptr& operator=(const shared_ptr& other) noexcept {
    if (this != &other) {
      reset();
      ptr_ = other.ptr_;
      block_ = other.block_;
      block_->increment_count();
    }
    return *this;
  }

  shared_ptr(shared_ptr&& other) noexcept
      : ptr_(other.ptr_), block_(other.block_) {
    other.ptr_ = nullptr;
    other.block_ = nullptr;
  }

  shared_ptr& operator=(shared_ptr&& other) noexcept {
    if (this != &other) {
      reset();
      ptr_ = other.ptr_;
      block_ = other.block_;

      other.ptr_ = nullptr;
      other.block_ = nullptr;
    }
    return *this;
  }

  ~shared_ptr() {
    if (block_) {
      block_->decerement_count();
      if (get_count() == 0) {
        delete ptr_;
        delete block_;
      }
    }
  }

  void reset(T* pointer = nullptr) {
    if (block_) {
      block_->decerement_count();
      if (block_->count_ == 0) {
        delete ptr_;
        delete block_;
      }
    }

    if (pointer) {
      ptr_ = pointer;
      block_ = new control_block{};
      block_->increment_count();
    } else {
      ptr_ = nullptr;
      block_ = nullptr;
    }
  }

  size_t get_count() const { return block_ ? block_->count_ : 0; }

  T* operator->() const { return ptr_; }
  T& operator*() const { return *ptr_; }
  operator bool() const noexcept { return ptr_ != nullptr; }

 private:
  T* ptr_;
  control_block* block_;
};
};  // namespace slime
#endif  // UTILS_SHARED_PTR_H_
