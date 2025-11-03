#ifndef STACK_H_
#define STACK_H_
#include <cstddef>
#include <stdexcept>
#include "DoubleLinkedList/LinkedList.h"

template<typename T>
class Stack {
    using value_type = T;
    using size_type = size_t;
    
public:
    // ---- CONSTRUCTORS AND DESTRUCTORS ----
    
    /**
     * Initializes an empty Stack
     */
    Stack();
    
    /**
     * Copy constructor - creates a deep copy of another Stack
     * 
     * ARGS:
     * other: the Stack to be copied
     */
    Stack(const Stack& other);
    
    /**
     * Move constructor - transfers ownership of resources from another Stack
     * 
     * ARGS:
     * other: the Stack to move from (will be left empty)
     */
    Stack(Stack&& other);
    
    /**
     * Destroys the Stack and deallocates all memory
     */
    ~Stack();
    
    /**
     * Copy assignment operator - performs a deep copy of another Stack
     * 
     * ARGS:
     * other: the Stack to be copied
     * 
     * RETURNS:
     * reference to this Stack
     */
    Stack& operator=(const Stack& other);
    
    /**
     * Move assignment operator - transfers ownership of resources from another Stack
     * 
     * ARGS:
     * other: the Stack to move from (will be left empty)
     * 
     * RETURNS:
     * reference to this Stack
     */
    Stack& operator=(Stack&& other);
    
    // ---- STACK OPERATIONS ----
    
    /**
     * Adds an element to the top of the Stack
     * 
     * ARGS:
     * value: the element to be added
     */
    void push(const value_type& value);
    
    /**
     * Removes the element at the top of the Stack
     * 
     * THROWS:
     * std::out_of_range if the Stack is empty
     */
    void pop();
    
    /**
     * Returns a reference to the element at the top of the Stack
     * 
     * RETURNS:
     * reference to the top element
     * 
     * THROWS:
     * std::out_of_range if the Stack is empty
     */
    value_type& top();
    
    /**
     * Returns a const reference to the element at the top of the Stack
     * 
     * RETURNS:
     * const reference to the top element
     * 
     * THROWS:
     * std::out_of_range if the Stack is empty
     */
    const value_type& top() const;
    
    /**
     * Checks if the Stack is empty
     * 
     * RETURNS:
     * true if the Stack is empty, false otherwise
     */
    bool empty() const;
    
    /**
     * Returns the number of elements in the Stack
     * 
     * RETURNS:
     * the size of the Stack
     */
    size_type size() const;

private:
    LinkedList<T> list_;  // Underlying data structure
};

#include "Stack.cpp"
#endif // STACK_H_