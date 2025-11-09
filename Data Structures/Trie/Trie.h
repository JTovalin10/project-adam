#ifndef TRIE_H_
#define TRIE_H_

#include <stdexcept>
#include <cstddef>
#include "../Hash_Table/Hash_Table.h"

class TrieNode {
    public:
    HashTable<char, TrieNode*> children;
    bool end_of_word;

    TrieNode();
    ~TrieNode();
};

class Trie {
    using string = std::string;
    public:

    Trie();

    Trie(const Trie& other);

    Trie(Trie&& other);

    ~Trie();

    Trie& operator=(const Trie& other);

    Trie& operator=(Trie&& other);

    void insert(const string& word);

    bool search(const string& word);

    void remove(const string& word);

    private:
    TrieNode trie_;
    
    TrieNode* copyHelper(const TrieNode* node);

    void destroyHelper(TrieNode* node);
};

#endif // TRIE_H_
