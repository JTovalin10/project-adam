#ifndef MINHEAP_H_
#define MINHEAP_H_

#include <cstddef>
#include <stdexcept>
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

#endif // MINHEAP_H_
