#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <cstddef>
#include <stdexcept>

using size_type = std::size_t;

template<typename T>
class Node {
    using value_type = T;
    public:
    Node<T>* next;
    Node<T>* prev;
    value_type val;

    /**
     * Initalizes a Node with only a value
     * 
     * ARGS:
     * val: the value of the node
     */
    Node(value_type val);

    /**
     * Initalizes a Node with only a value
     * 
     * ARGS:
     * val: the value of the node
     * prev: points to the previous Node
     * next: points to the next Node
     */
    Node(value_type val, Node<T>* prev, Node<T>* next);
};

template<typename T>
class LinkedList {
    using size_type = size_t;
    using value_type = T;
    public:

    // ---- CONSTRUCTORS ---- //

    /**
     * Initalizes an empty LinkedList
     */
    LinkedList();

    /**
     * Constructs a LinkedList by coping the contents of another vector
     * 
     * ARGS:
     * other: the other LinkedList that will be copied
     */
    LinkedList(const LinkedList& other);

    /**
     * Destroys LinkedList and safely deallocates the allocated memory
     */
    ~LinkedList();

    /**
     * Performs a deep copy of another LinkedList's content
     * 
     * ARGS:
     * other: the other LinkedList that will be copied
     */
    LinkedList& operator=(const LinkedList& other);

    value_type& operator[](size_type index);

    const value_type& operator[](size_type index) const;

    // ---- SETTER AND GETTER ---- //

    /**
     * Adds the given value to the front of the LinkedList
     * 
     * ARGS:
     * val: the value that will be added to the front of the linkedlist
     */
    void push_front(const value_type& val);

    /**
     * removes the element that is at the front of the LinkedList
     * 
     * THROWS:
     * std::out_of_bounds if the LinkedList is empty
     */
    void pop_front();

    /**
     * Adds the given element to the end of the LinkedList
     * 
     * ARGS:
     * val: the value that we are going to add to the end of the LinkedList
     */
    void push_back(const value_type& val);

    /**
     * Removes the element at the end of the LinkedList
     */
    void pop_back();

    /**
     * Adds the given element to the given index and shifts all the other elements
     * to the right
     * 
     * ARGS:
     * val: the value that we are going to add to the LinkedList
     * index: the index where we are going to add it
     * 
     * THROWS:
     * out_of_bounds if index is not within 0<=index<=size()
     */
    void insert(const value_type& val, size_type index);

    /**
     * Removes the element at the given index
     * 
     * ARGS:
     * index: the position of the element that will be removed
     * 
     * THROWS:
     * out_of_bounds if the index is not within 0 <= index <= size()
     */
    void erase(size_type index);

    /**
     * looks for the first instance of the given target
     * 
     * ARGS:
     * target: the object to be found
     * 
     * RETURNS:
     * if the target is found it will return Node*, else nullptr
     */
    Node<value_type>* find(const value_type& target);

        /**
     * looks for the first instance of the given target
     * 
     * ARGS:
     * target: the object to be found
     * 
     * RETURNS:
     * if the target is found it will return Node*, else nullptr
     */
    const Node<value_type>* find(const value_type& target) const;

    /**
     * returns the size of the LinkedList
     * 
     * RETURNS:
     * returns the size
     */
    size_type size() const;

    /**
     * checks if the LinkedList is empty
     * 
     * RETURNS:
     * true if the linkedlist is empty, else false
     */
    bool empty() const; 

    /**
     * Returns the value of the node at the front of the linkedlist
     * 
     * RETURNS:
     * the value of the node at the front
     * 
     * THROWS:
     * std::out_of_range if the list is empty
     */
    value_type& front();

    /**
     * Returns the value of the node at the front of the linkedlist
     * 
     * RETURNS:
     * the value of the node at the front
     * 
     * THROWS:
     * std::out_of_range if the list is empty
     */
    const value_type& front() const;

    /**
     * Returns the value of the node at the end of the linkedlist
     * 
     * RETURNS:
     * Returns the value of the node at the end
     * 
     * THROWS:
     * std::out_of_range if the list is empty
     */
    value_type& back();

    /**
     * Returns the value of the node at the end of the linkedlist
     * 
     * RETURNS:
     * Returns the value of the node at the end
     * 
     * THROWS:
     * std::out_of_range if the list is empty
     */
    const value_type& back() const;

    // ---- ITERATOR ---- //
    
    class Iterator {
        public:

        /**
         * LinkedList Iterator constructor
         * 
         * ARGS:
         * node: the node where we are going to start the iterator
         * tail: the end of the linkedlist
         */
        Iterator(Node<T>* node, Node<T>* tail);

        /**
         * Checks if the iterator has a next node
         * 
         * RETURNS:
         * true if the iterator has progress, else false
         */
        bool hasNext();

        /**
         * Gets the next value in the list following the iter
         * 
         * RETURNS:
         * value_type that is the node->val
         */
        value_type next();

        /**
         * Function to dereference the iterator mean in a for auto loop
         * 
         * RETURNS:
         * returns the node->val
         */
        value_type& operator*();

        /**
         * Function that increments the iter for a for auto loop
         * 
         * RETURNS:
         * returns the next iterator in the chain
         */
        Iterator& operator++();

        /**
         * comparsion check for for loop
         * 
         * PARAM:
         * other: the other Iterator we are comparing against to ensure
         * they are not the same
         * 
         * RETURNS:
         * if they are not the same returns true, else false
         */
        bool operator!=(const Iterator& other) const; 

        private:
        Node<T>* current_node;
        Node<T>* tail_;

    };

    /**
     * Initalizes the start of the iterator by returning the start of
     * the linkedlist
     * 
     * RETURNS:
     * Iterator which points to the start of the LinkedList
     */
    Iterator begin();

    /**
     * Defines the end of the iterator so we have a end point
     * 
     * RETURNS:
     * Iterator which points to the end of the LinkedList
     */
    Iterator end();

    // ---- OTHER ---- //

    /**
     * Reverses the linkedlist
     */
    void reverse();    

    private:
    Node<T>* head_;
    Node<T>* tail_;
};

#include "LinkedList.cpp"

#endif // LINKEDLIST_H_
