#include "gtest/gtest.h"
#include "Trie.h"

TEST(TrieTest, EmptyConstructor) {
    Trie t;

    // An empty trie should not find any words
    ASSERT_FALSE(t.search("a"));
    ASSERT_FALSE(t.search("hello"));
    ASSERT_FALSE(t.search("anyword"));

    // An empty trie should not have any prefixes
    ASSERT_FALSE(t.prefix("a"));
    ASSERT_FALSE(t.prefix("b"));
    ASSERT_FALSE(t.prefix("hello"));

    // Test the empty string case:
    // search("") should be false because the root node's
    // 'end_of_word' flag is false.
    ASSERT_FALSE(t.search(""));

    // prefix("") should be true because the root node exists,
    // and an empty string is a valid prefix.
    ASSERT_TRUE(t.prefix(""));
}

TEST(TrieTest, copy_constructor) {
    Trie t;
    t.insert("DEADBEEF");
    Trie t2 = t;
    ASSERT_TRUE(t2.search("DEADBEEF"));
}

TEST(TrieTest, move_constructor) {
    Trie t;
    t.insert("DEADBEEF");
    Trie t2 = std::move(t);
    ASSERT_TRUE(t2.search("DEADBEEF"));
    ASSERT_FALSE(t.search("DEADBEEF"));
}

TEST(TrieTest, copy_assignment_operator) {
    Trie t;
    t.insert("DEADBEEF");
    Trie t2;
    t2.insert("HELLO");
    t2 = t;
    ASSERT_TRUE(t2.search("DEADBEEF"));
    ASSERT_FALSE(t2.search("HELLO"));
    ASSERT_TRUE(t.search("DEADBEEF"));
}

TEST(TrieTest, move_assignment_operator) {
    Trie t;
    t.insert("DEADBEEF");
    Trie t2;
    t2.insert("HELLO");
    t2 = std::move(t);
    ASSERT_TRUE(t2.search("DEADBEEF"));
    ASSERT_FALSE(t2.search("HELLO"));
    ASSERT_FALSE(t.search("DEADBEEF"));
}

TEST(TrieTest, insert) {
    Trie t;
    t.insert("DEADBEEF");
    ASSERT_TRUE(t.search("DEADBEEF"));
    t.insert("ROASTBEEF");
    ASSERT_TRUE(t.search("ROASTBEEF"));
}

TEST(TrieTest, Search) {
    Trie t;
    t.insert("DEADBEEF");
    ASSERT_TRUE(t.search("DEADBEEF"));
    t.insert("ROASTBEEF");
    ASSERT_TRUE(t.search("ROASTBEEF"));
    ASSERT_FALSE(t.search("DEADBEE"));
    ASSERT_FALSE(t.search("ROAST"));
}

TEST(TrieTest, prefix) {
    Trie t;
    t.insert("DEADBEEF");
    ASSERT_TRUE(t.prefix("DEADBEEF"));
    t.insert("ROASTBEEF");
    ASSERT_TRUE(t.prefix("ROASTBEEF"));
    ASSERT_TRUE(t.prefix("DEADBEE"));
    ASSERT_TRUE(t.prefix("ROAST"));

    ASSERT_FALSE(t.prefix("HELLO"));
    ASSERT_FALSE(t.prefix("DEADCOW"));
}