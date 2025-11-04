#ifndef QUEUE_H_
#define QUEUE_H_

#include <cstddef>
#include <stdexcept>

template<typename T>
class Queue {
    using size_type = std::size_t;
    using value_type = T;
    public:

    Queue();

    Queue(const Queue& other);

    Queue(Queue&& other);

    ~Queue();

    Queue& operator=(const Queue& other);

    Queue& operator=(Queue&& other);

    value_type& front();

    const value_type& front() const;

    value_type& back();

    const value_type& back const();

    const bool empty() const;

    size_type size() const;

    // -- MODIFIERS -- //

    void push(value_type& value);

    void empace(value_type& value);

    void pop();

    void swap(Queue&& other);

    // -- comparsions -- //

    bool operator==(const Queue& other);

    bool operator!=(const Queue& other);

    bool operator<(const Queue& other);

    bool operator<=(const Queue& other);

    bool operator>(const Queue& other);

    bool operator>=(const Queue& other);

    
};

#include "Queue.cpp"

#endif // QUEUE_H_
