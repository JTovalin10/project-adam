#ifndef MINHEAP_H_
#define MINHEAP_H_

#include <cstddef>
#include <stdexcept>
#include "../Vector/Vector.h"

template<typename T>
class MinHeap {
    public:
    using size_type = std::size_t;
    using value_type = T;

    MinHeap();

    MinHeap(const MinHeap& other);

    MinHeap(MinHeap&& other);

    ~MinHeap();

    MinHeap& operator=(const MinHeap& other);

    MinHeap& operator=(MinHeap&& other);

    private:
    Vector<T> list_;
};

template<typename T>
MinHeap<T>::MinHeap() {}

template<typename T>
MinHeap<T>::MinHeap(const MinHeap& other) {
    list_ = other.list_;
}

template<typename T>
MinHeap<T>::MinHeap(MinHeap&& other) {
    list_ = std::move(other.list_);
}

#endif // MINHEAP_H_
