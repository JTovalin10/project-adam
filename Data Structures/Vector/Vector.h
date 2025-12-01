#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>  // for std::size_t
#include <memory>
#include <stdexcept>  // for std::out_of_range (throws)

/**
 * A dynamic array template that stores elements of type T
 *
 * This vector is suppose to mimic std::Vector
 *
 * @tparam T the type of elements stored in the vector
 */

template <typename T>
class Vector {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using iterator = value_type*;
  using const_iterator = const value_type*;

  /**
   * Move Constructor - constructs this Vector by stealing from the other Vector
   *
   * ARGS:
   * other: the vector we will steal from
   */
  // ---- Type Aliases ---- //

  // The standarize types for compatibility with STL algorithms

  // ---- Constructors & DESTRUCTOR ---- //

  /**
   * Creates an empty vector with a default inital capacity
   */
  Vector();

  /**
   * Constructs a vector by coping the contents of another vector
   *
   * ARGS:
   * other: the Vector whose content will be copied
   */
  Vector(const Vector& other);

  /**
   * Move Constructor - constructs this Vector by stealing from the other Vector
   *
   * ARGS:
   * other: the vector we will steal from
   */
  Vector(Vector&& other) noexcept;

  /**
   * Destroys the vector and safely deallocates the dynamically allocated
   * memory.
   */
  ~Vector();

  /**
   * Performs a deep copy of another Vector's content
   *
   * ARGS:
   * other: The Vector whose content will be copied
   *
   * RETURNS:
   * A reference to the current Vector (*this)
   */
  Vector& operator=(const Vector& other);

  /**
   * Move assignment operator - constructs this Vector by stealing from the
   * other Vector
   *
   * ARGS:
   * other: the vector we will steal from
   */
  Vector& operator=(Vector&& other) noexcept;

  // ---- Element Access ---- //

  /**
   * Returns a mutable reference to the element at the given index
   *
   * REQUIRES:
   * index is a valid position (0 <= index < size_)
   *
   * ARGS:
   * index: The position of the element
   *
   * RETURNS:
   * A mutable reference (T&) to the element
   *
   * THROWS:
   * std::out_of_range if (index < 0) or (size_ > index)
   */
  T& operator[](size_type index);

  /**
   * Returns a const reference to the element at the given index
   *
   * REQUIRES:
   * index is a valid position (0 <= index < size_)
   *
   * ARGS:
   * index: The position of the element
   *
   * RETURNS:
   * A immutable reference (const T&) to the element
   */
  const T& operator[](size_type index) const;

  /**
   * Returns a reference to the element at the given index with bounds
   * checking
   *
   * REQUIRES:
   * index is a valid position (0 <= index < size_)
   *
   * ARGS:
   * index: The position of the element
   *
   * RETURNS:
   * A mutuable reference (T&) to the element
   *
   * THROWS:
   * std::out_of_range if the index is invalid (index >= size_ or index < 0)
   */
  T& at(size_type index);

  /**
   * Returns a const reference to the element at the given index with
   * bounds checking
   *
   * REQUIRES:
   * index is a valid position (0 <= index <= size_)
   *
   * ARGS:
   * index: The position of the element
   *
   * RETURNS:
   * A const reference (const T&) to the element
   *
   * THROWS:
   * std::out_of_range if the index is invalid (index >= size_ or index < 0)
   */
  const T& at(size_type index) const;

  // ---- Capacity & Size ---- //

  /**
   * Returns the number of elements in the Vector
   *
   * RETURNS:
   * The current number of elements (size_)
   */
  size_type size() const;

  /**
   * Returns the total storage capacity of the Vector
   *
   * RETURNS:
   * The current storage capacity (capacity_)
   */
  size_type capacity() const;

  /**
   * Checks if the Vector is emoty
   *
   * RETURNS:
   * True if the Vector size is 0, otherwise false
   */
  bool empty() const;

  // ---- Modifiers ---- //

  /**
   * Adds a new element to the end of the Vector
   *
   * ARGS:
   * item: the element to be appended
   *
   * EFFECTS:
   * The size of the vector will be increased by one. May trigger
   * a reallocation if the capacity is exceeded. Adds the element to
   * the end of the list
   */
  void push_back(const T& item);

  /**
   * Remove the last element from the vector
   *
   * REQUIRES:
   * The vector is not empty
   *
   * EFFECTS:
   * The size of the Vector is reduced by one
   *
   * THROWS:
   * std::out_of_range if size == 0
   */
  void pop_back();

  /**
   * Inserts an element at a specific index
   *
   * REQUIRES:
   * 0 <= index <= size
   *
   * ARGS:
   * item: The element to be inserted
   * index: the position where the element will be inserted
   *       - 0 to size-1: inserts in the middle or beginning
   *       - size: inserts at the end (same as push_back)
   *
   * EFFECTS:
   * Element at and after index are shifted to the right. The size
   * increases by one.
   *
   * THROWS:
   * std::out_of_range if index > size
   */
  void insert(const T& item, size_type index);

  /**
   * Sets the element at the specific index
   *
   * REQUIRES:
   * 0 <= index < size
   *
   * ARGS:
   * item: The element to be set
   * index: the position where the element will be set
   *
   * EFFECTS:
   */
  void set(const T& item, size_type index);

  /**
   * Removes the element at the specific index
   *
   * REQUIRES:
   * 0 <= index < size
   *
   * ARGS:
   * index: the position where the element will be removed
   *
   * EFFECTS:
   * If the element is not the last element then elements after index
   * are shifted to the left. The size will decrease by one
   */
  void remove(size_type index);

  // ---- ITERATORS ---- //

  /** These methods will allow the Vector to be used with range-based
   * for loops
   */

  iterator begin();
  const_iterator begin() const;

  iterator end();
  const_iterator end() const;

  // ---- Private Members ---- //

 private:
  size_type capacity_;
  size_type size_;
  T* array_;
  static constexpr size_type initial_capacity = 1;
  static constexpr double resize_multiplier = 2.0;

  /**
   * Helper function that doubles the size of the array storage when needed
   *
   * EFFECTS:
   * Allocates new memory, copies all existing elements, and updates capacity_
   */
  void resize();
};

// Template member function implementations
// Following Google C++ Style Guide: template implementations belong in header

template <typename T>
Vector<T>::Vector()
    : capacity_(initial_capacity), size_(0), array_(new T[capacity_]) {}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : capacity_(other.capacity_), size_(other.size_) {
  std::unique_ptr<T[]> temp(new T[capacity_]);
  for (size_type i = 0; i < size_; i++) {
    temp[i] = other.array_[i];
  }
  array_ = temp.release();
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : capacity_(other.capacity_), size_(other.size_), array_(other.array_) {
  other.array_ = nullptr;
  other.size_ = 0;
  other.capacity_ = initial_capacity;
}

template <typename T>
Vector<T>::~Vector() {
  delete[] array_;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
  if (this == &other) {
    return *this;
  }
  size_type new_size = other.size_;
  size_type new_capacity = other.capacity_;
  std::unique_ptr<T[]> temp(new T[new_capacity]);
  for (size_type i = 0; i < other.size_; i++) {
    temp[i] = other.array_[i];
  }
  delete[] array_;
  array_ = temp.release();
  size_ = new_size;
  capacity_ = new_capacity;
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
  if (this != &other) {
    delete[] array_;
    array_ = other.array_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.array_ = nullptr;
    other.size_ = 0;
    other.capacity_ = initial_capacity;
  }
  return *this;
}

template <typename T>
T& Vector<T>::operator[](size_type index) {
  if (index >= size_) {
    throw std::out_of_range("Vector::operator[], Invalid Index");
  }
  return array_[index];
}

template <typename T>
const T& Vector<T>::operator[](size_type index) const {
  if (index >= size_) {
    throw std::out_of_range("Vector::operator[], invalid index");
  }
  return array_[index];
}

template <typename T>
T& Vector<T>::at(size_type index) {
  if (index >= size_) {
    throw std::out_of_range("Vector::at, invalid index");
  }
  return array_[index];
}

template <typename T>
const T& Vector<T>::at(size_type index) const {
  if (index >= size_) {
    throw std::out_of_range("Vector::at, invalid index");
  }
  return array_[index];
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const {
  return size_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
bool Vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
void Vector<T>::push_back(const T& item) {
  if (size_ == capacity_) {
    resize();
  }
  array_[size_] = item;
  size_++;
}

template <typename T>
void Vector<T>::pop_back() {
  if (size_ == 0) {
    throw std::out_of_range("Vector::pop_back, vector is empty");
  }
  size_--;
}

template <typename T>
void Vector<T>::insert(const T& item, size_type index) {
  if (index > size_) {
    throw std::out_of_range("Vector::insert, index is out of range");
  }
  if (size_ == capacity_) {
    resize();
  }
  for (size_type i = size_; i > index; --i) {
    array_[i] = array_[i - 1];
  }
  array_[index] = item;
  size_++;
}

template <typename T>
void Vector<T>::set(const T& item, size_type index) {
  if (index >= size_) {
    throw std::out_of_range("Vector::set, index is out of range");
  }
  array_[index] = item;
}

template <typename T>
void Vector<T>::remove(size_type index) {
  if (size_ == 0) {
    throw std::out_of_range("Vector::remove, vector is empty");
  }
  if (index >= size_) {
    throw std::out_of_range("Vector::remove, index is out of range");
  }
  for (size_type i = index; i < size_ - 1; i++) {
    array_[i] = array_[i + 1];
  }
  size_--;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return array_;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
  return array_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return array_ + size_;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const {
  return array_ + size_;
}

template <typename T>
void Vector<T>::resize() {
  size_type new_capacity = resize_multiplier * capacity_;
  std::unique_ptr<T[]> temp(new T[new_capacity]);
  for (size_type i = 0; i < size_; i++) {
    temp[i] = array_[i];
  }
  delete[] array_;
  array_ = temp.release();
  capacity_ = new_capacity;
}

#endif  // VECTOR_H_
