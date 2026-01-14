#ifndef UTILS_UNIQUEPTR_H
#define UTILS_UNIQUEPTR_H

#include <endian.h>

#include <stdexcept>

namespace slime {
template <typename T>
struct custom_deleter {
  void operator()(T* ptr) const { delete ptr; }
};

template <typename T, typename Deleter = custom_deleter<T>>
class unique_ptr {
 public:
  unique_ptr() : ptr_(nullptr) {}

  explicit unique_ptr(T* ptr) : ptr_(ptr) {}

  unique_ptr(const unique_ptr&) {
    throw std::logic_error("Unique Pointer should not copy");
  }

  unique_ptr& operator=(const unique_ptr&) {
    throw std::logic_error("Unique Pointer should not copy");
  }

  unique_ptr(unique_ptr&& other) noexcept {
    ptr_ = other.release();
    deleter_ = std::move(other.deleter_);
  }

  unique_ptr operator=(unique_ptr&& other) noexcept {
    if (this != &other) {
      deleter_(ptr_);
      ptr_ = other.release();
      deleter_ = std::move(other.deleter_);
    }
    return *this;
  }

  ~unique_ptr() {
    if (ptr_) {
      deleter_(ptr_);
    }
  }

  T* release() {
    T* temp = ptr_;
    ptr_ = nullptr;
    return temp;
  }

  template <class... Args>
  slime::unique_ptr<T> make_unique(Args&&... args) {}

  void reset(T* pointer = nullptr) {
    deleter_(ptr_);
    ptr_ = pointer;
  }

  bool is_owning() const { return ptr_ != nullptr; }

  T& operator*() const { return *ptr_; }

  T* operator->() const { return ptr_; }

  operator bool() const { return ptr_ != nullptr; }

 private:
  T* ptr_;
  [[no_unique_address]] Deleter deleter_;
};
}  // namespace slime

#endif  // UTILS_UNIQUEPTR_H
