#ifndef CGSTACK_H_
#define CGSTACK_H_

#include <condition_variable>
#include <cstddef>
#include <memory>
#include <mutex>
#include <new>
#include <shared_mutex>

template <typename T>
class CGStack {
  using type_name = T;

 public:
  /**
   * Default Constructor that links the head and tail
   */
  CGStack() { head_->next = tail_; }

  CGStack(const CGStack& other) = delete;

  /**
   * Move Constructor that steals the head and tail pointer from the other
   * CGStack
   *
   * ARGS:
   * other: rvalue CGStack
   */
  CGStack(CGStack&& other) noexcept {
    if (this != &other) {
      std::scoped_lock lock(mtx_, other.mtx_);
      head_ = other.head_;
      tail_ = other.tail_;

      other.head_ = nullptr;
      other.tail_ = nullptr;
    }
  }

  /**
   * Deconstructor that deallocates nodes
   */
  ~CGStack();

  CGStack& operator=(const CGStack& other) = delete;

  /**
   * move assignment operaotr which deallocates and then steals from other
   *
   * ARGS:
   * other: rvalue CGStack
   *
   * RETURNS:
   * this: ptr reference to this object
   */
  CGStack& operator=(CGStack&& other) noexcept {
    if (this != &other) {
      std::scoped_lock lock(mtx_, other.mtx_);
      Node* curr = head_;
      while (curr != tail_) {
        Node* temp = curr->next;
        delete curr;
        curr = temp;
      }
      delete tail_;

      head_ = other.head_;
      tail_ = other.tail_;

      other.head_ = nullptr;
      other.tail_ = nullptr;
    }
    return *this;
  }

  /**
   * adds an item to the stack
   *
   * ARGS:
   * item: element to be added to the top of the stack of type T
   */
  void push(T item);

  /**
   * removes the element from the top of the stack and returns it
   *
   * RETURNS:
   * shared_ptr with the element that was at the top of the stack, if the stack
   * was empty then the shared_ptr contains a nullptr
   */
  std::shared_ptr<T> pop();

  /**
   * Removes the element from tjhe top of the stack and returns it, if the stack
   * is empty then it will wait until it is not empty
   *
   * RETURNS:
   * shared_ptr that is guarentted to contain an element of type T
   */
  std::shared_ptr<T> wait_and_pop();

  /**
   * Looks at the top of the stack and returns what is there
   *
   * RETURNS:
   * returns a shared_ptr that contains the element at the top of the stack, if
   * the stack is empty, returns a nullptr
   */
  std::shared_ptr<T> peek() const;

  /**
   * Looks at the top of the stack adn returns the element at the top, if the
   * stack is empty then it waits until its not empty
   *
   * RETURNS:
   * returns a shared_ptr that is guranteed to contain the element at the top of
   * the stack
   */
  std::shared_ptr<T> wait_and_peek() const;

 private:
  struct Node {
    Node* next = nullptr;
    type_name data;

    Node() : data(T()) {};

    explicit Node(type_name data) : data(std::move(data)) {};
  };

  /*
   * Helper function that checks if the stack is empty. IMPORTANT: it does not
   * lock
   *
   * RETURNS:
   * true if the stack is empty, false if not
   */
  bool unsafe_empty() const { return head_->next == tail_; }

  /**
   * Helper functin that checks if the stack is not empty. IMPORTANT: it does
  not lock
   *
   * RETURNS:
   * true if the stack is not empty, otherwise it returns false
   */
  bool unsafe_not_empty() const { return head_->next != tail_; }

  /**
   * removes a node from the linkedlist
   *
   * ARGS:
   * node_to_keep: parent node of node_to_remove that is used to maintain the
  structure of the linkedlist
   * node_to_remove: the node that will be removed from the linkedlist
   */
  void unsafe_remove_node(Node* node_to_keep, Node* node_to_remove) noexcept {
    node_to_keep->next = node_to_remove->next;
    delete node_to_remove;
  }

  /**
   * adds a node to the linkedlist
   *
   * ARGS:
   * new_node: Node that will be added to the head of hte stack
   */
  void unsafe_add_node(Node* new_node) {
    Node* old_head = head_->next;
    new_node->next = old_head;
    head_->next = new_node;
  }

  Node* head_ = new Node();
  Node* tail_ = new Node();
  mutable std::shared_mutex mtx_;
  mutable std::condition_variable_any cv_;
};

template <typename T>
CGStack<T>::~CGStack() {
  Node* temp = head_;
  while (temp != tail_) {
    Node* next_temp = temp->next;
    delete temp;
    temp = next_temp;
  }
  delete tail_;
}

template <typename T>
void CGStack<T>::push(type_name item) {
  std::lock_guard<std::shared_mutex> lock(mtx_);
  Node* new_node = new Node(std::move(item));

  unsafe_add_node(new_node);
  cv_.notify_all();
}

template <typename T>
std::shared_ptr<T> CGStack<T>::pop() {
  std::lock_guard<std::shared_mutex> lock(mtx_);
  if (unsafe_empty()) {
    return nullptr;
  }
  Node* node_to_remove = head_->next;
  std::shared_ptr<T> res = std::make_shared<T>(std::move(node_to_remove->data));
  // if the make_shared did not throw then we remove from the LL
  unsafe_remove_node(head_, node_to_remove);
  return res;
}

template <typename T>
std::shared_ptr<T> CGStack<T>::wait_and_pop() {
  std::unique_lock<std::shared_mutex> lock(mtx_);
  cv_.wait(lock, [this] { return unsafe_not_empty(); });
  Node* node_to_remove = head_->next;
  std::shared_ptr<T> res = std::make_shared<T>(std::move(node_to_remove->data));
  unsafe_remove_node(head_, node_to_remove);
  return res;
}

template <typename T>
std::shared_ptr<T> CGStack<T>::peek() const {
  std::shared_lock<std::shared_mutex> lock(mtx_);
  // if empty
  if (unsafe_empty()) {
    return nullptr;
  }
  return std::make_shared<T>(head_->next->data);
}

template <typename T>
std::shared_ptr<T> CGStack<T>::wait_and_peek() const {
  std::unique_lock<std::shared_mutex> lock(mtx_);
  cv_.wait(lock, [this] { return unsafe_not_empty(); });
  return std::make_shared<T>(head_->next->data);
}

#endif  // CGSTACK_H_
