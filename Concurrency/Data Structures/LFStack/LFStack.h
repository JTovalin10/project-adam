#ifndef LFSTACK_H_
#define LFSTACK_H_

#include <atomic>
#include <memory>

#include "../utils/HazardPointer/HazardPointer.h"

template <typename T>
class LFStack {
  using type_name = T;

 public:
  LFStack() : hp_(8) {}

  LFStack(const LFStack& other) = delete;
  LFStack(LFStack&& other) = delete;
  LFStack& operator=(const LFStack& other) = delete;
  LFStack& operator=(LFStack&& other) = delete;

  ~LFStack();

  void push(type_name item);

  std::shared_ptr<T> pop();

  bool empty() const { return head_.load() == nullptr; }

 private:
  struct Node {
    std::shared_ptr<T> data;
    Node* next{nullptr};
    explicit Node(T data) : data(std::make_shared<T>(std::move(data))) {}
  };

  std::atomic<Node*> head_{nullptr};
  HazardPointer<Node> hp_;
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
  Node* new_node = new Node(std::move(item));
  new_node->next = head_.load(std::memory_order_relaxed);
  while (!head_.compare_exchange_weak(new_node->next, new_node,
                                      std::memory_order_release,
                                      std::memory_order_relaxed)) {
  }
}

template <typename T>
std::shared_ptr<T> LFStack<T>::pop() {
  while (true) {
    Node* node_to_remove = head_.load(std::memory_order_acquire);

    if (node_to_remove == nullptr) {
      return nullptr;
    }

    hp_.protect(node_to_remove);

    // Verify head hasn't changed after protection
    if (node_to_remove != head_.load(std::memory_order_acquire)) {
      hp_.release();
      continue;
    }

    Node* next = node_to_remove->next;
    if (head_.compare_exchange_weak(node_to_remove, next,
                                    std::memory_order_release,
                                    std::memory_order_relaxed)) {
      hp_.release();
      std::shared_ptr<T> result = node_to_remove->data;
      hp_.retire(node_to_remove);
      return result;
    }
    hp_.release();
  }
}

#endif  // LFSTACK_H_