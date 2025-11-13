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
  Node<K, V>* createNode(const K& key, const V& value, size_type level);
};

#endif // SKIPLIST_H_

