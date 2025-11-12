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
  RingBuffer& operator=(const RingBuffer& other);
  RingBuffer& operator=(RingBuffer&& other);

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

#endif  // RINGBUFFER_H_