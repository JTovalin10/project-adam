#ifndef LRU_CACHE_H_
#define LRU_CACHE_H_

#include <unordered_map>
#include <cstddef>
#include <stdexcept>

template<typename K, typename V>
class Node {
    using key_type = K;
    using value_type = V;
    public:
    key_type key;
    value_type value;
    Node<K, V>* prev = nullptr;
    Node<K, V>* next = nullptr;

    Node();

    Node(key_type key, value_type val);
};

template<typename K, typename V>
class LRUCache {
    using size_type = std::size_t;
    using key_type = K;
    using value_type = V;

    public:

    /**
     * Initalizes an empty LRU cache with the given capacity
     * 
     * REQUIRES:
     * capacity > 0
     * 
     * ARGS:
     * capacity: user defined capacity which will be used for the LRU protocol
     */
    LRUCache(size_type capacity);

    LRUCache(const LRUCache& other);

    LRUCache(LRUCache&& other);

    ~LRUCache();

    LRUCache& operator=(const LRUCache& other);

    LRUCache& operator=(LRUCache&& other);

    /**
     * Returns the value associated with the given key
     * 
     * ARGS:
     * key: the key that we are trying to find the value associated with
     * 
     * THROWS:
     * std::out_of_range if the key is not inside the cache
     * 
     * RETURNS:
     * the value associated with the key
     */
    value_type get(const key_type& key);

    /**
     * Adds the key-value pair into the cache (or if they key already exists
     * it will replace the value with the given one)
     * if the new item exceeds the capacity it will then remove the least
     * recentely used key-value pair
     * in the cache to make space for the new item
     * 
     * ARGS:
     * key: the key assocaited with the value that is unique to the value
     * value: the value of the key
     */
    void put(const key_type& key, const value_type& value);

    private:

    std::unordered_map<K, Node<K, V>*> map_;
    Node<K, V>* head_;
    Node<K, V>* tail_;
    size_type capacity_;

    void remove(Node<K, V>* node);
    void insert(Node<K, V>* node);
    bool empty();
    void clear();

};

template<typename K, typename V>
Node<K, V>::Node() : key(K()), value(V()) {}

template<typename K, typename V>
Node<K, V>::Node(key_type key, value_type val) : key(key), value(val) {}

template<typename K, typename V>
LRUCache<K, V>::LRUCache(size_type capacity) : capacity_(capacity) {
    head_ = new Node<K, V>();
    tail_ = new Node<K, V>();
    head_->next = tail_;
    tail_->prev = head_;
}

template<typename K, typename V>
LRUCache<K, V>::LRUCache(const LRUCache& other) : capacity_(other.capacity_) {
    head_ = new Node<K, V>();
    tail_ = new Node<K, V>();
    head_->next = tail_;
    tail_->prev = head_;

    // Deep copy the linked list
    Node<K, V>* other_curr = other.head_->next;
    while (other_curr != other.tail_) {
        Node<K, V>* new_node = new Node<K, V>(other_curr->key, other_curr->value);
        map_[new_node->key] = new_node;
        insert(new_node);
        other_curr = other_curr->next;
    }
}

template<typename K, typename V>
LRUCache<K, V>::LRUCache(LRUCache&& other)
    : map_(std::move(other.map_)),
      head_(other.head_),
      tail_(other.tail_),
      capacity_(other.capacity_) {
    // Steal resources
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.capacity_ = 0;
}

template<typename K, typename V>
LRUCache<K, V>::~LRUCache() {
    
    Node<K, V>* curr = head_;
    while (curr != nullptr) {
        Node<K, V>* temp = curr->next;
        delete curr;
        curr = temp;
    }
}

template<typename K, typename V>
LRUCache<K, V>& LRUCache<K, V>::operator=(const LRUCache& other) {
    if (this == &other) {
        return *this;
    }
    
    clear();
    capacity_ = other.capacity_;
    
    // Deep copy
    Node<K, V>* other_curr = other.head_->next;
    while (other_curr != other.tail_) {
        Node<K, V>* new_node = new Node<K, V>(other_curr->key, other_curr->value);
        map_[new_node->key] = new_node;
        insert(new_node);
        other_curr = other_curr->next;
    }
    
    return *this;
}

template<typename K, typename V>
LRUCache<K, V>& LRUCache<K, V>::operator=(LRUCache&& other) {
    if (this == &other) {
        return *this;
    }
    
    // Clean up current resources
    clear();
    delete head_;
    delete tail_;
    
    // Steal resources
    map_ = std::move(other.map_);
    head_ = other.head_;
    tail_ = other.tail_;
    capacity_ = other.capacity_;
    
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.capacity_ = 0;
    
    return *this;
}

template<typename K, typename V>
typename LRUCache<K, V>::value_type LRUCache<K, V>::get(const key_type& key) {
    const auto& it = map_.find(key);
    if (it == map_.end()) {
        throw std::out_of_range("LRUCache::get, key doesnt exist in the table");
    }
    Node<K, V>* node = it->second;
    V value = node->value;
    // this is the currently used one so we can delete it and then add it back
    remove(node);
    insert(node);
    return value;
}

template<typename K, typename V>
void LRUCache<K, V>::put(const key_type& key, const value_type& value) {
    auto iter = map_.find(key);
    if (iter != map_.end()) {
        remove(iter->second);
    }

    Node<K, V>* new_node = new Node<K, V>(key, value);
    map_[key] = new_node;
    insert(new_node);

    if (map_.size() > capacity_) {
        Node<K, V>* node_to_eject = head_->next;
        remove(node_to_eject);
        map_.erase(node_to_eject->key);
        delete node_to_eject;
    }
}

template<typename K, typename V>
void LRUCache<K, V>::remove(Node<K, V>* node) {
    Node<K, V>* previous_node = node->prev;
    Node<K, V>* next_node = node->next;
    previous_node->next = next_node;
    next_node->prev = previous_node;
}

template<typename K, typename V>
void LRUCache<K, V>::insert(Node<K, V>* node) {
    Node<K, V>* previous_end = tail_->prev;
    previous_end->next = node;
    tail_->prev = node;

    node->prev = previous_end;
    node->next = tail_;
}

template<typename K, typename V>
bool LRUCache<K, V>::empty() {
    return head_->next == tail_;
}

template<typename K, typename V>
void LRUCache<K, V>::clear() {
    Node<K, V>* curr = head_->next;
    while (curr != tail_) {
        Node<K, V>* temp = curr->next;
        delete curr;
        curr = temp;
    }
    head_->next = tail_;
    tail_->prev = head_;
    map_.clear();
}

#endif // LRU_CACHE_H_
