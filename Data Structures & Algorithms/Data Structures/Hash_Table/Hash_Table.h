#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_
#include <cstddef>
#include <stdexcept>
#include "../Vector/Vector.h"
#include "../DoubleLinkedList/LinkedList.h"
#define LOAD_BALANCE 0.75

template<typename K, typename V>
class Node {
public:
    using key_type = K;
    using value_type = V;
    
    key_type key;
    value_type value;
    Node<K, V>* next;
    
    Node();
    Node(const key_type& key, const value_type& value);
};

template<typename K, typename V>
class HashTable {
public:
    using key_type = K;
    using value_type = V;
    using size_type = std::size_t;
    
    // -- CONSTRUCTOR AND DESTRUCTOR --//
    HashTable();
    HashTable(const HashTable& other);
    HashTable(HashTable&& other);
    ~HashTable();
    
    HashTable& operator=(const HashTable& other);
    HashTable& operator=(HashTable&& other);
    
    // -- CAPACITY -- //
    bool empty() const;
    size_type size() const;
    
    // -- MODIFIERS -- //
    void clear();
    void insert(const key_type& key, const value_type& value);
    void insert_or_assign(const key_type& key, const value_type& value);
    void emplace(key_type&& key, value_type&& value);
    void try_emplace(key_type&& key, value_type&& value);
    void erase(const key_type& key);
    void swap(HashTable& other);
    void extract(const HashTable& other);
    void merge(HashTable&& other);
    
    // -- LOOKUP -- //
    value_type& at(const key_type& key);
    const value_type& at(const key_type& key) const;
    value_type& operator[](const key_type& key);
    size_type count(const key_type& key) const;
    Node<K, V>* find(const key_type& key);
    
    // -- HASH POLICY -- //
    double load_factor() const;
    double max_load_factor() const;
    void rehash();
    
private:
    Vector<Node<K, V>*> table_;  // Array of pointers (separate chaining)
    size_type num_elements_;
    size_type num_buckets_;
};

#include "Hash_Table.cpp"
#endif // HASH_TABLE_H_