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
    value_type val;

    Node(value_type val);

    Node(value_type val, Node* next);
};

template<typename T>
class SingleLinkedList {
    using size_type = size_t;
    using value_type = T;
    public:

    // ---- CONSTRUCTORS ---- //

    /**
     * Initalizes an empty SingleLinkedList
     */
    SingleLinkedList();

    /**
     * Constructs a SingleLinkedList by coping the contents of another vector
     * 
     * ARGS:
     * other: the other singlelinkedlist that will be copied
     */
    SingleLinkedList(const SingleLinkedList& other);

    /**
     * Destroys SingleLinkedList and safely deallocates the allocated memory
     */
    ~SingleLinkedList();

    /**
     * Performs a deep copy of another SingleLinkedList's content
     * 
     * ARGS:
     * other: the other SingleLinkedList that will be copied
     */
    SingleLinkedList& SingleLinkedList(const SingleLinkedList& other);

    // ---- SETTER AND GETTER ---- //

    /**
     * Adds the given value to the front of the SingleLinkedList
     * 
     * ARGS:
     * val: the value that will be added to the front of the linkedlist
     */
    void push_front(value_type val);

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
     * Looks through the entire list and removes all instances of the target
     * 
     * ARGS:
     * the object that will be removed from the linkedlist
     * 
     * RETURNS:
     * true if it removed even one instance, else false
     */
    bool remove(const value_type& target);

    /**
     * looks for the first instance of the given target
     * 
     * ARGS:
     * target: the object to be found
     * 
     * RETURNS:
     * Node* of the target
     */
    Node* find(const value_type& target);

    /**
     * returns the size of the LinkedList
     * 
     * RETURNS:
     * returns the size
     */
    size_type size();

    /**
     * checks if the LinkedList is empty
     * 
     * RETURNS:
     * true if the linkedlist is empty, else false
     */
    bool empty(); 

    /**
     * Returns the value of the node at the front of the linkedlist
     * 
     * RETURNS:
     * the value of the node at the front
     */
    value_type& front();

    /**
     * Returns the value of the node at the end of the linkedlist
     * 
     * RETURNS:
     * Returns the value of the node at the end
     */
    value_type& back();

    // ---- ITERATOR ---- //
    
    class Iterator {
        public:

        Iterator(Node<T>* node);
        bool hasNext();

        value_type next();

        private:
        Node<T>* current_node;

    };

    // ---- OTHER ---- //

    /**
     * Reverses the linkedlist
     */
    void reverse();    

    private:
    Node<T>* head;
    Node<T>* tail;
};

#endif // LINKEDLIST_H_
