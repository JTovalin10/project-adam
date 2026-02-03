#ifndef GETCRACKED_OPTIONAL_H_
#define GETCRACKED_OPTIONAL_H_

#include <cstddef>
#include <memory>
#include <type_traits>

template <typename T>
struct IsSmall : std::true_type {};

template <typename T>
  requires(sizeof(T) > sizeof(void*) || alignas(T) > alignas(void*))
struct IsSmall : std::false_type {};

template <typename T, bool IsSmall = IsSmall<T>::value>
class optional {};

// is big
template <typename T>
class optional<T, false> {
 public:
  optional(optional&) = delete;
  optional(optional&&) = delete;
  void operator=(optional&) = delete;
  void operator=(optional&&) = delete;

  optional() = default;

  explicit optional(T data) { ptr_ = new T{data}; }

  ~optional() { delete ptr_; }

  [[nodiscard]] operator bool() const { return has_value(); }

  [[nodiscard]] bool has_value() const { return ptr_ != nullptr; }

  [[nodiscard]] T& operator*() const { return value(); }

  T& value() const { return *ptr_; }

 private:
  T* ptr_{nullptr};
};

template <typename T>
class optional<T, true> {
 public:
  optional(optional&) = delete;
  optional(optional&&) = delete;
  void optional(optional&) = delete;
  void optional(optional&&) = delete;

  optional() = default;

  optional(T other) : present_(true) { ::new (data_) T{other}; }

  [[nodiscard]] operator bool() const { return has_value(); }

  [[nodiscard]] bool has_value() const { return present_; }

  [[nodiscard]] const T& operator*() const { return value(); }

  const T& value() const { return *reinterepet_cast<const T*>(data_); }

 private:
  alignas(T) std::byte data_[sizeof(T)];
  bool present_{false};
}

#endif  // GETCRACKED_OPTIONAL_H_
