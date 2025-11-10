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
        if (this == &other) {
            return *this;
        }
        destroyTree(root_);
        root_ = copyTree(other.root_);
        size_ = other.size_;
        return *this;
    }

    RedBlackTree& operator=(RedBlackTree&& other) {
        if (this == &other) {
            return *this;
        }
        destroyTree(root_);
        root = copyTree(other.root_);
        size_ = other.size_;

        destroyTree(other.root_);
        other.size_ = 0;
        return *this;
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
RedBlackTree<K, V>::RedBlackTree() : root_(nullptr), size_(0) {}

template<typename K, typename V>
RedBlackTree<K, V>::RedBlackTree(const RedBlackTree& other) : size_(other.size_) {
    root_ = copyTree(other.root_);
}

template<typename K, typename V>
RedBlackTree<K, V>::RedBlackTree(RedBlackTree&& other) : size_(other.size_) {
    root_ = copyTree(other.root_);
    destoryTree(other.root_);
    other.size_ = 0;
}

template<typename K, typename V>
RedBlackTree<K, V>::~RedBlackTree() {
    destoryTree(root_);
}

template<typename K, typename V>
void RedBlackTree<K, V>::insert(const key_type& key, const value_type& value) {
    if (empty()) {
        root_ = new Node<K, V>(key, value);
    } else {
        // find the correct place
        Node<K, V>* curr = root_;
        while (curr != nullptr) {
            if (curr->key > key) {
                curr = curr->left;
            } else if (curr->key < key) {
                curr = curr->right;
            } else {
                break;
            }
        }
        curr = new Node<K, V>(key, value);
        // TODO: we must check if it satisfies the red-black structure
    }
    size_++;
}

template<typename K, typename V>
bool RedBlackTree<K, V>::remove(const key_type& key) {
    Node<K, V>* node_to_remove = findNode(key);
    if (node_to_remove == nullptr) {
        return false;
    }
    // TODO: something here
    size_--;
    return true;
}

template<typename K, typename V>
void RedBlackTree<K, V>::clear() {
    destroyTree(root_);
    root_ = nullptr;
    size_ = 0;
}

template<typename K, typename V>
typename RedBlackTree<K, V>::value_type* RedBlackTree<K, V>::find(const key_type& key) {
    Node<K, V>* curr = root_;
    while (curr != nullptr) {
        if (curr->key > key) {
            curr = curr->left;
        } else if(curr->key < key) {
            curr = curr->right;
        } else {
            return curr->value;
        }
    }
    return nullptr;
}

template<typename K, typename V>
const typename RedBlackTree<K, V>::value_type* RedBlackTree<K, V>::find(const key_type& key) const {
    Node<K, V>* curr = root_;
    while (curr != nullptr) {
        if (curr->key > key) {
            curr = curr->left;
        } else if(curr->key < key) {
            curr = curr->right;
        } else {
            return curr->value;
        }
    }
    return nullptr;
}

template<typename K, typename V>
bool RedBlackTree<K, V>::contains(const key_type& key) const {
    Node<K, V>* node = find(key);
    if (node == nullptr) {
        return false;
    } else {
        return true;
    }
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
    if (root_ == nullptr) {
        return nullptr;
    }
    Node<K, V>* curr = root_;
    while (curr != nullptr) {
        if (curr->key < key) {
            curr = curr->right;
        } else if (curr->key > key) {
            curr = curr->left;
        } else {
            return curr;
        }
    }
    return nullptr;
}

template<typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::minimum(Node<K, V>* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    Node<K, V>* curr = node;
    while (curr != nullptr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

template<typename K, typename V>
void RedBlackTree<K, V>::transplant(Node<K, V>* u, Node<K, V>* v) {

}

template<typename K, typename V>
void RedBlackTree<K, V>::destroyTree(Node<K, V>* node) {
    if (node == nullptr) {
        return;
    }
    destoryTree(node.left);
    destoryTree(node.right);
    delete node;
}

template<typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::copyTree(Node<K, V>* node, Node<K, V>* parent) {
   if (node == nullptr) {
    return nullptr;
   }
   Node<K, V>* new_node = new Node<K, V>(node->key, node->value);
   new_node->parent = parent;
   new_node->color = node->color;

   new_node->left = copyTree(node->left, new_node);
   new_node->right = copyTree(node->right, new_node);
   return new_node;
}



#endif // REDBLACKTREE_H_
