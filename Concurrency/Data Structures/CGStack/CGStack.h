#ifndef CGSTACK_H_
#define CGSTACK_H_

#include <cstddef>
#include <memory>
#include <mutex>
#include <shared_mutex>

template <typename T>
class CGStack {
  using type_name = T;

 public:
  CGStack();

  CGStack(const CGStack& other) = delete;

  CGStack(CGStack&& other) noexcept;

  ~CGStack();

  CGStack& operator=(const CGStack& other) = delete;

  CGStack& operator=(CGStack&& other) noexcept {
    std::unique_lock<std::shared_mutex> lock(other.mtx_);
    if (this != &other) {
      Node* curr = head_->next;
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

  void push(T item);

  std::shared_ptr<T> pop();

  std::shared_ptr<T> peek() const;

 private:
  struct Node {
    Node* next = nullptr;
    type_name data;

    Node() : data(T()) {};

    explicit Node(type_name data) : data(std::move(data)) {};
  };

  bool unsafe_empty() const { return head_->next == tail_; }

  Node* head_ = new Node();
  Node* tail_ = new Node();
  mutable std::shared_mutex mtx_;
};

template <typename T>
CGStack<T>::CGStack() {
  head_->next = tail_;
}

template <typename T>
CGStack<T>::CGStack(CGStack&& other) noexcept {
  std::lock_guard<std::shared_mutex> lock(other.mtx_);
  // set these head and tail to the others
  head_ = other.head_;
  tail_ = other.tail_;

  other.head_ = nullptr;
  other.tail_ = nullptr;
}

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

  // grab the old head
  Node* old_head = head_->next;
  // set the new nodes next to the old head [new_node -> old_head]
  new_node->next = old_head;
  // make the next of the current head the new node [head_ -> new_node ->
  // old_head]
  head_->next = new_node;
}

template <typename T>
std::shared_ptr<T> CGStack<T>::pop() {
  std::lock_guard<std::shared_mutex> lock(mtx_);
  // if empty
  if (unsafe_empty()) {
    return nullptr;
  }
  Node* item = head_->next;
  std::shared_ptr<T> res = std::make_shared<T>(std::move(item->data));
  // if the make_shared did not throw then we remove from the LL
  head_->next = item->next;
  delete item;
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

#endif  // CGSTACK_H_
