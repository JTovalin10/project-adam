#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#define DEFAULT_MAX_LEVEL 16
#define DEFAULT_PROBABILITY 0.5

#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <optional>
#include <vector>

// when creating a skiplist we flip a coin with our probability and set a max
template <typename K, typename V>
class SkipList {
 public:
  using size_type = std::size_t;
  using key_type = K;
  using value_type = V;

  // with our defaults it can store up to 65,536 items
  SkipList();

  // we use these to calculate the max level with
  // L = ceil(log_{1/p}(N))
  // p = probability
  // N = expected_max_elements
  SkipList(size_type expected_max_elements, float desired_probability);

  SkipList(const SkipList& other);
  SkipList(SkipList&& other);
  ~SkipList();
  SkipList& operator=(const SkipList& other) {
    if (this == &other) {
      return *this;
    }
    clear();
    max_level_ = other.max_level_;
    current_level_ = other.current_level_;
    probability_ = other.probability_;

    Node* curr = other.head_->next_level[0];
    while (curr != nullptr) {
      insert(curr->key, curr->value);
      curr = curr->next_level[0];
    }
    return *this;
  }

  SkipList& operator=(SkipList&& other) {
    if (this == &other) {
      return *this;
    }
    clear();
    max_level_ = other.max_level_;
    current_level_ = other.current_level_;
    probability_ = other.probability_;

    head_ = other.head_;

    other.head_ = nullptr;
    other.size_ = 0;
    other.current_level_ = 0;
    other.probability_ = 0.0;
    return *this;
  }

  void insert(const key_type& key, const value_type& value);
  bool remove(const key_type& key);
  std::optional<value_type> find(const key_type& key) const;
  bool contains(const key_type& key) const;

  size_type size() const;
  bool empty() const;
  void clear();

 private:
  struct Node {
    key_type key;
    value_type value;
    std::vector<Node*> next_level;

    Node(const key_type& key, const value_type& value, size_type level)
        : key(key), value(value), next_level(level + 1, nullptr) {}
  };

  Node* head_;
  size_type size_;
  size_type max_level_;
  size_type current_level_;
  float probability_;

  // helper methods
  size_type randomLevel();
};

template <typename K, typename V>
SkipList<K, V>::SkipList()
    : size_(0),
      max_level_(DEFAULT_MAX_LEVEL),
      probability_(DEFAULT_PROBABILITY) {
  // creates dummy node
  head_ = new Node(K(), V(), max_level_);
}

// we use these to calculate the max level with
// L = ceil(log_{1/p}(N))
// p = probability
// N = expected_max_elements
template <typename K, typename V>
SkipList<K, V>::SkipList(size_type expected_max_elements, float probability)
    : head_(nullptr), size_(0), probability_(probability) {
  // as we cant use a specific log we can use log simplification to get
  // L = -log(n) / log(p)
  max_level_ = ceil((-log(expected_max_elements)) / log(probability_));
  // creates dummy node
  head_ = new Node(K(), V(), max_level_);
}

template <typename K, typename V>
SkipList<K, V>::SkipList(const SkipList& other)
    : max_level_(other.max_level_),
      current_level_(other.current_level_),
      probability_(other.probability_) {
  head_ = new Node(K(), V(), max_level_);
  Node* curr = other.head_->next_level[0];
  while (curr != nullptr) {
    insert(curr->key, curr->value);
    curr = curr->next_level[0];
  }
}

template <typename K, typename V>
SkipList<K, V>::SkipList(SkipList&& other)
    : size_(other.size_),
      max_level_(other.max_level_),
      current_level_(other.current_level_),
      probability_(other.probability_) {
  head_ = other.head_;

  other.head_ = nullptr;
  other.size_ = 0;
  other.max_level_ = 0;
  other.current_level_ = 0;
}

template <typename K, typename V>
SkipList<K, V>::~SkipList() {
  Node* curr = head_;
  while (curr != nullptr) {
    Node* next_curr = curr->next_level[0];
    delete curr;
    curr = next_curr;
  }
}

template <typename K, typename V>
void SkipList<K, V>::insert(const key_type& key, const value_type& value) {
  std::vector<Node*> pred(max_level_ + 1, nullptr);
  Node* curr = head_;
  for (int i = current_level_ - 1; i >= 0; i--) {
    while (curr->next_level[i] != nullptr && curr->next_level[i]->key < key) {
      curr = curr->next_level[i];
    }
    pred[i] = curr;
  }

  // update the value of the key
  if (curr->next_level[0] != nullptr && curr->next_level[0]->key == key) {
    curr->next_level[0] = value;
    return;
  }

  size_type random_level = randomLevel();
  Node* new_node = new Node(key, value, random_level);
  if (random_level > current_level_) {
    for (int i = current_level_; i < random_level; i++) {
      pred[i] = head_;
    }
    current_level_ = random_level;
    head_->next_level[current_level_] = new_node;
  }

  // now we want to link everything
  for (int i = 0; i < random_level; i++) {
    new_node->next_level[i] = pred[i]->next_level[i];
    pred[i]->next_level[i] = new_node;
  }
  size_++;
}

template <typename K, typename V>
bool SkipList<K, V>::remove(const key_type& key) {
  std::vector<Node*> pred(max_level_, nullptr);
  Node* curr = head_;
  for (int i = current_level_; i >= 0; i--) {
    while (curr->next_level[i] != nullptr && curr->next_level[i]->key < key) {
      curr = curr->next_level[i];
    }
    pred[i] = curr;
  }

  // the key is not within the list
  if (curr->next_level[0] == nullptr ||
      (curr->next_level[0] != nullptr && curr->next_level[0]->key != key)) {
    return false;
  }

  for (int i = 0; i < current_level_; i++) {
    pred[i]->next_level[i] = curr->next_level[i];
  }
  delete curr;
}

template <typename K, typename V>
std::optional<V> SkipList<K, V>::find(const key_type& key) const {
  if (empty()) {
    return std::nullopt;
  }
  Node* curr = head_;
  for (int i = current_level_; i >= 0; i--) {
    while (curr->next_level[i] != nullptr && curr->next_level[i]->key <= key) {
      if (curr->next_level[i]->key == key) {
        return curr->value;
      }
      curr = curr->next_level[i];
    }
  }
  return std::nullopt;
}

template <typename K, typename V>
bool SkipList<K, V>::contains(const key_type& key) const {
  std::optional<value_type> value = find(key);
  if (value.has_value()) {
    return true;
  } else {
    return false;
  }
}

template <typename K, typename V>
typename SkipList<K, V>::size_type SkipList<K, V>::size() const {
  return size_;
}

template <typename K, typename V>
bool SkipList<K, V>::empty() const {
  // the nullptr check if a precaution check in case it was moved and size
  // was not changed to 0. Although this should never happen
  return size_ == 0 || head_ == nullptr;
}

template <typename K, typename V>
void SkipList<K, V>::clear() {
  if (!empty()) {
    Node* curr = head_->next_level[0];
    while (curr != nullptr) {
      Node* next_curr = curr->next_level[0];
      delete curr;
      curr = next_curr;
    }
    size_ = 0;
    current_level_ = 0;
  }
}

template <typename K, typename V>
typename SkipList<K, V>::size_type SkipList<K, V>::randomLevel() {
  size_type level = 0;
  while ((level < max_level_) &&
         (rand() / static_cast<double>(RAND_MAX) < probability_)) {
    level++;
  }
  return level;
}

#endif  // SKIPLIST_H_
