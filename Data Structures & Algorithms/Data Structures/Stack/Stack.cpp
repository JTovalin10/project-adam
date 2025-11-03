#include "Stack.h"

template<typename T>
Stack<T>::Stack() {}

template<typename T>
Stack<T>::Stack(const Stack& other) {
    list_ = other.list_;
}

template<typename T>
Stack<T>::Stack(Stack&& other) {
    list_ = std::move(other.list_);
}

template<typename T>
Stack<T>::~Stack() {}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this == &other) {
        return *this;
    }
    list_ = other.list_;
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) {
    if (this == &other) {
        return *this;
    }
    list_ = std::move(other.list_);
    return *this;
}

template<typename T>
void Stack<T>::push(const value_type& value) {
    list_.push_back(value);
}

template<typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Stack::pop, the stack is empty");
    }
    list_.pop_back();
}

template<typename T>
typename Stack<T>::value_type& Stack<T>::top() {
    if (empty()) {
        throw std::out_of_range("Stack::top, the stack is empty");
    }
    return list_.back();
}

template<typename T>
const typename Stack<T>::value_type& Stack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Stack::top, the stack is empty");
    }
    return list_.back();
}

template<typename T>
bool Stack<T>::empty() const {
    return list_.empty();
}

template<typename T>
typename Stack<T>::size_type Stack<T>::size() const {
    return list_.size();
}