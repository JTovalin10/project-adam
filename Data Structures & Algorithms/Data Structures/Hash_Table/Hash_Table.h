#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_
#include <cstddef>
#include <stdexcept>
#include "../Vector/Vector.h"
#include "../DoubleLinkedList/LinkedList.h"

#define LOAD_BALANCE 0.75 // you can change but keep between 0.7-1.0

template<typename K, typename V>
class Node {
public:
    using key_type = K;
    using value_type = V;
    
    key_type key;
    value_type value;
    Node<K, V>* next = nullptr;
    
    Node() = default;
    
    Node(const key_type& key, const value_type& value) : key(key), value(value), next(nullptr) {}
};

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
    HashTable() : num_elements_(0), num_buckets_(10) {
        table_.resize(num_buckets_, nullptr);
    }

    /**
     * Copy Construtor that constructs this hashtable with another hashtable
     * 
     * ARGS:
     * other: the table that will be copied
     */
    HashTable(const HashTable& other) : num_elements_(other.num_elements_), num_elements_(other.num_elements_) {
      table_.resize(num_elements_, nullptr);
      
    }

    /**
     * Move Constructor that steals from the other hashtable to construct this one
     * 
     * ARGS:
     * other: the table that will be stolen from
     */
    HashTable(HashTable&& other);

    /**
     * Deconstructs this Hash Table
     */
    ~HashTable();
    
    /**
     * Copy Assignment Operator that copied the other hashtable when this hashtable has already been constructed
     * 
     * ARGS:
     * other: the table that will be copied
     */
    HashTable& operator=(const HashTable& other);

    /**
     * Move Assignment Operator that steals from the other hashtable when this hashtable is already constructed
     * 
     * ARGS:
     * other: the table that will be stolen from
     */
    HashTable& operator=(HashTable&& other);
    
private:
    Vector<Node<K, V>*> table_;  // Array of pointers (separate chaining)
    size_type num_elements_;
    size_type num_buckets_;

    /**
     * Helper function to compute hash
     */
    size_type hash(const key_type& key) const;
};


// -- CAPACITY -- //

/**
  * checks if the Hash_Table contains any elements
  *
  * RETURNS:
  * true if the table contains no elements, else false
  */
template<typename K, typename V>
bool HashTable<K, V>::empty() const {
  return num_elements_ == 0;
}

/**
  * Returns the number of elements within the Hash_table
  *
  * RETURNS:
  * the number of key-value pairs in the Hash_Table
  */
template<typename K, typename V>
size_type HashTable<K, V>::size() const {
  return num_elements_;
}

/**
  * Adds the key-value pair into the table, if the key already exists then
  * nothing happens
  *
  * ARGS:
  * key: the unique identifier of the value
  * value: the value of the key
  */
template<typename K, typename V>
void HashTable<K, V>::insert(const key_type& key, const value_type& value) {

}

/**
  * Adds the key-value pair into the table, if the key already exists then
  * it will replace the value of the exisiting key
  *
  * ARGS:
  * key: the unique identifier of the value
  * value: the value of the key
  */
template<typename K, typename V>
void HashTable<K, V>::insert_or_assign(const key_type& key, const value_type& value) {

}

/**
  * Adds the key-value pair into the table using move semantics for efficiency.
  * If the key already exists, nothing happens.
  *
  * ARGS:
  * key: the unique identifier (will be moved)
  * value: the value to store (will be moved)
  */
template<typename K, typename V>
void HashTable<K, V>::emplace(key_type&& key, value_type&& value) {

}

/**
  * Attempts to add the key-value pair into the table using move semantics.
  * If the key already exists, nothing happens (unlike emplace).
  *
  * ARGS:
  * key: the unique identifier (will be moved)
  * value: the value to store (will be moved)
  */
template<typename K, typename V>
void HashTable<K, V>::try_emplace(key_type&& key, value_type&& value) {

}

/**
  * Removes the element with the specified key from the table.
  *
  * ARGS:
  * key: the key of the element to remove
  */
template<typename K, typename V>
void HashTable<K, V>::erase(const key_type& key) {

}

/**
  * Swaps the contents of this table with another table.
  *
  * ARGS:
  * other: the table to swap with
  */
template<typename K, typename V>
void HashTable<K, V>::swap(HashTable& other) {

}

/**
  * Extracts nodes from another table (need to clarify behavior).
  *
  * ARGS:
  * other: the table to extract from
  */
template<typename K, typename V>
void HashTable<K, V>::extract(const HashTable& other) {

}

/**
  * Merges elements from another table into this one.
  *
  * ARGS:
  * other: the table to merge from (will be empty after)
  */
template<typename K, typename V>
void HashTable<K, V>::merge(HashTable&& other) {

}

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
  */
template<typename K, typename V>
value_type& HashTable<K, V>::at(const key_type& key) {

}

template<typename K, typename V>
const value_type& HashTable<K, V>::at(const key_type& key) const {

}

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
template<typename K, typename V>
value_type& HashTable<K, V>::operator[](const key_type& key) {

}

template<typename K, typename V>
const HashTable<K, V>::value_type& operator[](const key_type& key) {

}

/**
  * Finds the node containing the specified key.
  * 
  * ARGS:
  * key: the key to search for
  * 
  * RETURNS:
  * pointer to the node if found, nullptr otherwise
  */
template<typename K, typename V>
Node<K, V>* HashTable<K, V>find(const key_type& key) {

}

// -- HASH POLICY -- //

/**
  * Returns the current load factor (elements / buckets).
  * 
  * RETURNS:
  * the load factor
  */
template<typename K, typename V>
double HashTable<K, V>::load_factor() const {

}

/**
  * Returns the maximum allowed load factor before rehashing.
  * 
  * RETURNS:
  * the max load factor (0.75)
  */
template<typename K, typename V>
double HashTable<K, V>::max_load_factor() const {

}

/**
  * Reorganizes the hash table by increasing bucket count
  * and redistributing elements.
  */
template<typename K, typename V>
void HashTable<K, V>::rehash() {

}

// -- Private Helper -- //

template<typename K, typename V>
size_type HashTable<K, V>::hash(const key_type* key) const {
  return key % num_buckets_;
}

#endif // HASH_TABLE_H_
