#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <cstddef>        // for std::size_t
#include <stdexcept>      // for std::out_of_range (throws)

template<typename T>
class Node {
    public:
    using value_type = T;

    T val;
    Node<T>* next = nullptr;
    Node<T>* prev = nullptr;

    Node(value_type val);

    Node(value_type val, Node<value_type>* prev, Node<value_type>* next);
};

template<typename T>
class LinkedList {
    public:
    using value_type = T;
    using size_type = std::size_t;
    using Iterator = Node<T>*;

    // -- Constructors and de -- //
    LinkedList();

    ~LinkedList();

    LinkedList(const LinkedList& other);

    LinkedList& LinkedList(const LinkedList& other);

    void push_front(const value_type& val);

    void pop_front();

    void push_back();

    void pop_back();

    void insert(const value_type& val, size_type index);

    void deleteAt(size_type index);

    Node<T>* find(const value_type& val);

    size_type size();

    bool empty();

    value_type& front();

    value_type& back();

    class Iterator {
        public:

        Iterator(Node<T>* front, Node<T>* end);

        Iterator next();

        bool hasNext();

        private:
        Node<T>* head_;
        Node<T>* tail_;
    };

    void reverse();

    private:
    Node<T>* head_;
    Node<T>* prev_;
    size_type size_;
};

#include "LinkedList.h";

#endif // LINKEDLIST_H_