#ifndef TRIE_H_
#define TRIE_H_

#include <cstddef>
#include <string>
#include <unordered_map>
#include <utility>

class TrieNode {
    public:
    std::unordered_map<char, TrieNode*> children;
    bool end_of_word;

    /**
     * Constructs an empty TrieNode
     */
    TrieNode();
};

class Trie {
    using string = std::string;
    public:

    /**
     * Initalizes an empty Trie
     */
    Trie();

    /**
     * Initalizes a Trie by copying the given Trie
     * 
     * ARGS:
     * other: the Trie that will be deep copied
     */
    Trie(const Trie& other);

    /**
     * Initalizes a Trie by stealing from the other Trie
     */
    Trie(Trie&& other);

    /**
     * Deconstructs the Trie
     */
    ~Trie();

    /**
     * Copy assignment constructor that replaces this Trie by copying the given other Trie
     * 
     * ARGS:
     * other: the trie that will be copied
     */
    Trie& operator=(const Trie& other) {
        if (this == &other) {
            return *this;
        }
        Trie temp(other);
        std::swap(root_, temp.root_);
        return *this;
    }

    /**
     * Move assignment constructor - replaces this Trie by stealing from the other Trie
     */
    Trie& operator=(Trie&& other) {
        if (this == &other) {
            return *this;
        }
        destroyHelper(root_);
        root_ = other.root_;
        other.root_ = nullptr;
        return *this;
    }

    /**
     * adds the given word into the Trie
     * 
     * ARGS:
     * word: the word that will be added into the trie
     * 
     */
    void insert(const string& word);

    /**
     * Iterates through the Trie to see if the word is in it
     * 
     * ARGS:
     * word: the word that we are looking for inside the Trie
     * 
     * RETURNS:
     * true if the entire word is in the trie, else false
     */
    bool search(const string& word);

    /**
     * Iterates through the Trie to see if the entire word is in the Trie.
     * It can be a prefix of a word or the entire word
     * 
     * ARGS:
     * word: the word that we are looking for in the Trie
     * 
     * RETURNS:
     * true if the prefix is in the Trie, else false
     */
    bool prefix(const string& word);

    private:
    TrieNode* root_;
    
    /**
     * Helper method to recurivsely copy the Trie
     */
    TrieNode* copyHelper(const TrieNode* node);

    /**
     * Helper method to recusrively deallocate TrieNodes
     */
    void destroyHelper(TrieNode* node);

};

TrieNode::TrieNode() : end_of_word(false) {}

Trie::Trie() {
    root_ = new TrieNode();
}

Trie::Trie(const Trie& other) {
    root_ = copyHelper(other.root_);
}

Trie::Trie(Trie&& other) {
    root_ = other.root_;
    other.root_ = nullptr;
}

Trie::~Trie() {
    destroyHelper(root_);
}

void Trie::insert(const string& word) {
    TrieNode* curr = root_;
    for (char letter : word) {
        if (curr->children.find(letter) == curr->children.end()) {
            curr->children[letter] = new TrieNode();
        }
        curr = curr->children[letter];
    }
    curr->end_of_word = true;
}

bool Trie::search(const string& word) {
    if (root_ == nullptr) {
        return false;
    }
    TrieNode* curr = root_;
    for (char letter : word) {
        auto it = curr->children.find(letter);
        if (it == curr->children.end()) {
            return false;
        }
        curr = it->second;
    }
    return curr->end_of_word;
}

bool Trie::prefix(const string& word) {
    if (root_ == nullptr) {
        return false;
    }
    TrieNode* curr = root_;
    for (char letter : word) {
        auto it = curr->children.find(letter);
        if (it == curr->children.end()) {
            return false;
        }
        curr = it->second;
    }
    return true;
}

TrieNode* Trie::copyHelper(const TrieNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    TrieNode* new_node = new TrieNode();
    new_node->end_of_word = node->end_of_word;
    for (const auto& pair : node->children) {
        new_node->children[pair.first] = copyHelper(pair.second);
    }
    return new_node;
}

void Trie::destroyHelper(TrieNode* node) {
    if (node == nullptr) {
        return;
    }
    for (const auto& pair : node->children) {
        destroyHelper(pair.second);
    }
    delete node;
}

#endif // TRIE_H_
