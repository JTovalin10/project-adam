#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#define DEFAULT_MAX_LEVEL 16
#define DEFAULT_PROBABILITY 0.5

#include <cstddef>
#include <optional>
#include <vector>

template<typename K, typename V>
class SkipList {
  public:
  using size_type = std::size_t;
  using key_type = K;
  using value_type = V;

  SkipList();
  SkipList(size_type max_level, float probability);

  SkipList(const SkipList& other);
  SkipList(SkipList&& other);
  ~SkipList();
  SkipList& operator=(const SkipList& other);
  SkipList& operator=(SkipList&& other);

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
    std::vector<Node*> forward;

    Node(const key_type& key, const value_type& value, size_type level) :
      key(key), value(value), forward(level + 1, nullptr) {}
  };

  Node<K, V>* head_;
  size_type size_;
  size_type max_level_;
  size_type current_level_;
  float probability_;

  // helper methods
  size_type randomLevel();
  Node<K, V>* createNode(const key_type& key, const value_type& value, size_type level);
};

template<typename K, typename V>
SkipList<K, V>::SkipList() : head_(nullptr), size_(0), max_level_(DEFAULT_MAX_LEVEL), probability_(DEFAULT_PROBABILITY) {}

}

template<typename K, typename V>
SkipList<K, V>::SkipList(size_type max_level, float probability) : head_(nullptr), size_(0), max_level_(max_level_), probability_(probability_) {}

template<typename K, typename V>
SkipList<K, V>::SkipList(const SkipList& other) {

}

template<typename K, typename V>
SkipList<K, V>::SkipList(SkipList&& other) {

}

template<typename K, typename V>
SkipList<K, V>::~SkipList() {

}

template<typename K, typename V>
void SkipList<K, V>::insert(const key_type& key, const value_type& value) {

}

template<typename K, typename V>
bool SkipList<K, V>::remove(const key_type& key) {

}

template<typename K, typename V>
std::optional<value_type> SkipList<K, V>::find(const key_type& key) const {

}

template<typename K, typename V>
bool SkipList<K, V>::contains(const key_type& key) const {
  std::optional<value_type> value = find(key);
  if (value.has_value()) {
    return true;
  } else {
    return false;
  }
}

template<typename K, typename V>
typename SkipList<K, V>::size_type SkipList<K, V>::size() const {
  return size_;
}

template<typename K, typename V>
bool SkipList<K, V>::empty() const {
  return size_ == 0;
}

template<typename K, typename V>
void SkipList<K, V>::clear() {

}

template<typename K, typename V>
typename SkipList<K, V>::size_type SkipList<K, V>::randomLevel() {

}

template<typename K, typename V>
typename SkipList<K, V>::size_type SkipList<K, V>::randomLevel() {

}

template<typename K, typename V>
Node* SkipList<K, V>::createNode(const key_type& key, const value_type& value, size_type level) {

}

#endif // SKIPLIST_H_

