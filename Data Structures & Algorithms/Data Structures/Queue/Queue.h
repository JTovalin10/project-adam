#ifndef QUEUE_H_
#define QUEUE_H_
#include <cstddef>
#include <stdexcept>
#include "DoubleLinkedList/LinkedList.h"

template<typename T>
class Queue {
using size_type = std::size_t;
using value_type = T;

public:
    /**
     * Constructs an empty Queue
     * 
     * POSTCONDITIONS: empty() == true, size() == 0
     */
    Queue();
    
    /**
     * Copy Constructor - creates a new Queue as a copy of another
     * 
     * EFFECTS: Constructs a Queue with a copy of the contents of 'other'
     * 
     * ARGS:
     * other: the Queue to be copied
     * 
     * POSTCONDITIONS: *this == other, size() == other.size()
     */
    Queue(const Queue& other);
    
    /**
     * Move Constructor - transfers ownership from another Queue
     * 
     * EFFECTS: Constructs a Queue by moving the contents from 'other'.
     *          After this operation, 'other' is left in a valid but
     *          unspecified state (typically empty).
     * 
     * ARGS:
     * other: the Queue that will be moved from
     * 
     * POSTCONDITIONS: *this contains the elements that were in 'other'
     */
    Queue(Queue&& other);
    
    /**
     * Destructor - destroys the Queue and all its elements
     * 
     * EFFECTS: Destroys all elements in the Queue and deallocates
     *          all associated memory
     */
    ~Queue();
    
    /**
     * Copy Assignment Operator - replaces contents with a copy of another Queue
     * 
     * EFFECTS: Replaces the contents of this Queue with a copy of 'other'
     * 
     * ARGS:
     * other: the Queue to be copied
     * 
     * RETURNS: reference to *this
     * 
     * POSTCONDITIONS: *this == other, size() == other.size()
     */
    Queue& operator=(const Queue& other);
    
    /**
     * Move Assignment Operator - replaces contents by moving from another Queue
     * 
     * EFFECTS: Replaces the contents of this Queue by moving from 'other'.
     *          After this operation, 'other' is left in a valid but
     *          unspecified state (typically empty).
     * 
     * ARGS:
     * other: the Queue that will be moved from
     * 
     * RETURNS: reference to *this
     * 
     * POSTCONDITIONS: *this contains the elements that were in 'other'
     */
    Queue& operator=(Queue&& other);
    
    /**
     * Returns a reference to the element at the front of the Queue
     * 
     * THROWS: std::out_of_range if the Queue is empty
     * 
     * RETURNS: reference to the front element
     */
    value_type& front();
    
    /**
     * Returns a const reference to the element at the front of the Queue
     * 
     * THROWS: std::out_of_range if the Queue is empty
     * 
     * RETURNS: const reference to the front element
     */
    const value_type& front() const;
    
    /**
     * Returns a reference to the element at the back of the Queue
     * 
     * THROWS: std::out_of_range if the Queue is empty
     * 
     * RETURNS: reference to the back element
     */
    value_type& back();
    
    /**
     * Returns a const reference to the element at the back of the Queue
     * 
     * THROWS: std::out_of_range if the Queue is empty
     * 
     * RETURNS: const reference to the back element
     */
    const value_type& back() const;
    
    /**
     * Checks if the Queue is empty
     * 
     * RETURNS: true if the Queue is empty, false otherwise
     */
    bool empty() const;
    
    /**
     * Retrieves the size of the Queue
     * 
     * RETURNS: the number of elements in the Queue
     */
    size_type size() const;
    
    // -- MODIFIERS -- //
    
    /**
     * Adds the given element to the end of the Queue by copying
     * 
     * EFFECTS: Inserts a copy of 'value' at the end of the Queue
     * 
     * ARGS:
     * value: the element that will be copied and added to the end of the Queue
     * 
     * POSTCONDITIONS: size() is incremented by 1, back() == value
     */
    void push(const value_type& value);
    
    /**
     * Adds the given element to the end of the Queue by moving
     * Move version - transfers ownership instead of copying.
     * Efficient for large objects (buffers, strings, vectors).
     * 
     * EFFECTS: Constructs an element at the end of the Queue by moving
     *          from 'value'. After this operation, 'value' is left in
     *          a valid but unspecified state.
     * 
     * ARGS:
     * value: rvalue reference to element that will be moved into the Queue
     * 
     * POSTCONDITIONS: size() is incremented by 1
     */
    void push(value_type&& value);
    
    /**
     * Removes the element at the beginning of the Queue
     * 
     * EFFECTS: Removes the front element from the Queue
     * 
     * THROWS: std::out_of_range if the Queue is empty
     * 
     * POSTCONDITIONS: size() is decremented by 1 (if Queue was not empty)
     */
    void pop();
    
    /**
     * Swaps the contents of this Queue with another Queue
     * 
     * EFFECTS: Exchanges the contents of *this with 'other'
     * 
     * ARGS:
     * other: the Queue to swap with
     * 
     * POSTCONDITIONS: *this contains elements that were in 'other',
     *                 'other' contains elements that were in *this
     */
    void swap(Queue& other);
    
    // -- COMPARISONS -- //
    
    /**
     * Equality comparison operator
     * 
     * EFFECTS: Compares the contents of two Queues for equality
     * 
     * ARGS:
     * other: the Queue to compare with
     * 
     * RETURNS: true if both Queues contain the same elements in the same order,
     *          false otherwise
     */
    bool operator==(const Queue& other) const;
    
    /**
     * Inequality comparison operator
     * 
     * EFFECTS: Compares the contents of two Queues for inequality
     * 
     * ARGS:
     * other: the Queue to compare with
     * 
     * RETURNS: true if Queues differ in size or content, false otherwise
     */
    bool operator!=(const Queue& other) const;
    
    /**
     * Less-than comparison operator
     * 
     * EFFECTS: Performs lexicographical comparison
     * 
     * ARGS:
     * other: the Queue to compare with
     * 
     * RETURNS: true if *this is lexicographically less than 'other',
     *          false otherwise
     */
    bool operator<(const Queue& other) const;
    
    /**
     * Less-than-or-equal comparison operator
     * 
     * EFFECTS: Performs lexicographical comparison
     * 
     * ARGS:
     * other: the Queue to compare with
     * 
     * RETURNS: true if *this is lexicographically less than or equal to 'other',
     *          false otherwise
     */
    bool operator<=(const Queue& other) const;
    
    /**
     * Greater-than comparison operator
     * 
     * EFFECTS: Performs lexicographical comparison
     * 
     * ARGS:
     * other: the Queue to compare with
     * 
     * RETURNS: true if *this is lexicographically greater than 'other',
     *          false otherwise
     */
    bool operator>(const Queue& other) const;
    
    /**
     * Greater-than-or-equal comparison operator
     * 
     * EFFECTS: Performs lexicographical comparison
     * 
     * ARGS:
     * other: the Queue to compare with
     * 
     * RETURNS: true if *this is lexicographically greater than or equal to 'other',
     *          false otherwise
     */
    bool operator>=(const Queue& other) const;

private:
    LinkedList<T> list_;
};

#include "Queue.cpp"
#endif // QUEUE_H_