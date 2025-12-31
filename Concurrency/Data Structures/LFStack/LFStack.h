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

  bool empty() const;

 private:
  struct Node {
    std::shared_ptr<T> data;
    Node* next{nullptr};
    Node(T data = T()) : data(std::make_shared<T>(std::move(data))) {}
  };

  std::atomic<Node*> head_{nullptr};
};

template <typename T>
LFStack<T>::~LFStack() {}

template <typename T>
void LFStack<T>::push(type_name item) {}

template <typename T>
std::shared_ptr<T> LFStack<T>::pop() {}

template <typename T>
bool LFStack<T>::empty() const {}

#endif  // LFSTACK_H_
