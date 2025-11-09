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
    Color color = RED;
    
    Node();
    Node(const key_type& k, const value_type& v);
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
    RedBlackTree(RedBlackTree&& other) noexcept;
    ~RedBlackTree();
    
    RedBlackTree& operator=(const RedBlackTree& other);
    RedBlackTree& operator=(RedBlackTree&& other) noexcept;
    
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

#endif // REDBLACKTREE_H_