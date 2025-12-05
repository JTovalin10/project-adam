#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <cstddef>
#include <stdexcept>

template <typename T>
class LinkedList {
  using size_type = std::size_t;
  using value_type = T;

 private:
  struct Node;

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
  LinkedList(LinkedList&& other) noexcept;

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
    Iterator(Node* node, Node* tail) : current_node(node), tail_(tail) {}

    /**
     * Checks if the iterator has a next node
     *
     * RETURNS:
     * true if the iterator has progress, else false
     */
    bool hasNext() { return current_node->next != tail_; }

    /**
     * Gets the next value in the list following the iter
     *
     * RETURNS:
     * value_type that is the node->val
     */
    value_type next() {
      current_node = current_node->next;
      return current_node->val;
    }

    /**
     * Function to dereference the iterator mean in a for auto loop
     *
     * RETURNS:
     * returns the node->val
     */
    value_type& operator*() { return current_node->val; }

    /**
     * Function that increments the iter for a for auto loop
     *
     * RETURNS:
     * returns the next iterator in the chain
     */
    Iterator& operator++() {
      current_node = current_node->next;
      return *this;
    }

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
    bool operator!=(const Iterator& other) const {
      return current_node != other.current_node;
    }
    bool operator==(const Iterator& other) const {
      return current_node == other.current_node;
    }

   private:
    Node* current_node;
    Node* tail_;

    friend class ConstIterator;
  };

  class ConstIterator {
   public:
    /**
     * LinkedList Iterator constructor
     *
     * ARGS:
     * node: the node where we are going to start the iterator
     * tail: the end of the linkedlist
     */
    ConstIterator(const Node* node, const Node* tail)
        : current_node(node), tail_(tail) {}

    /**
     * Checks if the iterator has a next node
     *
     * RETURNS:
     * true if the iterator has progress, else false
     */
    bool hasNext() const { return current_node->next != tail_; }

    /**
     * Function to dereference the iterator mean in a for auto loop
     *
     * RETURNS:
     * returns the node->val
     */
    const value_type& operator*() const { return current_node->val; }

    /**
     * Function that increments the iter for a for auto loop
     *
     * RETURNS:
     * returns the next iterator in the chain
     */
    ConstIterator& operator++() {
      current_node = current_node->next;
      return *this;
    }

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
    bool operator!=(const ConstIterator& other) const {
      return current_node != other.current_node;
    }
    bool operator==(const ConstIterator& other) const {
      return current_node == other.current_node;
    }

   private:
    const Node* current_node;
    const Node* tail_;
    friend class Iterator;
  };

  /**
   * looks for the first instance of the given target
   *
   * ARGS:
   * target: the object to be found
   *
   * RETURNS:
   * if the target is found it will return Node*, else nullptr
   */
  Iterator find(const value_type& target);

  /**
   * looks for the first instance of the given target
   *
   * ARGS:
   * target: the object to be found
   *
   * RETURNS:
   * if the target is found it will return Node*, else nullptr
   */
  ConstIterator find(const value_type& target) const;

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
  /**
   * Initalizes the start of the iterator by returning the start of
   * the linkedlist
   *
   * RETURNS:
   * Iterator which points to the start of the LinkedList
   */
  Iterator begin();
  ConstIterator begin() const;
  ConstIterator cbegin() const;

  /**
   * Defines the end of the iterator so we have a end point
   *
   * RETURNS:
   * Iterator which points to the end of the LinkedList
   */
  Iterator end();
  ConstIterator end() const;
  ConstIterator cend() const;

  // ---- OTHER ---- //

  /**
   * Reverses the linkedlist
   */
  void reverse();

 private:
  struct Node {
    value_type val;
    Node* prev;
    Node* next;

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
    Node(value_type val, Node* prev, Node* next);
  };

  Node* head_;
  Node* tail_;
  size_type size_;
};

// Template member function implementations
// Following Google C++ Style Guide: template implementations belong in header

template <typename T>
LinkedList<T>::Node::Node(typename LinkedList<T>::value_type val)
    : val(val), prev(nullptr), next(nullptr) {}

template <typename T>
LinkedList<T>::Node::Node(typename LinkedList<T>::value_type val, Node* prev,
                          Node* next)
    : val(val), prev(prev), next(next) {}

template <typename T>
LinkedList<T>::LinkedList() : size_(0) {
  head_ = new Node(T());
  tail_ = new Node(T());
  head_->next = tail_;
  tail_->prev = head_;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : size_(other.size_) {
  head_ = new Node(T());
  tail_ = new Node(T());
  head_->next = tail_;
  tail_->prev = head_;
  Node* this_curr = head_;
  Node* other_curr = other.head_->next;
  while (other_curr != other.tail_) {
    this_curr->next = new Node(other_curr->val, this_curr, nullptr);
    this_curr = this_curr->next;
    other_curr = other_curr->next;
  }
  this_curr->next = tail_;
  tail_->prev = this_curr;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
  other.head_ = new Node(T());
  other.tail_ = new Node(T());
  other.head_->next = other.tail_;
  other.tail_->prev = other.head_;
  other.size_ = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
  Node* curr = head_->next;
  while (curr != tail_) {
    Node* nextCurr = curr->next;
    delete curr;
    curr = nextCurr;
  }
  delete head_;
  delete tail_;
}

template <typename T>
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
  tail_->prev = head_;
  Node* this_curr = head_;
  Node* other_curr = other.head_->next;
  while (other_curr != other.tail_) {
    this_curr->next = new Node(other_curr->val, this_curr, nullptr);
    this_curr = this_curr->next;
    other_curr = other_curr->next;
  }
  this_curr->next = tail_;
  tail_->prev = this_curr;
  size_ = other.size_;
  return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) {
  if (this == &other) {
    return *this;
  }
  Node* curr = head_;
  while (curr != tail_) {
    Node* temp = curr->next;
    delete curr;
    curr = temp;
  }
  delete head_;
  delete tail_;

  head_ = other.head_;
  tail_ = other.tail_;
  size_ = other.size_;
  other.head_ = new Node(T());
  other.tail_ = new Node(T());
  other.head_->next = other.tail_;
  other.tail_->prev = other.head_;
  other.size_ = 0;
  return *this;
}

template <typename T>
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

template <typename T>
const typename LinkedList<T>::value_type& LinkedList<T>::operator[](
    size_type index) const {
  if (index >= size_) {
    throw std::out_of_range("LinkedList::operator[], index is out of range");
  }
  size_type i = 0;
  const Node* curr = head_->next;
  while (curr != tail_) {
    if (i == index) {
      return curr->val;
    }
    curr = curr->next;
    i++;
  }
  throw std::out_of_range("LinkedList::operator[], index is out of range");
}

template <typename T>
void LinkedList<T>::push_front(const value_type& val) {
  Node* old_head = head_->next;
  Node* new_node = new Node(val);
  old_head->prev = new_node;
  new_node->next = old_head;
  new_node->prev = head_;
  head_->next = new_node;
  size_++;
}

template <typename T>
void LinkedList<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("LinkedList::pop_front, the linked list is empty");
  }
  Node* old_head = head_->next;
  Node* new_head = old_head->next;
  head_->next = new_head;
  new_head->prev = head_;
  delete old_head;
  size_--;
}

template <typename T>
void LinkedList<T>::push_back(const value_type& val) {
  Node* old_last = tail_->prev;
  Node* new_node = new Node(val, old_last, tail_);
  old_last->next = new_node;
  tail_->prev = new_node;
  size_++;
}

template <typename T>
void LinkedList<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("LinkedList::pop_back, The LinkedList is empty");
  }
  Node* old_last = tail_->prev;
  Node* new_last = old_last->prev;
  new_last->next = tail_;
  tail_->prev = new_last;
  delete old_last;
  size_--;
}

template <typename T>
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
    Node* next_node = curr->next;
    Node* new_node = new Node(val, curr, curr->next);
    curr->next = new_node;
    next_node->prev = new_node;
    size_++;
  }
}

template <typename T>
void LinkedList<T>::erase(size_type index) {
  if (empty() || index >= size_) {
    throw std::out_of_range(
        "LinkedList::erase, the LinkedList is empty or index is out of range");
  }
  Node* curr = head_->next;
  size_type i = 0;
  while (curr != tail_ && i < index) {
    curr = curr->next;
    i++;
  }
  Node* prev_node = curr->prev;
  Node* next_node = curr->next;
  prev_node->next = next_node;
  next_node->prev = prev_node;
  delete curr;
  size_--;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::find(const value_type& target) {
  Node* curr = head_->next;
  while (curr != tail_) {
    if (curr->val == target) {
      return Iterator(curr, tail_);
    }
    curr = curr->next;
  }
  return end();
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::find(
    const value_type& target) const {
  const Node* curr = head_->next;
  while (curr != tail_) {
    if (curr->val == target) {
      return ConstIterator(curr, tail_);
    }
    curr = curr->next;
  }
  return cend();
}

template <typename T>
typename LinkedList<T>::size_type LinkedList<T>::size() const {
  return size_;
}

template <typename T>
bool LinkedList<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename LinkedList<T>::value_type& LinkedList<T>::front() {
  if (empty()) {
    throw std::out_of_range("LinkedList::front, the LinkedList is empty");
  }
  return head_->next->val;
}

template <typename T>
const typename LinkedList<T>::value_type& LinkedList<T>::front() const {
  if (empty()) {
    throw std::out_of_range("LinkedList::front, the LinkedList is empty");
  }
  return head_->next->val;
}

template <typename T>
typename LinkedList<T>::value_type& LinkedList<T>::back() {
  if (empty()) {
    throw std::out_of_range("LinkedList::back, the LinkedList is empty");
  }
  return tail_->prev->val;
}

template <typename T>
const typename LinkedList<T>::value_type& LinkedList<T>::back() const {
  if (empty()) {
    throw std::out_of_range("LinkedList::back, the LinkedList is empty");
  }
  return tail_->prev->val;
}
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
  return Iterator(head_->next, tail_);
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::begin() const {
  return ConstIterator(head_->next, tail_);
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::cbegin() const {
  return ConstIterator(head_->next, tail_);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
  return Iterator(tail_, tail_);
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::end() const {
  return ConstIterator(tail_, tail_);
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::cend() const {
  return ConstIterator(tail_, tail_);
}

template <typename T>
void LinkedList<T>::reverse() {
  Node* curr = head_;
  while (curr != nullptr) {
    Node* temp = curr->next;
    curr->next = curr->prev;
    curr->prev = temp;
    curr = temp;
  }
  Node* old_head = head_;
  head_ = tail_;
  tail_ = old_head;
}

#endif  // LINKEDLIST_H_
