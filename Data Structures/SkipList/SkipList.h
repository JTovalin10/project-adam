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

  /**
   * Initalizes an empty skiplist with the default max level and probability
   */
  SkipList();

  /**
   * Initalizes a SkipList that uses the given parameters to calculate an
   * optimal max levels
   *
   * PARAMS:
   * expected_max_elements: the max elements the client expects to see in the
   * skip list
   *
   * desired_probability: the probability of heads the client desires
   */
  SkipList(size_type expected_max_elements, float desired_probability);

  /**
   * deep copies the client given skip list
   *
   * ARGS:
   * other: the skip list that will be copied
   */
  SkipList(const SkipList& other);

  /**
   * Constructs a skiplist by stealing from the other skiplist, it will leave
   * the other skiplist empty
   *
   * ARGS:
   * other: the skiplist that will be stolen from
   */
  SkipList(SkipList&& other);

  /**
   * Safely deconstructs the skiplist, unallocating all memory
   */
  ~SkipList();

  /**
   * Copy assignment operator that copies the other skiplist
   *
   * ARGS:
   * other: the skiplist that will be copied
   *
   * RETURNS:
   * a reference pointer to the new skiplist
   */
  SkipList& operator=(const SkipList& other) {
    if (this == &other) {
      return *this;
    }
    clear();
    size_ = 0;
    delete head_;

    max_level_ = other.max_level_;
    current_level_ = 0;
    probability_ = other.probability_;
    head_ = new Node(K(), V(), max_level_);

    Node* curr = other.head_->next_level[0];
    while (curr != nullptr) {
      insert(curr->key, curr->value);
      curr = curr->next_level[0];
    }
    return *this;
  }

  /**
   * Move assignment operator which steals from the client given skiplist to
   * give to this skiplist
   *
   * ARGS:
   * other: the skiplist that will be stolen from
   *
   * RETURNS:
   * a reference pointer to the newely constructed skiplist
   */
  SkipList& operator=(SkipList&& other) {
    if (this == &other) {
      return *this;
    }
    clear();
    delete head_;
    max_level_ = other.max_level_;
    size_ = other.size_;
    current_level_ = other.current_level_;
    probability_ = other.probability_;

    head_ = other.head_;

    other.head_ = nullptr;
    other.size_ = 0;
    other.current_level_ = 0;
    other.probability_ = 0.0;
    return *this;
  }

  /**
   * adds a new element to the skiplist, if the element already exists then
   * it will replace the exisiting value with the new one
   *
   * ARGS:
   * key: the unique key that defines the value
   * value: the value of the key
   */
  void insert(const key_type& key, const value_type& value);

  /**
   * removes the given key from the skiplist. If the key doesnt exist in the
   * skiplist, then nothing happens
   *
   * ARGS:
   * key: the target node that will be removed
   *
   * RETURNS:
   * if the key exists in the skiplist: true
   * else: false
   */
  bool remove(const key_type& key);

  /**
   * checks if the given key exists within the skiplist
   *
   * ARGS:
   * key: the key of the node we are trying to find
   *
   * RETURNS:
   * returns the value of the node if it exists,
   * if the key doesnt exist in the skiplist then it returns std::nullopt
   */
  std::optional<value_type> find(const key_type& key) const;

  /**
   * checksif the given key exists within the skiplist
   *
   * ARGS:
   * key: the key of the node we are trying to find
   *
   * RETURNS:
   * if the key exists then true, else false
   */
  bool contains(const key_type& key) const;

  /**
   * returns the number of elements within the skiplist
   * (excluding the head_)
   *
   * RETURNS:
   * the number of elements in the list
   */
  size_type size() const;

  /**
   * Checks if the skiplist contains any elements
   *
   * RETURNS:
   * if no elements are found: true, else false
   */
  bool empty() const;

  /**
   * removes all elements from the skiplist
   */
  void clear();

 private:
  struct Node {
    key_type key;
    value_type value;
    std::vector<Node*> next_level;

    /**
     * constructs a new node
     *
     * ARGS:
     * key: the unique key of the node
     * value: the value that is tied to the key
     * level: specificed level we want to give to our vector
     */
    Node(const key_type& key, const value_type& value, size_type level)
        : key(key), value(value), next_level(level + 1, nullptr) {}
  };

  Node* head_;
  size_type size_;
  size_type max_level_;
  size_type current_level_;
  float probability_;

  /**
   * Helper function that calculates a random level for each inserted node
   *
   * RETURNS:
   * A random level that is 0 <= level <= max_level_
   */
  size_type randomLevel();
};

template <typename K, typename V>
SkipList<K, V>::SkipList()
    : size_(0),
      max_level_(DEFAULT_MAX_LEVEL),
      current_level_(0),
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
    : size_(0), current_level_(0), probability_(probability) {
  // as we cant use a specific log we can use log simplification to get
  // L = -log(n) / log(p)
  max_level_ = ceil((-log(expected_max_elements)) / log(probability_));
  // creates dummy node
  head_ = new Node(K(), V(), max_level_);
}

template <typename K, typename V>
// TODO: SEGFAULT
SkipList<K, V>::SkipList(const SkipList& other)
    : max_level_(other.max_level_),
      current_level_(0),
      probability_(other.probability_) {
  head_ = new Node(K(), V(), max_level_);
  Node* curr = other.head_->next_level[0];
  size_ = 0;  // reset to zero as insert increments
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
  other.current_level_ = 0;
  other.max_level_ = 0;
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
  for (int i = current_level_; i >= 0; i--) {
    while (curr->next_level[i] != nullptr && curr->next_level[i]->key < key) {
      curr = curr->next_level[i];
    }
    pred[i] = curr;
  }

  // update the value of the key
  if (curr->next_level[0] != nullptr && curr->next_level[0]->key == key) {
    curr->next_level[0]->value = value;
    return;
  }

  size_type random_level = randomLevel();
  Node* new_node = new Node(key, value, random_level);
  if (random_level > current_level_) {
    for (size_type i = current_level_ + 1; i <= random_level; i++) {
      pred[i] = head_;
    }
    current_level_ = random_level;
  }

  // now we want to link everything
  for (size_type i = 0; i <= random_level; i++) {
    new_node->next_level[i] = pred[i]->next_level[i];
    pred[i]->next_level[i] = new_node;
  }
  size_++;
}

template <typename K, typename V>
bool SkipList<K, V>::remove(const key_type& key) {
  std::vector<Node*> pred(max_level_ + 1, nullptr);
  Node* curr = head_;
  for (int i = current_level_; i >= 0; i--) {
    while (curr->next_level[i] != nullptr && curr->next_level[i]->key < key) {
      curr = curr->next_level[i];
    }
    pred[i] = curr;
  }

  // the key is not within the list
  Node* node_to_delete = curr->next_level[0];
  if (node_to_delete == nullptr || node_to_delete->key != key) {
    return false;
  }
  for (size_type i = 0; i <= current_level_; i++) {
    if (pred[i]->next_level[i] != node_to_delete) {
      break;
    }
    pred[i]->next_level[i] = node_to_delete->next_level[i];
  }
  delete node_to_delete;
  // check if the node we deleted was the top level
  while (current_level_ > 0 && head_->next_level[current_level_] == nullptr) {
    current_level_--;
  }
  size_--;
  return true;
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
        return curr->next_level[i]->value;
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
    // change the next pointers of head so its not reading old memory
    for (size_type i = 0; i < head_->next_level.size(); i++) {
      head_->next_level[i] = nullptr;
    }
    current_level_ = 0;
    size_ = 0;
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
