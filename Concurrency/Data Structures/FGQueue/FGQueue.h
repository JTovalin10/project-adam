#ifndef FGQUEUE_H_
#define FGQUEUE_H_

#include <algorithm>
#include <memory>
#include <shared_mutex>

template <typename T>
class FGQueue {
  using value_type = T;

 public:
  FGQueue() : head_(new Node), tail_(head_.get()) {}

  FGQueue(const FGQueue& other) = delete;
  FGQueue& operator=(const FGQueue& other) = delete;

  ~FGQueue() = default;

  FGQueue(FGQueue&& other) noexcept;

  FGQueue& operator=(FGQueue&& other) noexcept;

  std::shared_ptr<value_type> try_pop() {
    std::unique_ptr<Node> old_head = pop_head();
    return old_head ? old_head->data : nullptr;
  }

  // add to the tail
  void push(value_type item) {
    // as unique and shared ptr are expensie to make we allow other threads to
    // work while these get constructed
    std::unique_ptr<Node> new_node = std::make_unique<Node>();
    std::shared_ptr<value_type> new_value =
        std::make_shared<T>(std::move(item));
    // grab the new_tail so we can work on it
    Node* const new_tail = new_node.get();
    // lock the function so we can do our work now
    std::lock_guard tail_lock(tail_mtx_);
    tail_->next = std::move(new_node);
    new_tail->data = new_value;
    // set the tail to the new_tail
    tail_ = new_tail;
  }

 private:
  struct Node {
    std::shared_ptr<value_type> data;
    std::unique_ptr<Node> next{nullptr};

    Node() = default;

    explicit Node(T data) : data(std::make_shared<T>(std::move(data))) {}
  };

  std::unique_ptr<Node> pop_head() {
    std::lock_guard head_lock(head_mtx_);
    if (not_empty()) {
      std::unique_ptr<Node> old_head = std::move(head_);
      head_ = std::move(old_head->next);
      return old_head;
    }
    return nullptr;
  }

  bool empty() const { return head_.get() == tail_; }

  bool not_empty() const { return head_.get() != tail_; }

  std::unique_ptr<Node> head_;  // front
  Node* tail_;                  // back

  mutable std::shared_mutex head_mtx_;
  mutable std::shared_mutex tail_mtx_;
};

#endif  // FGQUEUE_H_
