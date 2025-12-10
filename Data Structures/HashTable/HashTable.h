#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <utility>

#include "../Vector/Vector.h"

// Maximum load factor before rehashing (keep between 0.7-1.0)
inline constexpr double MAX_LOAD_FACTOR = 0.75;

template <typename K, typename V>
class HashTable {
 private:
  struct Node;

 public:
  using key_type = K;
  using value_type = V;
  using size_type = std::size_t;

  // -- CONSTRUCTOR AND DESTRUCTOR --//

  /**
   * Constructs an empty HashTable
   */
  HashTable();

  /**
   * Copy constructor that constructs this hashtable with another hashtable
   *
   * ARGS:
   * other: the table that will be copied
   */
  HashTable(const HashTable& other);

  /**
   * Move Constructor that steals from the other hashtable to construct this one
   * * ARGS:
   * other: the table that will be stolen from
   */
  HashTable(HashTable&& other);

  /**
   * Destroys this Hash Table
   */
  ~HashTable();

  /**
   * Copy assignment operator that copies the other hashtable when this
   * hashtable has already been constructed
   *
   * ARGS:
   * other: the table that will be copied
   */
  HashTable& operator=(const HashTable& other);

  /**
   * Move assignment operator that steals from the other hashtable when this
   * hashtable is already constructed
   *
   * ARGS:
   * other: the table that will be stolen from
   */
  HashTable& operator=(HashTable&& other);

  // -- CAPACITY -- //

  /**
   * Checks if the HashTable contains any elements
   *
   * RETURNS:
   * true if the table contains no elements, else false
   */
  bool empty() const { return num_elements_ == 0; }

  /**
   * Returns the number of elements within the HashTable
   *
   * RETURNS:
   * the number of key-value pairs in the HashTable
   */
  size_type size() const { return num_elements_; }

  // -- MODIFIERS -- //

  /**
   * Adds the key-value pair into the table, if the key already exists then
   * nothing happens
   *
   * ARGS:
   * key: the unique identifier of the value
   * value: the value of the key
   */
  void insert(const key_type& key, const value_type& value);

  /**
   * Adds the key-value pair into the table, if the key already exists then
   * it will replace the value of the existing key
   *
   * ARGS:
   * key: the unique identifier of the value
   * value: the value of the key
   */
  void insert_or_assign(const key_type& key, const value_type& value);

  /**
   * Removes the element with the specified key from the table.
   *
   * ARGS:
   * key: the key of the element to remove
   */
  void erase(const key_type& key);

  // -- LOOKUP -- //

  /**
   * Accesses the value associated with the key.
   * Throws std::out_of_range if key doesn't exist.
   *
   * ARGS:
   * key: the key to look up
   *
   * RETURNS:
   * reference to the value associated with the key
   *
   * THROWS:
   * std::out_of_range if key is not found
   */
  value_type& at(const key_type& key);
  const value_type& at(const key_type& key) const;

  /**
   * Accesses or inserts element with the given key.
   * If key doesn't exist, creates it with default value.
   *
   * ARGS:
   * key: the key to look up or insert
   *
   * RETURNS:
   * reference to the value associated with the key
   */
  value_type& operator[](const key_type& key);
  const value_type& operator[](const key_type& key) const;

  /**
   * Finds the node containing the specified key.
   *
   * ARGS:
   * key: the key to search for
   *
   * RETURNS:
   * pointer to the node if found, nullptr otherwise
   */
  Node* find(const key_type& key);
  const Node* find(const key_type& key) const;

  /**
   * Finds the node contains the specified key
   *
   * ARGS:
   * key: the target
   *
   * RETURNS:
   * true if its within the table, else false
   */
  bool contains(const key_type& key) const;

  // -- HASH POLICY -- //

  /**
   * Returns the current load factor (elements / buckets).
   *
   * RETURNS:
   * the load factor
   */
  double load_factor() const;

  /**
   * Returns the maximum allowed load factor before rehashing.
   *
   * RETURNS:
   * the max load factor (0.75)
   */
  double max_load_factor() const;

  /**
   * Reorganizes the hash table by increasing bucket count
   * and redistributing elements.
   */
  void rehash();

  // Forward declaration for iterator
  class iterator;
  class const_iterator;

  // -- ITERATORS -- //
  iterator begin() {
    for (size_type i = 0; i < num_buckets_; ++i) {
      if (table_[i] != nullptr) {
        return iterator(this, i, table_[i]);
      }
    }
    return end();
  }

  const_iterator begin() const {
    for (size_type i = 0; i < num_buckets_; ++i) {
      if (table_[i] != nullptr) {
        return const_iterator(this, i, table_[i]);
      }
    }
    return end();
  }

  const_iterator cbegin() const { return begin(); }

  iterator end() { return iterator(this, num_buckets_, nullptr); }
  const_iterator end() const {
    return const_iterator(this, num_buckets_, nullptr);
  }

  const_iterator cend() const { return end(); }

  // Forward iterator for HashTable that traverses all key-value pairs.
  class iterator {
   public:
    using iterator_category = std::forward_iterator_tag;

    // Constructs an end iterator.
    iterator();

    // Constructs an iterator pointing to the given node in the given bucket.
    //
    // Parameters:
    //   table: Pointer to the HashTable being iterated.
    //   bucket: Index of the bucket containing the node.
    //   node: Pointer to the current node, or nullptr for end iterator.
    iterator(HashTable* table, size_type bucket, Node* node);

    // Dereferences the iterator to access the node.
    //
    // Returns:
    //   Reference to the current node.
    Node& operator*();

    // Accesses the node through pointer semantics.
    //
    // Returns:
    //   Pointer to the current node.
    Node* operator->();

    // Advances the iterator to the next element (prefix increment).
    //
    // Returns:
    //   Reference to this iterator after incrementing.
    iterator& operator++();

    // Advances the iterator to the next element (postfix increment).
    //
    // Returns:
    //   Copy of this iterator before incrementing.
    iterator operator++(int);

    // Compares two iterators for equality.
    //
    // Parameters:
    //   other: The iterator to compare with.
    //
    // Returns:
    //   true if both iterators point to the same node, false otherwise.
    bool operator==(const iterator& other) const;

    // Compares two iterators for inequality.
    //
    // Parameters:
    //   other: The iterator to compare with.
    //
    // Returns:
    //   true if iterators point to different nodes, false otherwise.
    bool operator!=(const iterator& other) const;

   private:
    // Advances to the next element in the hash table.
    void advance_to_next();

    HashTable* table_;
    size_type bucket_index_;
    Node* current_;

    friend class const_iterator;
  };

  // Const forward iterator for HashTable that traverses all key-value pairs.
  class const_iterator {
   public:
    using iterator_category = std::forward_iterator_tag;

    // Constructs an end iterator.
    const_iterator();

    // Constructs a const iterator pointing to the given node in the given
    // bucket.
    //
    // Parameters:
    //   table: Pointer to the HashTable being iterated.
    //   bucket: Index of the bucket containing the node.
    //   node: Pointer to the current node, or nullptr for end iterator.
    const_iterator(const HashTable* table, size_type bucket, const Node* node);

    // Constructs a const_iterator from a non-const iterator.
    //
    // Parameters:
    //   it: The iterator to convert.
    const_iterator(const iterator& it);

    // Dereferences the iterator to access the node.
    //
    // Returns:
    //   Const reference to the current node.
    const Node& operator*() const;

    // Accesses the node through pointer semantics.
    //
    // Returns:
    //   Const pointer to the current node.
    const Node* operator->() const;

    // Advances the iterator to the next element (prefix increment).
    //
    // Returns:
    //   Reference to this iterator after incrementing.
    const_iterator& operator++();

    // Advances the iterator to the next element (postfix increment).
    //
    // Returns:
    //   Copy of this iterator before incrementing.
    const_iterator operator++(int);

    // Compares two iterators for equality.
    //
    // Parameters:
    //   other: The iterator to compare with.
    //
    // Returns:
    //   true if both iterators point to the same node, false otherwise.
    bool operator==(const const_iterator& other) const;

    // Compares two iterators for inequality.
    //
    // Parameters:
    //   other: The iterator to compare with.
    //
    // Returns:
    //   true if iterators point to different nodes, false otherwise.
    bool operator!=(const const_iterator& other) const;

   private:
    // Advances to the next element in the hash table.
    void advance_to_next();

    const HashTable* table_;
    size_type bucket_index_;
    const Node* current_;
  };

 private:
  struct Node {
    const key_type key;
    value_type value;
    Node* next = nullptr;

    Node() = default;

    Node(const key_type& key, const value_type& value)
        : key(key), value(value), next(nullptr) {}
  };

  Vector<Node*> table_;  // Array of pointers (separate chaining)
  size_type num_elements_;
  size_type num_buckets_;

  /**
   * Helper function to compute hash
   */
  size_type hash(const key_type& key) const;
};

// ----------------------------------------------------------------------------
// --- MEMBER FUNCTION DEFINITIONS
// ----------------------------------------------------------------------------

// -- CONSTRUCTOR AND DESTRUCTOR --//

template <typename K, typename V>
HashTable<K, V>::HashTable() : num_elements_(0), num_buckets_(10) {
  // Initialize table_ with nullptrs
  for (size_type i = 0; i < num_buckets_; ++i) {
    table_.push_back(nullptr);
  }
}

template <typename K, typename V>
HashTable<K, V>::HashTable(const HashTable& other)
    : num_elements_(other.num_elements_), num_buckets_(other.num_buckets_) {
  // Initialize table_ with nullptrs
  for (size_type i = 0; i < num_buckets_; ++i) {
    table_.push_back(nullptr);
  }
  // Copy all chains
  for (size_type i = 0; i < other.num_buckets_; ++i) {
    Node* other_curr = other.table_[i];
    Node* this_prev = nullptr;
    while (other_curr != nullptr) {
      Node* new_node = new Node(other_curr->key, other_curr->value);
      if (this_prev == nullptr) {
        table_[i] = new_node;
      } else {
        this_prev->next = new_node;
      }
      this_prev = new_node;
      other_curr = other_curr->next;
    }
  }
}

template <typename K, typename V>
HashTable<K, V>::HashTable(HashTable&& other)
    : table_(std::move(other.table_)),
      num_elements_(other.num_elements_),
      num_buckets_(other.num_buckets_) {
  // Reset other to empty state
  other.num_elements_ = 0;
  other.num_buckets_ = 10;
  // Reinitialize other's table
  other.table_ = Vector<Node*>();
  for (size_type i = 0; i < other.num_buckets_; ++i) {
    other.table_.push_back(nullptr);
  }
}

template <typename K, typename V>
HashTable<K, V>::~HashTable() {
  for (size_type i = 0; i < num_buckets_; ++i) {
    Node* curr = table_[i];
    while (curr != nullptr) {
      Node* temp = curr->next;
      delete curr;
      curr = temp;
    }
  }
}

template <typename K, typename V>
HashTable<K, V>& HashTable<K, V>::operator=(const HashTable& other) {
  if (this == &other) {
    return *this;
  }
  // Clean up current table
  for (size_type i = 0; i < num_buckets_; ++i) {
    Node* curr = table_[i];
    while (curr != nullptr) {
      Node* temp = curr->next;
      delete curr;
      curr = temp;
    }
  }
  // Copy member variables
  num_buckets_ = other.num_buckets_;
  num_elements_ = other.num_elements_;
  // Clear and resize table
  table_ = Vector<Node*>();
  for (size_type i = 0; i < num_buckets_; ++i) {
    table_.push_back(nullptr);
  }
  // Copy all chains
  for (size_type i = 0; i < other.num_buckets_; ++i) {
    Node* other_curr = other.table_[i];
    Node* this_prev = nullptr;
    while (other_curr != nullptr) {
      Node* new_node = new Node(other_curr->key, other_curr->value);
      if (this_prev == nullptr) {
        table_[i] = new_node;
      } else {
        this_prev->next = new_node;
      }
      this_prev = new_node;
      other_curr = other_curr->next;
    }
  }
  return *this;
}

template <typename K, typename V>
HashTable<K, V>& HashTable<K, V>::operator=(HashTable&& other) {
  if (this == &other) {
    return *this;
  }
  // Clean up current table
  for (size_type i = 0; i < num_buckets_; ++i) {
    Node* curr = table_[i];
    while (curr != nullptr) {
      Node* temp = curr->next;
      delete curr;
      curr = temp;
    }
  }
  // Move from other
  table_ = std::move(other.table_);
  num_buckets_ = other.num_buckets_;
  num_elements_ = other.num_elements_;
  // Reset other to empty state
  other.num_buckets_ = 10;
  other.num_elements_ = 0;
  other.table_ = Vector<Node*>();
  for (size_type i = 0; i < other.num_buckets_; ++i) {
    other.table_.push_back(nullptr);
  }
  return *this;
}

// -- MODIFIERS -- //

template <typename K, typename V>
void HashTable<K, V>::insert(const key_type& key, const value_type& value) {
  // Check if key already exists
  Node* existing = find(key);
  if (existing != nullptr) {
    // Key already exists, do nothing
    return;
  }
  size_type hashed_key = hash(key);
  Node* new_node = new Node(key, value);
  if (table_[hashed_key] == nullptr) {
    table_[hashed_key] = new_node;
  } else {
    // Insert at head of chain
    new_node->next = table_[hashed_key];
    table_[hashed_key] = new_node;
  }
  num_elements_++;
  if (load_factor() > max_load_factor()) {
    rehash();
  }
}

template <typename K, typename V>
void HashTable<K, V>::insert_or_assign(const key_type& key,
                                       const value_type& value) {
  size_type hashed_key = hash(key);
  Node* curr = table_[hashed_key];
  while (curr != nullptr) {
    if (curr->key == key) {
      // Key exists, update value
      curr->value = value;
      return;
    }
    curr = curr->next;
  }
  // Key doesn't exist, insert new node
  Node* new_node = new Node(key, value);
  if (table_[hashed_key] == nullptr) {
    table_[hashed_key] = new_node;
  } else {
    // Insert at head of chain
    new_node->next = table_[hashed_key];
    table_[hashed_key] = new_node;
  }
  num_elements_++;
  if (load_factor() > max_load_factor()) {
    rehash();
  }
}

template <typename K, typename V>
void HashTable<K, V>::erase(const key_type& key) {
  size_type hashed_key = hash(key);
  if (table_[hashed_key] == nullptr) {
    return;
  }
  Node* curr = table_[hashed_key];
  Node* prev = nullptr;
  while (curr != nullptr) {
    if (curr->key == key) {
      if (prev == nullptr) {
        // Removing head of chain
        table_[hashed_key] = curr->next;
      } else {
        prev->next = curr->next;
      }
      delete curr;
      num_elements_--;
      return;
    }
    prev = curr;
    curr = curr->next;
  }
}

// -- LOOKUP -- //

template <typename K, typename V>
typename HashTable<K, V>::value_type& HashTable<K, V>::at(const key_type& key) {
  size_type hashed_key = hash(key);
  Node* curr = table_[hashed_key];
  while (curr != nullptr) {
    if (curr->key == key) {
      return curr->value;
    }
    curr = curr->next;
  }
  throw std::out_of_range("HashTable::at: key not found");
}

template <typename K, typename V>
const typename HashTable<K, V>::value_type& HashTable<K, V>::at(
    const key_type& key) const {
  size_type hashed_key = hash(key);
  const Node* curr = table_[hashed_key];
  while (curr != nullptr) {
    if (curr->key == key) {
      return curr->value;
    }
    curr = curr->next;
  }
  throw std::out_of_range("HashTable::at: key not found");
}

template <typename K, typename V>
typename HashTable<K, V>::value_type& HashTable<K, V>::operator[](
    const key_type& key) {
  Node* found = find(key);
  if (found != nullptr) {
    return found->value;
  }
  insert(key, value_type());
  return find(key)->value;
}

template <typename K, typename V>
const typename HashTable<K, V>::value_type& HashTable<K, V>::operator[](
    const key_type& key) const {
  return at(key);
}

template <typename K, typename V>
typename HashTable<K, V>::Node* HashTable<K, V>::find(const key_type& key) {
  size_type hashed_key = hash(key);
  Node* curr = table_[hashed_key];
  while (curr != nullptr) {
    if (curr->key == key) {
      return curr;
    }
    curr = curr->next;
  }
  return nullptr;
}

template <typename K, typename V>
const typename HashTable<K, V>::Node* HashTable<K, V>::find(
    const key_type& key) const {
  size_type hashed_key = hash(key);
  const Node* curr = table_[hashed_key];
  while (curr != nullptr) {
    if (curr->key == key) {
      return curr;
    }
    curr = curr->next;
  }
  return nullptr;
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const key_type& key) const {
  size_type hashed_key = hash(key);
  const Node* curr = table_[hashed_key];
  while (curr != nullptr) {
    if (curr->key == key) {
      return true;
    }
    curr = curr->next;
  }
  return false;
}

// -- HASH POLICY -- //

template <typename K, typename V>
double HashTable<K, V>::load_factor() const {
  if (num_buckets_ == 0) {
    return 0.0;
  }
  return static_cast<double>(num_elements_) / static_cast<double>(num_buckets_);
}

template <typename K, typename V>
double HashTable<K, V>::max_load_factor() const {
  return MAX_LOAD_FACTOR;
}

template <typename K, typename V>
void HashTable<K, V>::rehash() {
  size_type old_bucket_size = num_buckets_;
  num_buckets_ *= 2;
  Vector<Node*> new_table;
  for (size_type i = 0; i < num_buckets_; i++) {
    new_table.push_back(nullptr);
  }
  // set num_elements_ to 0 as we are going to use insert
  std::hash<K> hasher;
  for (size_type i = 0; i < old_bucket_size; i++) {
    Node* curr = table_[i];
    while (curr != nullptr) {
      Node* next_curr = curr->next;

      size_type hash = hasher(curr->key) % num_buckets_;

      curr->next = new_table[hash];
      new_table[hash] = curr;

      curr = next_curr;
    }
  }
  table_ = new_table;
}

// -- Private Helper -- //

template <typename K, typename V>
typename HashTable<K, V>::size_type HashTable<K, V>::hash(
    const key_type& key) const {
  // Use std::hash for generic types, then modulo for bucket assignment
  std::hash<key_type> hasher;
  return hasher(key) % num_buckets_;
}

// ----------------------------------------------------------------------------
// --- ITERATOR DEFINITIONS
// ----------------------------------------------------------------------------

template <typename K, typename V>
HashTable<K, V>::iterator::iterator(HashTable* table, size_type bucket,
                                    Node* node)
    : table_(table), bucket_index_(bucket), current_(node) {
  if (current_ == nullptr && table_ != nullptr) {
    advance_to_next();
  }
}

template <typename K, typename V>
HashTable<K, V>::iterator::iterator()
    : table_(nullptr), bucket_index_(0), current_(nullptr) {}

template <typename K, typename V>
typename HashTable<K, V>::Node& HashTable<K, V>::iterator::operator*() {
  return *current_;
}

template <typename K, typename V>
typename HashTable<K, V>::Node* HashTable<K, V>::iterator::operator->() {
  return current_;
}

template <typename K, typename V>
typename HashTable<K, V>::iterator& HashTable<K, V>::iterator::operator++() {
  if (current_ != nullptr) {
    current_ = current_->next;
    if (current_ == nullptr) {
      advance_to_next();
    }
  }
  return *this;
}

template <typename K, typename V>
typename HashTable<K, V>::iterator HashTable<K, V>::iterator::operator++(int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename K, typename V>
bool HashTable<K, V>::iterator::operator==(const iterator& other) const {
  return current_ == other.current_;
}

template <typename K, typename V>
bool HashTable<K, V>::iterator::operator!=(const iterator& other) const {
  return !(*this == other);
}

template <typename K, typename V>
void HashTable<K, V>::iterator::advance_to_next() {
  bucket_index_++;
  while (bucket_index_ < table_->num_buckets_ &&
         table_->table_[bucket_index_] == nullptr) {
    bucket_index_++;
  }
  if (bucket_index_ < table_->num_buckets_) {
    current_ = table_->table_[bucket_index_];
  } else {
    current_ = nullptr;
  }
}

// ----------------------------------------------------------------------------
// --- CONST_ITERATOR DEFINITIONS
// ----------------------------------------------------------------------------

template <typename K, typename V>
HashTable<K, V>::const_iterator::const_iterator(const HashTable* table,
                                                size_type bucket,
                                                const Node* node)
    : table_(table), bucket_index_(bucket), current_(node) {
  if (current_ == nullptr && table_ != nullptr) {
    advance_to_next();
  }
}

template <typename K, typename V>
HashTable<K, V>::const_iterator::const_iterator()
    : table_(nullptr), bucket_index_(0), current_(nullptr) {}

template <typename K, typename V>
HashTable<K, V>::const_iterator::const_iterator(const iterator& it)
    : table_(it.table_),
      bucket_index_(it.bucket_index_),
      current_(it.current_) {}

template <typename K, typename V>
const typename HashTable<K, V>::Node&
HashTable<K, V>::const_iterator::operator*() const {
  return *current_;
}

template <typename K, typename V>
const typename HashTable<K, V>::Node*
HashTable<K, V>::const_iterator::operator->() const {
  return current_;
}

template <typename K, typename V>
typename HashTable<K, V>::const_iterator&
HashTable<K, V>::const_iterator::operator++() {
  if (current_ != nullptr) {
    current_ = current_->next;
    if (current_ == nullptr) {
      advance_to_next();
    }
  }
  return *this;
}

template <typename K, typename V>
typename HashTable<K, V>::const_iterator
HashTable<K, V>::const_iterator::operator++(int) {
  const_iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename K, typename V>
bool HashTable<K, V>::const_iterator::operator==(
    const const_iterator& other) const {
  return current_ == other.current_;
}

template <typename K, typename V>
bool HashTable<K, V>::const_iterator::operator!=(
    const const_iterator& other) const {
  return !(*this == other);
}

template <typename K, typename V>
void HashTable<K, V>::const_iterator::advance_to_next() {
  bucket_index_++;
  while (bucket_index_ < table_->num_buckets_ &&
         table_->table_[bucket_index_] == nullptr) {
    bucket_index_++;
  }
  if (bucket_index_ < table_->num_buckets_) {
    current_ = table_->table_[bucket_index_];
  } else {
    current_ = nullptr;
  }
}

#endif  // HASHTABLE_H_
