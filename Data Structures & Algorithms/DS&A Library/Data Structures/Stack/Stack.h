#ifndef STACK_H_
#define STACK_H_

#include <cstddef>
#include <stdexcept>
#include "DoubleLinkedList/LinkedList.h"

template<typename T>
class Stack {
    using value_type = T;
    using size_type = size_t;

    // ---- CONSTRUCTORS AND DESTRUCTORS
    Stack();

    ~Stack();

    Stack(const value_type& other);

    Stack& operator=(const Stack& other);

    Stack(Stack&& other);

    Stack& operator=(Stack&& other);

    void push(const value_type& value);

    void pop();

    value_type& top();

    const value_type& top() const;

    bool empty() const;

    size_type size() const;


    private:
    LinkedList<T> list_;
    size_type size_;
};

#include "Stack.cpp"

#endif // STACK_H_