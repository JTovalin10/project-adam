#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

#include <cstddef>

// Represents the color of a node in the red-black tree.
enum Color { RED, BLACK };

// A node in the red-black tree containing a key-value pair.
//
// Template Parameters:
//   K: The type of the key.
//   V: The type of the value.
template <typename K, typename V>
class Node {
  using key_type = K;
  using value_type = V;

 public:
  Node<K, V>* left = nullptr;
  Node<K, V>* right = nullptr;
  Node<K, V>* parent = nullptr;

  // The key is const to prevent violating the BST structure.
  const key_type key;
  value_type value;
  Color color = RED;

  // Constructs a node with default-initialized key and value.
  Node();

  // Constructs a node with the given key and value.
  //
  // Parameters:
  //   key: The key for this node.
  //   value: The value for this node.
  Node(const key_type& key, const value_type& value);
};

// A self-balancing binary search tree that maintains red-black properties.
//
// Red-black trees guarantee O(log n) time complexity for insertion, deletion,
// and search operations by maintaining the following invariants:
//   1. Every node is either red or black.
//   2. The root is always black.
//   3. All leaves (nullptr) are considered black.
//   4. Red nodes cannot have red children.
//   5. Every path from a node to its descendant leaves contains the same
//      number of black nodes.
//
// Template Parameters:
//   K: The type of the keys. Must support comparison operators.
//   V: The type of the values.
template <typename K, typename V>
class RedBlackTree {
  using key_type = K;
  using value_type = V;
  using size_type = std::size_t;

 public:
  // -- CONSTRUCTION & DESTRUCTION -- //

  // Constructs an empty red-black tree.
  RedBlackTree();

  // Copy constructor. Creates a deep copy of the given tree.
  //
  // Parameters:
  //   other: The tree to copy from.
  RedBlackTree(const RedBlackTree& other);

  // Move constructor. Transfers ownership from the given tree.
  //
  // Parameters:
  //   other: The tree to move from. After the move, other will be empty.
  RedBlackTree(RedBlackTree&& other);

  // Destructor. Deallocates all nodes in the tree.
  ~RedBlackTree();

  // Copy assignment operator. Replaces the contents with a copy of other.
  //
  // Parameters:
  //   other: The tree to copy from.
  //
  // Returns:
  //   A reference to this tree.
  RedBlackTree& operator=(const RedBlackTree& other) {
    if (this == &other) {
      return *this;
    }
    destroyTree(root_);
    root_ = copyTree(other.root_, nullptr);
    size_ = other.size_;
    return *this;
  }

  // Move assignment operator. Replaces the contents by moving from other.
  //
  // Parameters:
  //   other: The tree to move from. After the move, other will be empty.
  //
  // Returns:
  //   A reference to this tree.
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

  // Inserts a key-value pair into the tree.
  // If the key already exists, updates its value.
  //
  // Parameters:
  //   key: The key to insert.
  //   value: The value to associate with the key.
  void insert(const key_type& key, const value_type& value);

  // Removes the node with the given key from the tree.
  //
  // Parameters:
  //   key: The key to remove.
  //
  // Returns:
  //   true if the key was found and removed, false otherwise.
  bool remove(const key_type& key);

  // Removes all elements from the tree, leaving it empty.
  void clear();

  // -- SEARCH & ACCESS -- //

  // Finds the value associated with the given key.
  //
  // Parameters:
  //   key: The key to search for.
  //
  // Returns:
  //   A pointer to the value if found, nullptr otherwise.
  value_type* find(const key_type& key);

  // Finds the value associated with the given key (const version).
  //
  // Parameters:
  //   key: The key to search for.
  //
  // Returns:
  //   A const pointer to the value if found, nullptr otherwise.
  const value_type* find(const key_type& key) const;

  // Checks whether the tree contains the given key.
  //
  // Parameters:
  //   key: The key to search for.
  //
  // Returns:
  //   true if the key exists in the tree, false otherwise.
  bool contains(const key_type& key) const;

  // -- PROPERTIES -- //

  // Returns the number of key-value pairs in the tree.
  size_type size() const;

  // Checks whether the tree is empty.
  //
  // Returns:
  //   true if the tree contains no elements, false otherwise.
  bool empty() const;

 private:
  Node<K, V>* root_;
  size_type size_;

  // -- ROTATION OPERATIONS -- //

  // Performs a left rotation around the given node.
  // Used to maintain red-black tree balance properties.
  //
  // Parameters:
  //   node: The pivot node for the rotation.
  void rotateLeft(Node<K, V>* node);

  // Performs a right rotation around the given node.
  // Used to maintain red-black tree balance properties.
  //
  // Parameters:
  //   node: The pivot node for the rotation.
  void rotateRight(Node<K, V>* node);

  // -- REBALANCING -- //

  // Restores red-black tree properties after insertion.
  // Handles recoloring and rotations to fix red-red violations.
  //
  // Parameters:
  //   node: The newly inserted node (initially colored red).
  void insertFixUp(Node<K, V>* node);

  // Restores red-black tree properties after deletion.
  // Handles recoloring and rotations to fix black-height violations.
  //
  // Parameters:
  //   node: The node that may be causing a black-height violation.
  //         May be nullptr if a black leaf was removed.
  void deleteFixup(Node<K, V>* node, Node<K, V>* parent);

  // Helper function to remove a node with the given key.
  //
  // Parameters:
  //   node: The starting node for the search (unused, kept for interface).
  //   key: The key to remove.
  //
  // Returns:
  //   true if the key was found and removed, false otherwise.
  bool removeHelper(Node<K, V>* node, const key_type& key);

  // -- NODE MANAGEMENT -- //

  // Searches for a node with the given key.
  //
  // Parameters:
  //   key: The key to search for.
  //
  // Returns:
  //   A pointer to the node if found, nullptr otherwise.
  Node<K, V>* findNode(const key_type& key) const;

  // Finds the node with the minimum key in the subtree rooted at node.
  //
  // Parameters:
  //   node: The root of the subtree to search.
  //
  // Returns:
  //   A pointer to the node with the minimum key, or nullptr if node is null.
  Node<K, V>* minimum(Node<K, V>* node) const;

  // Finds the node with the maximum key in the subtree rooted at node.
  //
  // Parameters:
  //   node: The root of the subtree to search.
  //
  // Returns:
  //   A pointer to the node with the maximum key, or nullptr if node is null.
  Node<K, V>* maximum(Node<K, V>* node) const;

  // Replaces the subtree rooted at u with the subtree rooted at v.
  // Updates parent pointers accordingly.
  //
  // Parameters:
  //   u: The node to be replaced.
  //   v: The node to replace u (may be nullptr).
  void transplant(Node<K, V>* u, Node<K, V>* v);

  // -- MEMORY MANAGEMENT -- //

  // Recursively deletes all nodes in the subtree rooted at node.
  //
  // Parameters:
  //   node: The root of the subtree to destroy.
  void destroyTree(Node<K, V>* node);

  // Recursively creates a deep copy of the subtree rooted at node.
  //
  // Parameters:
  //   node: The root of the subtree to copy.
  //   parent: The parent of the new copied node.
  //
  // Returns:
  //   A pointer to the root of the copied subtree.
  Node<K, V>* copyTree(Node<K, V>* node, Node<K, V>* parent);

  // Returns the uncle of the given parent node.
  // The uncle is the sibling of the parent in relation to the grandparent.
  //
  // Parameters:
  //   parent: The parent node whose sibling (uncle) we want to find.
  //
  // Returns:
  //   A pointer to the uncle node, or nullptr if no uncle exists.
  Node<K, V>* getUncle(Node<K, V>* parent);

  // Helper function for inserting a key-value pair into a non-empty tree.
  //
  // Parameters:
  //   key: The key to insert.
  //   value: The value to associate with the key.
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
    size_++;
  } else {
    insertHelper(key, value);
  }
}

template <typename K, typename V>
void RedBlackTree<K, V>::insertHelper(const key_type& key,
                                      const value_type& value) {
  // Find the correct insertion position.
  Node<K, V>* parent = nullptr;
  Node<K, V>* curr = root_;
  while (curr != nullptr) {
    parent = curr;
    if (key < curr->key) {
      curr = curr->left;
    } else if (key > curr->key) {
      curr = curr->right;
    } else {
      // Key already exists, update the value.
      curr->value = value;
      return;
    }
  }

  // Create and link the new node.
  Node<K, V>* new_node = new Node<K, V>(key, value);
  new_node->parent = parent;

  if (key < parent->key) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }

  // Restore red-black properties.
  insertFixUp(new_node);
  size_++;
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
  return removeHelper(root_, key);
}

template <typename K, typename V>
bool RedBlackTree<K, V>::removeHelper(Node<K, V>* node, const key_type& key) {
  // Find the node to delete.
  Node<K, V>* curr = root_;
  while (curr != nullptr) {
    if (key < curr->key) {
      curr = curr->left;
    } else if (key > curr->key) {
      curr = curr->right;
    } else {
      break;
    }
  }

  // Key not found.
  if (curr == nullptr) {
    return false;
  }

  Node<K, V>* node_to_fix;
  Node<K, V>* node_to_fix_parent = nullptr;
  Color original_color = curr->color;

  // Case 1: Node has no left child.
  if (curr->left == nullptr) {
    node_to_fix = curr->right;
    node_to_fix_parent = curr->parent;
    transplant(curr, curr->right);
  }
  // Case 2: Node has no right child.
  else if (curr->right == nullptr) {
    node_to_fix = curr->left;
    node_to_fix_parent = curr->parent;
    transplant(curr, curr->left);
  }
  // Case 3: Node has two children.
  else {
    Node<K, V>* new_curr = minimum(curr->right);
    original_color = new_curr->color;
    node_to_fix = new_curr->right;

    if (curr->right != new_curr) {
      node_to_fix_parent = new_curr->parent;
      transplant(new_curr, new_curr->right);
      new_curr->right = curr->right;
      new_curr->right->parent = new_curr;
    } else {
      node_to_fix_parent = new_curr;
    }

    transplant(curr, new_curr);
    new_curr->left = curr->left;
    new_curr->left->parent = new_curr;
    new_curr->color = curr->color;
  }

  delete curr;

  // If we removed a black node, fix the red-black properties.
  if (original_color == BLACK) {
    deleteFixup(node_to_fix, node_to_fix_parent);
  }

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
  // Get references to the key nodes.
  Node<K, V>* new_parent = pivot->right;
  Node<K, V>* original_parent = pivot->parent;
  Node<K, V>* inner_subtree = new_parent->left;

  // Perform the pivot: new_parent becomes pivot's parent.
  new_parent->left = pivot;

  // Link original_parent to new_parent.
  if (original_parent == nullptr) {
    root_ = new_parent;
  } else if (original_parent->left == pivot) {
    original_parent->left = new_parent;
  } else {
    original_parent->right = new_parent;
  }

  // Adopt the inner subtree.
  pivot->right = inner_subtree;

  // Update all parent pointers to match the new structure.
  if (inner_subtree != nullptr) {
    inner_subtree->parent = pivot;
  }
  pivot->parent = new_parent;
  new_parent->parent = original_parent;
}

template <typename K, typename V>
void RedBlackTree<K, V>::rotateRight(Node<K, V>* pivot) {
  Node<K, V>* original_parent = pivot->parent;
  Node<K, V>* new_parent = pivot->left;
  // Preserve the new parent's right subtree.
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
  // Continue fixing until we reach the root or the parent is black.
  while (node != root_ && node->parent->color == RED) {
    Node<K, V>* parent = node->parent;
    Node<K, V>* grand_parent = parent->parent;

    // Case: Parent is left child of grandparent.
    if (grand_parent->left != nullptr && grand_parent->left == parent) {
      Node<K, V>* uncle = grand_parent->right;

      // Case 1: Uncle is red - recolor.
      if (uncle != nullptr && uncle->color == RED) {
        uncle->color = BLACK;
        parent->color = BLACK;
        grand_parent->color = RED;
        node = grand_parent;
      } else {
        // Case 2: Node is right child (L-R case) - convert to L-L.
        if (node == parent->right) {
          node = parent;
          rotateLeft(node);
          parent = node->parent;
        }

        // Case 3: Node is left child (L-L case) - rotate and recolor.
        Color grand_parent_color = grand_parent->color;
        grand_parent->color = parent->color;
        parent->color = grand_parent_color;
        rotateRight(grand_parent);
      }
    }
    // Mirror case: Parent is right child of grandparent.
    else {
      Node<K, V>* uncle = grand_parent->left;

      // Case 1: Uncle is red - recolor.
      if (uncle != nullptr && uncle->color == RED) {
        uncle->color = BLACK;
        parent->color = BLACK;
        grand_parent->color = RED;
        node = grand_parent;
      } else {
        // Case 2: Node is left child (R-L case) - convert to R-R.
        if (node == parent->left) {
          node = parent;
          rotateRight(node);
          parent = node->parent;
        }

        // Case 3: Node is right child (R-R case) - rotate and recolor.
        Color grand_parent_color = grand_parent->color;
        grand_parent->color = parent->color;
        parent->color = grand_parent_color;
        rotateLeft(grand_parent);
      }
    }
  }

  // Ensure root is always black.
  root_->color = BLACK;
}

template <typename K, typename V>
void RedBlackTree<K, V>::deleteFixup(Node<K, V>* node, Node<K, V>* parent) {
  // Continue fixing until node is the root or is red.
  while (node != root_ && (node == nullptr || node->color == BLACK)) {
    // Now we have parent even when node is nullptr!

    // Case: Node is the left child.
    if (parent->left == node) {
      Node<K, V>* sibling = parent->right;

      if (sibling == nullptr) break;

      // Case 1: Sibling is red
      if (sibling->color == RED) {
        sibling->color = BLACK;
        parent->color = RED;
        rotateLeft(parent);
        sibling = parent->right;
      }

      // Case 2: Sibling BLACK, both nephews BLACK
      if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
          (sibling->right == nullptr || sibling->right->color == BLACK)) {
        sibling->color = RED;
        node = parent;
        parent = node->parent;  // Update parent for next iteration
      } else {
        // Case 3: Outer nephew BLACK, inner nephew RED
        if (sibling->right == nullptr || sibling->right->color == BLACK) {
          if (sibling->left != nullptr) {
            sibling->left->color = BLACK;
          }
          sibling->color = RED;
          rotateRight(sibling);
          sibling = parent->right;
        }

        // Case 4: Outer nephew RED
        sibling->color = parent->color;
        parent->color = BLACK;
        if (sibling->right != nullptr) {
          sibling->right->color = BLACK;
        }
        rotateLeft(parent);
        node = root_;
      }
    }
    // Mirror case: Node is the right child
    else {
      Node<K, V>* sibling = parent->left;

      if (sibling == nullptr) break;

      // Case 1: Sibling is red
      if (sibling->color == RED) {
        sibling->color = BLACK;
        parent->color = RED;
        rotateRight(parent);
        sibling = parent->left;
      }

      // Case 2: Sibling BLACK, both nephews BLACK
      if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
          (sibling->right == nullptr || sibling->right->color == BLACK)) {
        sibling->color = RED;
        node = parent;
        parent = node->parent;  // Update parent for next iteration
      } else {
        // Case 3: Outer nephew BLACK, inner nephew RED
        if (sibling->left == nullptr || sibling->left->color == BLACK) {
          if (sibling->right != nullptr) {
            sibling->right->color = BLACK;
          }
          sibling->color = RED;
          rotateLeft(sibling);
          sibling = parent->left;
        }

        // Case 4: Outer nephew RED
        sibling->color = parent->color;
        parent->color = BLACK;
        if (sibling->left != nullptr) {
          sibling->left->color = BLACK;
        }
        rotateRight(parent);
        node = root_;
      }
    }
  }

  if (node != nullptr) {
    node->color = BLACK;
  }
}

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
Node<K, V>* RedBlackTree<K, V>::maximum(Node<K, V>* node) const {
  if (node == nullptr) {
    return nullptr;
  }

  Node<K, V>* curr = node;
  while (curr != nullptr && curr->right != nullptr) {
    curr = curr->right;
  }
  return curr;
}

template <typename K, typename V>
void RedBlackTree<K, V>::transplant(Node<K, V>* u, Node<K, V>* v) {
  // u is the root.
  if (u->parent == nullptr) {
    root_ = v;
  }
  // u is the left child.
  else if (u->parent->left == u) {
    u->parent->left = v;
  }
  // u is the right child.
  else {
    u->parent->right = v;
  }

  if (v != nullptr) {
    v->parent = u->parent;
  }
}

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
