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

  CGStack& operator=(const CGStack& other) {
    if (this != &other) {
      Node* curr = head_;
      while (curr != tail_) {
        Node* temp = curr->next;
        delete curr;
        curr = temp;
      }
      delete tail_;
    }
    return *this;
  }

  CGStack& operator=(CGStack&& other) = delete;

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

  Node* old_head = head_->next;
  new_node->next = old_head;
  head_->next = new_node;
}

template <typename T>
std::shared_ptr<T> CGStack<T>::pop() {
  std::lock_guard<std::shared_mutex> lock(mtx_);
  // if empty
  if (head_->next != tail_) {
    Node* item = head_->next;

    // remove it from the LL
    head_->next = item->next;
    T data = item->data;
    delete item;
    return std::make_shared<T>(data);
  }
  return nullptr;
}

template <typename T>
std::shared_ptr<T> CGStack<T>::peek() const {
  std::shared_lock<std::shared_mutex> lock(mtx_);
  // if empty
  if (head_->next != tail_) {
    return std::make_shared<T>(head_->next->data);
  }
  return nullptr;
}

#endif  // CGSTACK_H_
