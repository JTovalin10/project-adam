#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

#include <cstddef>

enum Color { RED, BLACK };

template<typename K, typename V>
class Node {
    using key_type = K;
    using value_type = V;
public:
    Node<K, V>* left = nullptr;
    Node<K, V>* right = nullptr;
    Node<K, V>* parent = nullptr;
    key_type key;
    value_type value;
    Color color = BLACK;
    
    Node();
    Node(const key_type& key, const value_type& value);
};

template<typename K, typename V>
class RedBlackTree {
    using key_type = K;
    using value_type = V;
    using size_type = std::size_t;
    
public:
    // -- CONSTRUCTION & DESTRUCTION -- //
    RedBlackTree();
    RedBlackTree(const RedBlackTree& other);
    RedBlackTree(RedBlackTree&& other);
    ~RedBlackTree();
    
    RedBlackTree& operator=(const RedBlackTree& other) {

    }

    RedBlackTree& operator=(RedBlackTree&& other) {

    }
    
    // -- MODIFIERS -- //
    void insert(const key_type& key, const value_type& value);
    bool remove(const key_type& key);
    void clear();
    
    // -- SEARCH & ACCESS -- //
    value_type* find(const key_type& key);
    const value_type* find(const key_type& key) const;
    bool contains(const key_type& key) const;
    
    // -- PROPERTIES -- //
    size_type size() const;
    bool empty() const;
    
private:
    Node<K, V>* root_;
    size_type size_;
    
    // -- ROTATION OPERATIONS -- //
    void rotateLeft(Node<K, V>* node);
    void rotateRight(Node<K, V>* node);
    
    // -- REBALANCING -- //
    void insertFixup(Node<K, V>* node);
    void deleteFixup(Node<K, V>* node);
    
    // -- NODE MANAGEMENT -- //
    Node<K, V>* findNode(const key_type& key) const;
    Node<K, V>* minimum(Node<K, V>* node) const;
    void transplant(Node<K, V>* u, Node<K, V>* v);
    
    // -- MEMORY MANAGEMENT -- //
    void destroyTree(Node<K, V>* node);
    Node<K, V>* copyTree(Node<K, V>* node, Node<K, V>* parent);
};

template<typename K, typename V>
Node<K, V>::Node() : key(K()), value(V()) {}

template<typename K, typename V>
Node<K, V>::Node(const key_type& key, const value_type& value) : key(key), value(value) {}

template<typename K, typename V>
RedBlackTree<K, V>::RedBlackTree() : size_(0) {

}

template<typename K, typename V>
RedBlackTree<K, V>::RedBlackTree(const RedBlackTree& other) {

}

template<typename K, typename V>
RedBlackTree<K, V>::RedBlackTree(RedBlackTree&& other) {
    
}

template<typename K, typename V>
RedBlackTree<K, V>::~RedBlackTree() {
    
}

template<typename K, typename V>
void RedBlackTree<K, V>::insert(const key_type& key, const value_type& value) {

}

template<typename K, typename V>
bool RedBlackTree<K, V>::remove(const key_type& key) {

}

template<typename K, typename V>
void RedBlackTree<K, V>::clear() {

}

template<typename K, typename V>
typename RedBlackTree<K, V>::value_type* RedBlackTree<K, V>::find(const key_type& key) {

}

template<typename K, typename V>
const typename RedBlackTree<K, V>::value_type* RedBlackTree<K, V>::find(const key_type& key) const {

}

template<typename K, typename V>
bool RedBlackTree<K, V>::contains(const key_type& key) const {

}

template<typename K, typename V>
typename RedBlackTree<K, V>::size_type RedBlackTree<K, V>::size() const {
    return size_;
}

template<typename K, typename V>
bool RedBlackTree<K, V>::empty() const {
    return size_ == 0;
}

template<typename K, typename V>
void RedBlackTree<K, V>::rotateLeft(Node<K, V>* node) {

}

template<typename K, typename V>
void RedBlackTree<K, V>::rotateRight(Node<K, V>* node) {

}

template<typename K, typename V>
void RedBlackTree<K, V>::insertFixup(Node<K, V>* node) {

}

template<typename K, typename V>
void RedBlackTree<K, V>::deleteFixup(Node<K, V>* node) {

}

template<typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::findNode(const key_type& key) const {

}

template<typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::minimum(Node<K, V>* node) const {

}

template<typename K, typename V>
void RedBlackTree<K, V>::transplant(Node<K, V>* u, Node<K, V>* v) {

}

template<typename K, typename V>
void RedBlackTree<K, V>::destroyTree(Node<K, V>* node) {

}

template<typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::copyTree(Node<K, V>* node, Node<K, V>* parent) {

}

#endif // REDBLACKTREE_H_
