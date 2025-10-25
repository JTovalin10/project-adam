#include "Vector.h"

template<typename T>
Vector<T>::Vector() : capacity_(initial_capacity), size_(0), array_(new T[initial_capacity]) {}

template<typename T>
Vector<T>::Vector(const Vector& other) : capacity_(other.capacity_), size_(other.size_), array_(new T[capacity_]) {
    for (int i = 0; i < size_; i++) {
        array_[i] = other.array_[i];
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete[] array_;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }
    delete[] array_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    array_ = new T[capacity_]
    for (int i = 0; i < size; i++) {
        array_[i] = other.array_[i];
    }
    return *this;
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Vector::operator[], Invalid Index");
    }
    return array_[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Vector::operator[], invalid index");
    }
    return array_[index];
}

template<typename T>
T& Vector<T>::at(size_type index) {
    if (index >= size) {
        throw std::out_of_range("Vector::at, invalid index");
    }
    return array_[index];
}

template<typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Vector::at, invalid index");
    }
    return array_[index];
}

// -- CAPACITY & SIZE -- //

template<typename T>
typename Vector<T>::size_type Vector<T>::size() const {
    return size_;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::capacity() const {
    return capacity_;
}

template<typename T>
bool Vector<T>::empty() const {
    return size_ == 0;
}

// -- Modifiers -- //

template<typename T>
void Vector<T>::push_back(const T& item) {
    if (size_ == capacity_) {
        resize();
    }
    array_[size] = item;
    size++;
}

template<typename T>
void Vector<T>::pop_back() {
    if (size_ == 0) {
        throw std::out_of_range("Vector::pop_back, vector is empty");
    }
    size--;
}

//TODO: fix this as it is doing set not insert
template<typename T>
void Vector<T>::insert(const T& item, size_type index) {
    if (index >= size_) {
        throw std::out_of_range("Vector::insert, index is out of range");
    }
    if (size_ == capacity_) {
        resize();
    }
    size++;
    for (int i = size_ - 1; i > index ; i--) {
        array[i] = array[i - 1];
    }
    array_[index] = item;
}

template<typename T>
void Vector<T>::remove(size_type index) {
    if (size_ == 0) {
        throw std::out_of_range("Vector::remove, vector is empty");
    }
    if (index == size_) {
        pop_back();
    } else {
        for (int i = index; i < size_ - 1; i++) {
            array_[i] = array_[i + 1];
        }
    }
}

#TODO:
template<typename T>
typename Vector<T>::iterator Vector<T>::begin() {
    continue;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
    continue;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() {
    continue;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const {
    continue;
}

template<typename T>
void Vector<T>::resize() {
    size_type new_capacity = 2 * capacity_;
    T* temp_array = new T[new_capacity];
    for (int i = 0; i < size_; i++) {
        temp_array[i] = array_[i];
    }
    delete[] array_;
    array_ = temp_array;
}
