#include "Queue.h"

template<typename T>
Queue<T>::Queue() {}

template<typename T>
Queue<T>::Queue(const Queue& other) {
    list_ = other.list_;
}

template<typename T>
Queue<T>::Queue(Queue&& other) {
    list_ = std::move(other.list_);
}

template<typename T>
Queue<T>::~Queue() {}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    list_ = other.list_;
    return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) {
    list_ = std::move(other.list_);
    return *this;
}

template<typename T>
typename Queue<T>::value_type& Queue<T>::front() {
    if (list_.empty()) {
        throw std::out_of_range("Queue::front, the list is empty");
    }
    return list_.front();
}

template<typename T>
const typename Queue<T>::value_type& Queue<T>::front() const {
    if (list_.empty()) {
        throw std::out_of_range("Queue::front, the list is empty");
    }
    return list_.front();
}

template<typename T>
typename Queue<T>::value_type& Queue<T>::back() {
    if (list_.empty()) {
        throw std::out_of_range("Queue::front, the list is empty");
    }
    return list_.back();
}

template<typename T>
const typename Queue<T>::value_type& Queue<T>::back() const {
    if (list_.empty()) {
        throw std::out_of_range("Queue::front, the list is empty");
    }
    return list_.back();
}

template<typename T>
bool Queue<T>::empty() const {
    return list_.empty();
}

template<typename T>
typename Queue<T>::size_type Queue<T>::size() const {
    return list_.size();
}

template<typename T>
void Queue<T>::push(const value_type& value) {
    list_.push_back(value);
}

template<typename T>
void Queue<T>::push(value_type&& value) {
    list_.push_back(std::move(value));
}

template<typename T>
void Queue<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Queue::pop, the list is empty");
    }
    list_.pop_front();
}

template<typename T>
void Queue<T>::swap(Queue& other) {
    LinkedList<T> this_temp = list_;
    list_ = std::move(other.list_);
    other.list_ = this_temp;
}

template<typename T>
bool Queue<T>::operator==(const Queue& other) const {
    // First check if sizes are different
    if (list_.size() != other.list_.size()) {
        return false;
    }
    
    // Compare all elements
    for (size_type i = 0; i < list_.size(); i++) {
        if (list_[i] != other.list_[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Queue<T>::operator!=(const Queue& other) const {
    return !(*this == other);
}

template<typename T>
bool Queue<T>::operator<(const Queue& other) const {
    size_type min_size = std::min(list_.size(), other.list_.size());
    
    for (size_type i = 0; i < min_size; i++) {
        const T& value_1 = list_[i];
        const T& value_2 = other.list_[i];
        
        if (value_1 < value_2) {
            return true;
        }
        if (value_1 > value_2) {
            return false;
        }
    }
    return list_.size() < other.list_.size();
}

template<typename T>
bool Queue<T>::operator<=(const Queue& other) const {
    return !(other < *this);
}

template<typename T>
bool Queue<T>::operator>(const Queue& other) const {
    return other < *this;
}

template<typename T>
bool Queue<T>::operator>=(const Queue& other) const {
    return !(*this < other);
}