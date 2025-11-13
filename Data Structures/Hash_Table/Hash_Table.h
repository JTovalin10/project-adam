#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <utility>
#include "../Vector/Vector.h"

// Maximum load factor before rehashing (keep between 0.7-1.0)
static constexpr double MAX_LOAD_FACTOR = 0.75;

template<typename K, typename V>
class HashTable {
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
     * Copy assignment operator that copies the other hashtable when this hashtable has already been constructed
     * 
     * ARGS:
     * other: the table that will be copied
     */
    HashTable& operator=(const HashTable& other);

    /**
     * Move assignment operator that steals from the other hashtable when this hashtable is already constructed
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
    bool empty() const;

    /**
     * Returns the number of elements within the HashTable
     * 
     * RETURNS:
     * the number of key-value pairs in the HashTable
     */
    size_type size() const;

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

private:
    struct Node {
        const key_type key;
        value_type value;
        Node* next = nullptr;
        
        Node() = default;
        
        Node(const key_type& key, const value_type& value) : key(key), value(value), next(nullptr) {}
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

template<typename K, typename V>
HashTable<K, V>::HashTable() : num_elements_(0), num_buckets_(10) {
    // Initialize table_ with nullptrs
    for (size_type i = 0; i < num_buckets_; ++i) {
        table_.push_back(nullptr);
    }
}

template<typename K, typename V>
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

template<typename K, typename V>
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

template<typename K, typename V>
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

template<typename K, typename V>
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

template<typename K, typename V>
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

// -- CAPACITY -- //

template<typename K, typename V>
bool HashTable<K, V>::empty() const {
    return num_elements_ == 0;
}

template<typename K, typename V>
typename HashTable<K, V>::size_type HashTable<K, V>::size() const {
    return num_elements_;
}

// -- MODIFIERS -- //

template<typename K, typename V>
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

template<typename K, typename V>
void HashTable<K, V>::insert_or_assign(const key_type& key, const value_type& value) {
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

template<typename K, typename V>
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

template<typename K, typename V>
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

template<typename K, typename V>
const typename HashTable<K, V>::value_type& HashTable<K, V>::at(const key_type& key) const {
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

template<typename K, typename V>
typename HashTable<K, V>::value_type& HashTable<K, V>::operator[](const key_type& key) {
    Node* found = find(key);
    if (found != nullptr) {
        return found->value;
    }
    insert(key, value_type()); 
    return find(key)->value; 
}

template<typename K, typename V>
const typename HashTable<K, V>::value_type& HashTable<K, V>::operator[](const key_type& key) const {
    return at(key);
}


template<typename K, typename V>
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

template<typename K, typename V>
const typename HashTable<K, V>::Node* HashTable<K, V>::find(const key_type& key) const {
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

template<typename K, typename V>
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

template<typename K, typename V>
double HashTable<K, V>::load_factor() const {
    if (num_buckets_ == 0) {
        return 0.0;
    }
    return static_cast<double>(num_elements_) / static_cast<double>(num_buckets_);
}

template<typename K, typename V>
double HashTable<K, V>::max_load_factor() const {
  return MAX_LOAD_FACTOR;
}

template<typename K, typename V>
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

template<typename K, typename V>
typename HashTable<K, V>::size_type HashTable<K, V>::hash(const key_type& key) const {
  // Use std::hash for generic types, then modulo for bucket assignment
  std::hash<key_type> hasher;
  return hasher(key) % num_buckets_;
}


#endif // HASH_TABLE_H_
