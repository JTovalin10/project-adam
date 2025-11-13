#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
#include <cstddef>
#include <optional>

#define DEFAULT_CAPACITY = 10

/**
 * A ring buffer is a fixed size first in first our data structure
 * (queue) where it treats memory as if it was connecteed end to end
 *
 * head and tail: it uses these pointers to manage the elements
 * head - acts like a write pointer, when an element is added this advances
 * tail - acts like a read pointer, when an element is removed this advances
 * if either pointer reaches the end of the buffer then it wraps around to
 * the beginning
 *
 * When the buffer is full the new element is written to the oldest
 * data, overwriting it which allows the buffer to maintain a consistent size
 * without running out of memory
 *
 * When the pointer reaches the end of the buffer it wraps around to the beginning
 * creating the circular behavior
 *
 */

template<typename T>
class RingBuffer {
 public:
  using size_type = std::size_t;
  using value_type = T;
  
  /**
   * Constructs an empty RingBuffer with a capacity using the DEFAULT_CAPACITY
   */
  RingBuffer();
  
  /**
   *  Constructs an empty Ringbuffer with the client defined capacity
   */
  explicit RingBuffer(size_type capacity);

  /**
   *  Constructs a RingBuffer by copying another client given RingBuffer
   *
   *  ARGS:
   *  other: the RingBuffer that will be copied
   */
  RingBuffer(const RingBuffer& other);

  /**
   *  Constructs a RingBuffer by stealing from the client given RingBuffer.
   *  This will leave the other RingBuffer empty
   *
   *  ARGS:
   *  other: the RingBuffer that will be stolen
   */
  RingBuffer(RingBuffer&& other);

  /**
   * Deconstructs the RingBuffer
   */
  ~RingBuffer();

  /**
   * Copy assignment operator which copys another RingBuffer
   * and replaces all current fields with the other RingBuffer
   *
   * ARGS:
   * other: the client given RingBuffer that will be copied
   *
   * RETURNS:
   * a reference pointer to the this RingBuffer
   */
  RingBuffer& operator=(const RingBuffer& other) {
    if (this == &other) {
      return *this;
    }
    delete[] buffer_;
    buffer_ = new T[other.capacity_];
    for (size_type i = 0; i < other.capacity_; i++) {
      buffer_[i] = other.buffer_[i];
    }
    capacity_ = other.capacity_;
    size_ = other.size_;
    read_ = other.read_;
    write_ = other.write_;
    return *this;
  }

  /**
   * move assignment operator which steals another RingBuffer
   * and replaces all current fields with the other RingBuffer.
   * This will leave the other RingBuffer empty.
   *
   * ARGS:
   * other: the client given RingBuffer that will be stolen
   *
   * RETURNS:
   * a reference pointer to the this RingBuffer
   */
  RingBuffer& operator=(RingBuffer&& other) {
    if (this == &other) {
      return *this;
    }
    buffer_ = other.buffer_;
    other.buffer_ = nullptr;

    capacity_ = other.capacity_;
    size_ = other.size_;
    read_ = other.read_;
    write_ = other.write_;

    other.capacity_ = 0;
    other.size_ = 0;
    other.read_ = 0;
    other.write_ = 0;
    return *this;
  }
  
  /**
   *  Adds give item to the end of the buffer
   *
   *  ARGS:
   *  item: the element that will be added to the end of the buffer
   */
  void push(const value_type& item);
  
  /**
   * Removes and returns the element at the start of the buffer
   *
   * RETURNS:
   * if the buffer is empty it will return std::nullopt, else
   * it will return the value at the start of the buffer
   */
  std::optional<T> pop();
  

  /**
   *  [read_, ..., write_]
   */


  /** 
   * returns the element at the start of the buffer. Additionally,
   * it does not remove the element from the buffer
   *
   * RETURNS:
   * if the buffer is empty then it will return std::nullopt, else 
   * it will return the value of the element at the start of the buffer
   */
  std::optional<T> front() const;
  
  /**
   * Returns the element at the end of the buffer (does not modify the buffer)
   *
   * RETURNS:
   * std::nullopt if the buffer is empty, else
   * value of the element at the end of the buffer
   */
  std::optional<T> back() const;
  
  /**
   * checks if there are any elements in the buffer
   *
   * RETURNS:
   * true if the buffer contains elements, else
   * false
   */
  bool empty() const;
  
  /**
   * Checks if the number of elements is at capacity
   *
   * RETURNS:
   * true if size_ == capacity_
   * else false
  bool full() const;

  /**
   * Returns the number of elements in the buffer
   * 
   * RETURNS:
   * number of elemnts in the buffer
   */
  size_type size() const;

  /**
   * Returns the capacity that was defined at Construction
   *
   * RETURNS:
   * size_type which represents the capacity
   */
  size_type capacity() const;
  
  /**
   * Removes all elements from the buffer
   *
   * EFFECTS:
   * buffer_, size_, write_, read_
   *
   */
  void clear();

  private:
  value_type* buffer_;
  size_type size_ = 0;
  size_type read_ = 0;
  size_type write_ = 0;
  const size_type capacity_;
};

template<typename T>
RingBuffer<T>::RingBuffer() : capacity_(DEFAULT_CAPACITY) {
  buffer_ = new T[capacity_];
}

template<typename T>
explicit RingBuffer<T>::RingBuffer(size_type capacity) : capacity_(capacity) {
  buffer_ = new T[capacity_];
}

template<typename T>
RingBuffer<T>::RingBuffer(const RingBuffer& other) : size_(other.size_), read_(other.read_), write_(other.write_), capacity_(other.capacity_) {
  buffer_ = new T[capacity_];
  for (size_type i = 0; i < capacity_; i++) {
    buffer_[i] = other.buffer_[i];
  }
}

template<typename T>
RingBuffer<T>::RingBuffer(RingBuffer&& other) : size_(other.size_), read_(other.read_), write_(other.write_), capacity_(other.capacity_), buffer_(other.buffer_) { 
  other.buffer_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
  other.read_ = 0;
  other.write_ = 0;
}

template<typename T>
RingBuffer<T>::~RingBuffer() {
  delete[] buffer_;
}

template<typename T>
void RingBuffer<T>::push(const value_type& item) {
  // we want to overwrite the oldest data
  buffer_[write_] = item;
  write_ = (write_ + 1) % capacity_;
  // if the buffer is full then the head and tail are at the same item
  // hence, the write and read are at the oldest item
  // so we just overwrite the item and increment both the head and tail
  // as that item is no longer the oledest item
  if (full()) {
    tail_ = (tail_ + 1) % capacity_;
  } else { 
    size_++;
  }
}

template<typename T>
std::optional<T> RingBuffer<T>::pop() {
  if (empty()) {
    return std::nullopt;
  }
  T value = buffer_[read_];

  buffer_[read_] = std::nullopt;
  read_ = (read_ + 1) % capacity_;
  size_--;
  return value;
}

template<typename T>
std::optional<T> RingBuffer<T>::front() const {
  if (empty()) {
    return std::nullopt;
  }
  T value = buffer_[read_];
  return value;
}

template<typename T>
std::optional<T> RingBuffer<T>::back() const {
  if (empty()) {
    return std::nullopt;
  }
  T value = buffer_[write_];
  return value;
}

template<typename T>
bool RingBuffer<T>::empty() const {
  return size_ == 0;
}

template<typename T>
bool RingBuffer<T>::full() const {
  return size_ == capacity_;
}

template<typename T>
typename RingBuffer<T>::size_type RingBuffer<T>::size() const {
  return size_;
}

template<typename T>
typename RingBuffer<T>::size_type RingBuffer<T>::capacity() const {
  return capacity_;
}

template<typename T>
void RingBuffer<T>::clear() {
  delete[] buffer_;
  buffer_ = new T[capacity_];
  size_ = 0;
  read_ = 0;
  write_ = 0;
}

#endif  // RINGBUFFER_H_

