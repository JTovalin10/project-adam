#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

#include <cstddef>

enum Color { RED, BLACK };

template <typename K, typename V>
class Node {
  using key_type = K;
  using value_type = V;

 public:
  Node<K, V>* left = nullptr;
  Node<K, V>* right = nullptr;
  Node<K, V>* parent = nullptr;
  // made const so that the client cannot violate the BST strucutre
  const key_type key;
  value_type value;
  Color color = RED;

  Node();
  Node(const key_type& key, const value_type& value);
};

template <typename K, typename V>
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
    root_ = copyTree(other.root_, nullptr);
    size_ = other.size_;
    return *this;
  }

  RedBlackTree& operator=(RedBlackTree&& other) {
    if (this == &other) {
      return *this;
    }
    destroyTree(root_);
    root_ = other.root_;
    size_ = other.size_;

    other.root_ = nullptr;
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
  void insertFixUp(Node<K, V>* node);
  void deleteFixup(Node<K, V>* node);

  // -- NODE MANAGEMENT -- //
  Node<K, V>* findNode(const key_type& key) const;
  Node<K, V>* minimum(Node<K, V>* node) const;
  void transplant(Node<K, V>* u, Node<K, V>* v);

  // -- MEMORY MANAGEMENT -- //
  void destroyTree(Node<K, V>* node);
  Node<K, V>* copyTree(Node<K, V>* node, Node<K, V>* parent);

  Node<K, V>* getUncle(Node<K, V>* parent);

  void insertHelper(const key_type& key, const value_type& value);
};

template <typename K, typename V>
Node<K, V>::Node() : key(K()), value(V()) {}

template <typename K, typename V>
Node<K, V>::Node(const key_type& key, const value_type& value)
    : key(key), value(value) {}

template <typename K, typename V>
RedBlackTree<K, V>::RedBlackTree() : root_(nullptr), size_(0) {}

template <typename K, typename V>
RedBlackTree<K, V>::RedBlackTree(const RedBlackTree& other)
    : size_(other.size_) {
  root_ = copyTree(other.root_, nullptr);
}

template <typename K, typename V>
RedBlackTree<K, V>::RedBlackTree(RedBlackTree&& other)
    : root_(other.root_), size_(other.size_) {
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename K, typename V>
RedBlackTree<K, V>::~RedBlackTree() {
  destroyTree(root_);
}

template <typename K, typename V>
void RedBlackTree<K, V>::insert(const key_type& key, const value_type& value) {
  if (empty()) {
    root_ = new Node<K, V>(key, value);
    root_->color = BLACK;
  } else {
    insertHelper(key, value);
  }
  size_++;
}

template <typename K, typename V>
void RedBlackTree<K, V>::insertHelper(const key_type& key,
                                      const value_type& value) {
  // find the correct place
  Node<K, V>* parent = nullptr;
  Node<K, V>* curr = root_;
  while (curr != nullptr) {
    parent = curr;
    if (key < curr->key) {
      curr = curr->left;
    } else if (key > curr->key) {
      curr = curr->right;
    } else {
      curr->value = value;
      return;  // key exists so we will update the value
    }
  }
  Node<K, V>* new_node = new Node<K, V>(key, value);
  new_node->parent = parent;

  if (key < parent->key) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }
  insertFixUp(new_node);
}

template <typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::getUncle(Node<K, V>* current_parent) {
  Node<K, V>* grand_parent = current_parent->parent;
  if (grand_parent == nullptr) {
    return nullptr;
  }
  if (grand_parent->left == current_parent) {
    return grand_parent->right;
  } else {
    return grand_parent->left;
  }
}

template <typename K, typename V>
bool RedBlackTree<K, V>::remove(const key_type& key) {
  if (empty()) {
    return false;
  }
  Node<K, V>* node_to_remove = findNode(key);
  if (node_to_remove == nullptr) {
    return false;
  }
  // TODO: something here
  size_--;
  return true;
}

template <typename K, typename V>
void RedBlackTree<K, V>::clear() {
  destroyTree(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename K, typename V>
typename RedBlackTree<K, V>::value_type* RedBlackTree<K, V>::find(
    const key_type& key) {
  Node<K, V>* node = findNode(key);
  if (node == nullptr) {
    return nullptr;
  } else {
    return &(node->value);
  }
}

template <typename K, typename V>
const typename RedBlackTree<K, V>::value_type* RedBlackTree<K, V>::find(
    const key_type& key) const {
  Node<K, V>* node = findNode(key);
  if (node == nullptr) {
    return nullptr;
  } else {
    return &(node->value);
  }
}

template <typename K, typename V>
bool RedBlackTree<K, V>::contains(const key_type& key) const {
  const value_type* node = find(key);
  if (node == nullptr) {
    return false;
  } else {
    return true;
  }
}

template <typename K, typename V>
typename RedBlackTree<K, V>::size_type RedBlackTree<K, V>::size() const {
  return size_;
}

template <typename K, typename V>
bool RedBlackTree<K, V>::empty() const {
  return size_ == 0;
}

template <typename K, typename V>
void RedBlackTree<K, V>::rotateLeft(Node<K, V>* pivot) {
  // 1. Get references to the key nodes
  Node<K, V>* new_parent = pivot->right;
  Node<K, V>* original_parent = pivot->parent;
  Node<K, V>* inner_subtree = new_parent->left;

  // 2. Perform the pivot: new_parent becomes pivot's parent
  new_parent->left = pivot;

  // 3. Link original_parent to new_parent
  if (original_parent == nullptr) {
    root_ = new_parent;  // new_parent is now the tree's root
  } else if (original_parent->left == pivot) {
    original_parent->left = new_parent;  // new_parent takes pivot's old spot
  } else {
    original_parent->right = new_parent;  // new_parent takes pivot's old spot
  }

  // 4. "Adopt" the inner subtree
  pivot->right = inner_subtree;

  // 5. Update all the parent pointers to match the new structure
  if (inner_subtree != nullptr) {
    inner_subtree->parent = pivot;  // B's parent is now P
  }
  pivot->parent = new_parent;            // P's parent is now X
  new_parent->parent = original_parent;  // X's parent is now G
}

template <typename K, typename V>
void RedBlackTree<K, V>::rotateRight(Node<K, V>* pivot) {
  Node<K, V>* original_parent = pivot->parent;
  Node<K, V>* new_parent = pivot->left;
  // we want to preserves the children's right subtree
  Node<K, V>* sub_tree = new_parent->right;

  new_parent->right = pivot;
  if (original_parent == nullptr) {
    root_ = new_parent;
  } else if (original_parent->left == pivot) {
    original_parent->left = new_parent;
  } else {
    original_parent->right = new_parent;
  }
  pivot->left = sub_tree;
  if (sub_tree != nullptr) {
    sub_tree->parent = pivot;
  }
  new_parent->parent = original_parent;
  pivot->parent = new_parent;
}

template <typename K, typename V>
void RedBlackTree<K, V>::insertFixUp(Node<K, V>* node) {
  while (node != root_ && node->parent->color == RED) {
    Node<K, V>* parent = node->parent;
    Node<K, V>* grand_parent = parent->parent;
    if (grand_parent->left != nullptr && grand_parent->left == parent) {
      Node<K, V>* uncle = grand_parent->right;
      if (uncle != nullptr && uncle->color == RED) {
        uncle->color = BLACK;
        parent->color = BLACK;
        grand_parent->color = RED;
        node = grand_parent;
      } else {
        // L-R
        if (node == parent->right) {
          node = parent;
          rotateLeft(node);
          parent = node->parent;
        }
        // L-L
        COLOR grand_parent_color = grand_parent->color;
        grand_parent->color = parent->color;
        parent->color = grand_parent_color;
        rotateRight(grand_parent);
      }
      // inverse case, right side of the tree
    } else {
      Node<K, V>* uncle = grand_parent->left;
      if (uncle != nullptr && uncle->color == RED) {
        uncle->color = BLACK;
        parent->color = BLACK;
        grand_parent->color = RED;
        node = grand_parent;
      } else {
        // R-L
        if (node == parent->left) {
          node = parent;
          rotateRight(node);
          parent = node->parent;
        }
        // R-R
        COLOR grand_parent_color = grand_parent->color;
        grand_parent->color = parent->color;
        parent->color = grand_parent_color;
        rotateLeft(grand_parent);
      }
    }
  }
  root_->color = BLACK;
}

template <typename K, typename V>
void RedBlackTree<K, V>::deleteFixup(Node<K, V>* node) {}

template <typename K, typename V>
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

template <typename K, typename V>
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

template <typename K, typename V>
void RedBlackTree<K, V>::transplant(Node<K, V>* u, Node<K, V>* v) {}

template <typename K, typename V>
void RedBlackTree<K, V>::destroyTree(Node<K, V>* node) {
  if (node == nullptr) {
    return;
  }
  destroyTree(node->left);
  destroyTree(node->right);
  delete node;
}

template <typename K, typename V>
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

#endif  // REDBLACKTREE_H_
