#ifndef LRU_CACHE_H_
#define LRU_CACHE_H_

#include <unordered_map>
#include "../DoubleLinkedList/LinkedList.h"
#include <cstddef>

template<typename K, typename V>
class LRUCache {
    using size_type = std::size_t;
    using key_type = K;
    using value_type = V;

    public:

    LRUCache(size_type capacity);

    value_type get(const key_type& key);

    void put(const key_value& key, const value_type& value);

    private:
    
    std::unordered_map<K, V> map_;
    LinkedList<K> list_;
    size_type size_;
};


#endif // LRU_CACHE_H_
