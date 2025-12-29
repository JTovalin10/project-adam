#ifndef LFSTACK_H_
#define LFSTACK_H_

#include <atomic>
#include <memory>

template <typename T>
class LFStack {
  using type_name = T;

 public:
  LFStack() = default;

  LFStack(const LFStack& other) = delete;
  LFStack(LFStack&& other) = delete;
  LFStack& operator=(const LFStack& other) = delete;
  LFStack& operator=(LFStack&& other) = delete;

  ~LFStack();

  void push(type_name item);

  std::shared_ptr<T> pop();

  bool is_empty() const;

 private:
  struct Node {
    std::shared_ptr<T> data;
    Node* next{nullptr};
    Node(T data = T()) : data(std::make_shared<T>(std::move(data))) {}
  };

  std::atomic<Node*> head_{nullptr};
};

template <typename T>
LFStack<T>::~LFStack() {
  Node* curr = head_.load();
  while (curr != nullptr) {
    Node* temp = curr->next;
    delete curr;
    curr = temp;
  }
}

template <typename T>
void LFStack<T>::push(type_name item) {
  Node* new_node = new Node(item);
  new_node->next = head_.load();

  // nothing above CAS can move
  while (!head_.compare_exchange_weak(new_node->next, new_node,
                                      std::memory_order_release,
                                      std::memory_order_relaxed));
}

template <typename T>
std::shared_ptr<T> LFStack<T>::pop() {
  Node* node = head_.load();

  // nothing below CAS can move
  while (node != nullptr && !head_.compare_exchange_weak(
                                node, node->next, std::memory_order_acquire,
                                std::memory_order_relaxed));
  if (node == nullptr) {
    return nullptr;
  }
  T data = node->data;
  delete node;
  return data;
}

template <typename T>
bool LFStack<T>::is_empty() const {
  return head_.load() == nullptr;
}

#endif  // LFSTACK_H_
