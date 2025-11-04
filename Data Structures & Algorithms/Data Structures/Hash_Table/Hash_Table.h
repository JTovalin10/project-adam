#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <cstddef>
#include <stdexcept>
#include "../Vector/Vector.h"
#include "../DoubleLinkedList/LinkedList.h"

template<typename T>
class HashTable {
    using value_type = T;
    using size_type = std::size_t;
    public:

    HashTable();

    HashTable& HashTable(const HashTable& other);

    HashTable& HashTable(HashTable&& other);

    ~HashTable();

    HashTable& operator=(const HashTable& other);

    HashTable& operator=(HashTable&& other);
    private:
    Vector<LinkedList<value_type>> table;
};

#include "Hash_Table.cpp"

#endif // HASH_TABLE_H_
