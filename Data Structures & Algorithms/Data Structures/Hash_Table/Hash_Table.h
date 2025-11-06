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
    HashTable(const HashTable& other);

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
    
    // -- CAPACITY -- //

    /**
     * checks if the Hash_Table contains any elements
     * 
     * RETURNS:
     * true if the table contains no elements, else false
     */
    bool empty() const;

    /**
     * Returns the number of elements within the Hash_table
     * 
     * RETURNS:
     * the number of key-value pairs in the Hash_Table
     */
    size_type size() const;
    
    // -- MODIFIERS -- //

    /**
     * Removes all elements within the hashtable
     */
    void clear();

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
     * it will replace the value of the exisiting key
     * 
     * ARGS:
     * key: the unique identifier of the value
     * value: the value of the key
     */
    void insert_or_assign(const key_type& key, const value_type& value);

    /**
     * Adds the key-value pair into the table, but grabs the rvalue for large
     * elements. The key and value may be left empty after the operation.
     * If the key already exists theb
     * 
     * ARGS:
     * key: the unique identifer of the value
     */
    
    /**
     * Adds the key-value pair into the table using move semantics for efficiency.
     * If the key already exists, nothing happens.
     * 
     * ARGS:
     * key: the unique identifier (will be moved)
     * value: the value to store (will be moved)
     */
    void emplace(key_type&& key, value_type&& value);

    /**
     * Attempts to add the key-value pair into the table using move semantics.
     * If the key already exists, nothing happens (unlike emplace).
     * 
     * ARGS:
     * key: the unique identifier (will be moved)
     * value: the value to store (will be moved)
     */
    void try_emplace(key_type&& key, value_type&& value);

    /**
     * Removes the element with the specified key from the table.
     * 
     * ARGS:
     * key: the key of the element to remove
     */
    void erase(const key_type& key);

    /**
     * Swaps the contents of this table with another table.
     * 
     * ARGS:
     * other: the table to swap with
     */
    void swap(HashTable& other);

    /**
     * Extracts nodes from another table (need to clarify behavior).
     * 
     * ARGS:
     * other: the table to extract from
     */
    void extract(const HashTable& other);

    /**
     * Merges elements from another table into this one.
     * 
     * ARGS:
     * other: the table to merge from (will be empty after)
     */
    void merge(HashTable&& other);
    
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
    const value_type& operator[](const key_type& key);

    /**
     * Finds the node containing the specified key.
     * 
     * ARGS:
     * key: the key to search for
     * 
     * RETURNS:
     * pointer to the node if found, nullptr otherwise
     */
    Node<K, V>* find(const key_type& key);
    
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
    Vector<Node<K, V>*> table_;  // Array of pointers (separate chaining)
    size_type num_elements_;
    size_type num_buckets_;

    /**
     * Helper function to compute hash
     */
    size_type hash(const key_type& key) const;
};

#endif // HASH_TABLE_H_