#ifndef FGQUEUE_H_
#define FGQUEUE_H_

#include <algorithm>
#include <memory>
#include <mutex>

template <typename T>
class FGQueue {
  using value_type = T;

 public:
  /**
   * default constructor that sets the tail to the head_
   */
  FGQueue() : head_(new Node), tail_(head_.get()) {}

  FGQueue(const FGQueue& other) = delete;
  FGQueue& operator=(const FGQueue& other) = delete;

  /**
   * unique ptrs handle clean up
   */
  ~FGQueue() = default;

  /**
   * move constructor: steals from rvalue other
   *
   * ARGS:
   * other: rvalue that will be stolen from
   */
  FGQueue(FGQueue&& other) noexcept {
    if (this != &other) {
      std::scoped_lock lock(head_mtx_, other.head_mtx_, tail_mtx_,
                            other.tail_mtx_);
      head_ = std::move(other.head_);
      tail_ = other.tail_;

      other.tail_ = nullptr;
    }
  }

  /**
   * move assignment operator: steals from rvalue other
   *
   * ARGS:
   * other: rvalue that will be stolen from
   */
  FGQueue& operator=(FGQueue&& other) noexcept {
    if (this != &other) {
      std::scoped_lock lock(head_mtx_, other.head_mtx_, tail_mtx_,
                            other.tail_mtx_);
      head_.reset();

      head_ = std::move(other.head_);
      tail_ = other.tail_;

      other.tail_ = nullptr;
    }
    return *this;
  }

  /**
   * pops from the front of the queue
   *
   * RETURNS:
   * returns a shared ptr that contains the value of the head if the queue is
   * not empty. otherwise, the shared_ptr contains nullptr as the queue is empty
   */
  std::shared_ptr<value_type> try_pop() {
    std::unique_ptr<Node> old_head = pop_head();
    Node* const node = old_head.get();
    return node ? node->data : nullptr;
  }

  /*
   * Adds client provided element to the end of the queue
   *
   * ARGS:
   * item: element of type T that will be added to the queue
   */
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
    tail_->data = new_value;
    tail_->next = std::move(new_node);
    // set the tail to the new_tail
    tail_ = new_tail;
  }

 private:
  struct Node {
    // shared_ptr so that this works on any type as we dont need the default
    // constructor
    std::shared_ptr<value_type> data;
    // unique ptr handles clean up
    std::unique_ptr<Node> next{nullptr};

    Node() = default;

    explicit Node(T data) : data(std::make_shared<T>(std::move(data))) {}
  };

  /**
   * helper function that pops head if the queue is not empty
   *
   * RETURNS:
   * returns a unique_ptr with the old_head node if the queue is not empty.
   * otherwise it will return a unique_ptr with a nullptr.
   */
  std::unique_ptr<Node> pop_head() {
    std::lock_guard head_lock(head_mtx_);
    if (not_empty()) {
      std::unique_ptr<Node> old_head = std::move(head_);
      head_ = std::move(old_head->next);
      return old_head;
    }
    return nullptr;
  }

  /**
   * Helper function that checks if the queue is empty
   *
   * RETURNS:
   * if the queue is empty returns true. otherwise, returns false
   */
  bool empty() const { return head_.get() == tail_; }

  /**
   * Helper function that checks if the queue is not empty
   *
   * RETURNS:
   * if the queue is not empty returns true, otherwise returns false
   */
  bool not_empty() const { return head_->next != nullptr; }

  std::unique_ptr<Node> head_;  // front
  Node* tail_;                  // back

  std::mutex head_mtx_;
  std::mutex tail_mtx_;
};

#endif  // FGQUEUE_H_
