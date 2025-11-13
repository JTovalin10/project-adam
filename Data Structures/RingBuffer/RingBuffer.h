#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
#include <cstddef>

#define DEFAULT_CAPACITY = 10

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
  size_type capacity_;
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

}

template<typename T>
bool RingBuffer<T>::is_full() const {

}

template<typename T>
typename RingBuffer<T>::size_type RingBuffer<T>::size() const {

}

template<typename T>
typename RingBuffer<T>::size_type RingBuffer<T>::capacity() const {

}

template<typename T>
void RingBuffer<T>::clear() {

}

#endif  // RINGBUFFER_H_
