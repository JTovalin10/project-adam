#ifndef SPSCQUEUE_H_
#define SPSCQUEUE_H_

#include <atomic>
#include <cstddef>
#include <memory>
#include <vector>

static const auto CACHE_LINE_SIZE =
    std::hardware_constructive_interference_size;

template <typename T>
class SPSCQueue {
  using type_name = T;
  using size_type = std::size_t;

 public:
  explicit SPSCQueue(size_t capacity = 1) {
    buffer_.resize(capacity);
    capacity_ = capacity;
  }

  SPSCQueue(const SPSCQueue& other) = delete;

  SPSCQueue& operator=(const SPSCQueue& other) = delete;

  ~SPSCQueue() = default;

  SPSCQueue(SPSCQueue&& other) = delete;

  SPSCQueue& operator=(SPSCQueue&& other) = delete;

  bool push(type_name element) {
    size_t current_producer = producer_.load(std::memory_order_relaxed);
    size_t next_producer = (current_producer + 1) % capacity_;
    // if the buffer is full
    if (next_producer == consumer_.load(std::memory_order_acquire)) {
      return false;
    }
    buffer_[current_producer] = std::make_shared<T>(std::move(element));
    producer_.store(next_producer, std::memory_order_release);
    return true;
  }

  std::shared_ptr<T> try_pop() {
    size_t current_consumer = consumer_.load(std::memory_order_acquire);
    // if the buffer is empty
    if (current_consumer == producer_.load(std::memory_order_relaxed)) {
      return std::shared_ptr<T>();
    }
    std::shared_ptr<T> result = buffer_[current_consumer];
    size_t next_consumer = (current_consumer + 1) % capacity_;
    consumer_.store(next_consumer, std::memory_order_release);
    return result;
  }

  bool empty() const {
    return producer_.load(std::memory_order_relaxed) ==
           consumer_.load(std::memory_order_relaxed);
  }

  size_type size() const {
    return producer_.load(std::memory_order_relaxed) -
           consumer_.load(std::memory_order_relaxed);
  }

 private:
  std::vector<std::shared_ptr<T>> buffer_;
  size_type capacity_;
  alignas(CACHE_LINE_SIZE) std::atomic<size_type> consumer_{0};  // read
  alignas(CACHE_LINE_SIZE) std::atomic<size_type> producer_{0};  // write
};

#endif  // SPSCQUEUE_H_
