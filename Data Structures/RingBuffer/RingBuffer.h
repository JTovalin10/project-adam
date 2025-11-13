#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
#include <cstddef>

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

  RingBuffer();
  explicit RingBuffer(size_type capacity);
  RingBuffer(const RingBuffer& other);
  RingBuffer(RingBuffer&& other);
  ~RingBuffer();
  RingBuffer& operator=(const RingBuffer& other) {
    if (this == &other) {
      return *this;
    }

    return *this;
  }

  RingBuffer& operator=(RingBuffer&& other) {
    if (this == &other) {
      return *this;
    }
    
    return *this;
  }
  
  void enqueue(const value_type& item);
  void push(const value_type& item);
  void write(const value_type& item);
  void dequeue();
  void pop();
  value_type& read() const;
  
  const value_type& peek() const;
  const value_type& front() const;
  const value_type& back() const;
  
  bool is_empty() const;
  bool is_full() const;
  size_type size() const;
  size_type capacity() const;
  
  void clear();

  private:
  value_type* buffer_;
  size_type size_;
  size_type head_;
  size_type tail_;
  const size_type capacity_;
};

template<typename T>
RingBuffer<T>::RingBuffer() : capacity_(DEFAULT_CAPACITY) {}

template<typename T>
explicit RingBuffer<T>::RingBuffer(size_type capacity) : capacity_(capacity) {}

template<typename T>
RingBuffer<T>::RingBuffer(const RingBuffer& other) {

}

template<typename T>
RingBuffer<T>::RingBuffer(RingBuffer&<T> other) {

}

template<typename T>
RingBuffer<T>::~RingBuffer() {

}

template<typename T>
void RingBuffer<T>::enqueue(const value_type& item) {

}

template<typename T>
void RingBuffer<T>::push(const value_type& item) {

}

template<typename T>
void RingBuffer<T>::write(const value_type& item) {

}

template<typename T>
void RingBuffer<T>::dequeue() {

}


template<typename T>
void RingBuffer<T>::pop() {

}


template<typename T>
typename RingBuffer<T>::value_type& RingBuffer<T>::read() const {

}


template<typename T>
const typename RingBuffer<T>::value_type& RingBuffer<T>::peek() const {

}

template<typename T>
const typename RingBuffer<T>::value_type& RingBuffer<T>::front() const {

}

template<typename T>
const typename RingBuffer<T>::value_type& RingBuffer<T>::back() const {

}

template<typename T>
bool RingBuffer<T>::is_empty() const {
  return size_ == 0;
}

template<typename T>
bool RingBuffer<T>::is_full() const {
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

}

#endif  // RINGBUFFER_H_
