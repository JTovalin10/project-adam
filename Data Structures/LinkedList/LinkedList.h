#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <cstddef>
#include <stdexcept>

template<typename T>
class LinkedList {
    using size_type = std::size_t;
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
     * Move constructor - transfers ownership of resources
     * 
     * ARGS:
     * other: the LinkedList to move from (will be left empty)
     */
    LinkedList(LinkedList&& other);

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

    /**
     * Move assignment operator - transfers ownership of resources
     * 
     * ARGS:
     * other: the LinkedList to move from (will be left empty)
     */
    LinkedList& operator=(LinkedList&& other);

    /**
     * bracket operator - retrieves the value at given index
     * 
     * ARGS:
     * index: the index of the element in the list
     * 
     * THROWS:
     * std::out_of_range if index >= size
     * 
     * RETURNS:
     * the value of the given element
     */
    value_type& operator[](size_type index);

    /**
     * const bracket operator - retrieves the value at given index
     * 
     * ARGS:
     * index: the index of the element in the list
     * 
     * THROWS:
     * std::out_of_range if index >= size
     * 
     * RETURNS:
     * the const value of the given element
     */
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
    Node* find(const value_type& target);

        /**
     * looks for the first instance of the given target
     * 
     * ARGS:
     * target: the object to be found
     * 
     * RETURNS:
     * if the target is found it will return Node*, else nullptr
     */
    const Node* find(const value_type& target) const;

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
        Iterator(Node* node, Node* tail);

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
        Node* current_node;
        Node* tail_;

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
    struct Node {
        Node* next;
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
         * next: points to the next Node
         */
        Node(value_type val, Node* next);
    };

    Node* head_;
    Node* tail_;
    size_type size_;
};

// Template member function implementations
// Following Google C++ Style Guide: template implementations belong in header

template<typename T>
LinkedList<T>::Node::Node(typename LinkedList<T>::value_type val) : val(val), next(nullptr) {}

template<typename T>
LinkedList<T>::Node::Node(typename LinkedList<T>::value_type val, Node* next) : val(val), next(next) {}

template<typename T>
LinkedList<T>::LinkedList() : size_(0) {
    head_ = new Node(T());
    tail_ = new Node(T());
    head_->next = tail_;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : size_(other.size_) {
    head_ = new Node(T());
    tail_ = new Node(T());
    head_->next = tail_;
    Node* thisCurr = head_;
    Node* otherCurr = other.head_->next;
    while (otherCurr != other.tail_) {
        thisCurr->next = new Node(otherCurr->val);
        thisCurr = thisCurr->next;
        otherCurr = otherCurr->next;
    }
    thisCurr->next = tail_;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList&& other) : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = new Node(T());
    other.tail_ = new Node(T());
    other.head_->next = other.tail_;
    other.size_ = 0;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node* curr = head_;
    while (curr != nullptr) {
        Node* nextCurr = curr->next;
        delete curr;
        curr = nextCurr;
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this == &other) {
        return *this;
    }
    Node* curr = head_->next;
    while (curr != tail_) {
        Node* temp = curr->next;
        delete curr;
        curr = temp;
    }
    head_->next = tail_;
    Node* thisCurr = head_;
    Node* otherCurr = other.head_->next;
    while (otherCurr != other.tail_) {
        thisCurr->next = new Node(otherCurr->val);
        thisCurr = thisCurr->next;
        otherCurr = otherCurr->next;
    }
    thisCurr->next = tail_;
    size_ = other.size_;
    return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) {
    if (this == &other) {
        return *this;
    }
    Node* curr = head_;
    while (curr != nullptr) {
        Node* temp = curr->next;
        delete curr;
        curr = temp;
    }
    size_ = other.size_;
    head_ = other.head_;
    tail_ = other.tail_;
    other.head_ = new Node(T());
    other.tail_ = new Node(T());
    other.head_->next = other.tail_;
    other.size_ = 0;
    return *this;
}

template<typename T>
typename LinkedList<T>::value_type& LinkedList<T>::operator[](size_type index) {
    if (index >= size_) {
        throw std::out_of_range("LinkedList::operator[], index is out of range");
    }
    size_type i = 0;
    Node* curr = head_->next;
    while (curr != tail_) {
        if (i == index) {
            return curr->val;
        }
        curr = curr->next;
        i++;
    }
    throw std::out_of_range("LinkedList::operator[], index is out of range");
}

template<typename T>
const typename LinkedList<T>::value_type& LinkedList<T>::operator[](size_type index) const {
    if (index >= size_) {
        throw std::out_of_range("LinkedList::operator[], index is out of range");
    }
    size_type i = 0;
    Node* curr = head_->next;
    while (curr != tail_) {
        if (i == index) {
            return curr->val;
        }
        curr = curr->next;
        i++;
    }
    throw std::out_of_range("LinkedList::operator[], index is out of range");
}

template<typename T>
void LinkedList<T>::push_front(const value_type& val) {
    Node* newNode = new Node(val, head_->next);
    head_->next = newNode;
    size_++;
}

template<typename T>
void LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("LinkedList::pop_front, the linked list is empty");
    }
    Node* oldHead = head_->next;
    Node* newHead = oldHead->next;
    head_->next = newHead;
    delete oldHead;
    size_--;
}

template<typename T>
void LinkedList<T>::push_back(const value_type& val) {
    Node* newNode = new Node(val, tail_);
    Node* curr = head_;
    while (curr->next != tail_) {
        curr = curr->next;
    }
    curr->next = newNode;
    size_++;
}

template<typename T>
void LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("LinkedList::pop_back, The LinkedList is empty");
    }
    Node* curr = head_;
    Node* prev = nullptr;
    while (curr->next != tail_) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = tail_;
    delete curr;
    size_--;
}

template<typename T>
void LinkedList<T>::insert(const value_type& val, size_type index) {
    if (index > size_) {
        throw std::out_of_range("LinkedList::insert, index is out of range");
    }
    if (index == 0) {
        push_front(val);
    } else {
        Node* curr = head_;
        size_type i = 0;
        while (curr->next != tail_ && i < index) {
            curr = curr->next;
            i++;
        }
        Node* newNode = new Node(val, curr->next);
        curr->next = newNode;
        size_++;
    }
}

template<typename T>
void LinkedList<T>::erase(size_type index) {
    if (empty() || index >= size_) {
        throw std::out_of_range("LinkedList::erase, the LinkedList is empty or index is out of range");
    }
    Node* curr = head_->next;
    Node* prev = head_;
    size_type i = 0;
    while (curr != tail_ && i < index) {
        prev = curr;
        curr = curr->next;
        i++;
    }
    prev->next = curr->next;
    delete curr;
    size_--;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::find(const value_type& target) {
    Node* curr = head_->next;
    while (curr != tail_) {
        if (curr->val == target) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::find(const value_type& target) const {
    const Node* curr = head_->next;
    while (curr != tail_) {
        if (curr->val == target) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

template<typename T>
typename LinkedList<T>::size_type LinkedList<T>::size() const {
    return size_;
}

template<typename T>
bool LinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
typename LinkedList<T>::value_type& LinkedList<T>::front() {
    if (empty()) {
        throw std::out_of_range("LinkedList::front, the LinkedList is empty");
    }
    return head_->next->val;
}

template<typename T>
const typename LinkedList<T>::value_type& LinkedList<T>::front() const {
    if (empty()) {
        throw std::out_of_range("LinkedList::front, the LinkedList is empty");
    }
    return head_->next->val;
}

template<typename T>
typename LinkedList<T>::value_type& LinkedList<T>::back() {
    if (empty()) {
        throw std::out_of_range("LinkedList::back, the LinkedList is empty");
    }
    Node* curr = head_->next;
    while (curr->next != tail_) {
        curr = curr->next;
    }
    return curr->val;
}

template<typename T>
const typename LinkedList<T>::value_type& LinkedList<T>::back() const {
    if (empty()) {
        throw std::out_of_range("LinkedList::back, the LinkedList is empty");
    }
    const Node* curr = head_->next;
    while (curr->next != tail_) {
        curr = curr->next;
    }
    return curr->val;
}

template<typename T>
LinkedList<T>::Iterator::Iterator(Node* node, Node* tail) : current_node(node), tail_(tail) {}

template<typename T>
typename LinkedList<T>::value_type& LinkedList<T>::Iterator::operator*() {
    return current_node->val;
}

template<typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() {
    current_node = current_node->next;
    return *this;
}

template<typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& other) const {
    return current_node != other.current_node;
}

template<typename T>
bool LinkedList<T>::Iterator::hasNext() {
    if (current_node->next == tail_) {
        return false;
    } else {
        return true;
    }
}

template<typename T>
typename LinkedList<T>::value_type LinkedList<T>::Iterator::next() {
    current_node = current_node->next;
    return current_node->val;
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
    return Iterator(head_->next, tail_);
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
    return Iterator(tail_, tail_);
}

template<typename T>
void LinkedList<T>::reverse() {
    Node* prev = head_;
    Node* curr = head_->next;
    Node* next = nullptr;
    while (curr != tail_) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head_->next = tail_;
    tail_->next = prev;
    Node* temp = head_;
    head_ = tail_;
    tail_ = temp;
}

#endif // LINKEDLIST_H_