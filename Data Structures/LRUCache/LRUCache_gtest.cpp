#include "LRUCache.h"
#include "gtest/gtest.h"

// ============= BASIC FUNCTIONALITY TESTS =============

TEST(LRUCacheTest, BasicConstructor) {
    LRUCache<int, int> lru(1);
    lru.put(0, 0);
    ASSERT_EQ(lru.get(0), 0);
}

TEST(LRUCacheTest, BasicEviction) {
    LRUCache<int, int> lru(1);
    lru.put(0, 0);
    ASSERT_EQ(lru.get(0), 0);
    
    lru.put(1, 1);  // Should evict key 0
    ASSERT_THROW(lru.get(0), std::out_of_range);
    ASSERT_EQ(lru.get(1), 1);
}

TEST(LRUCacheTest, GetNonExistentKey) {
    LRUCache<int, int> lru(5);
    ASSERT_THROW(lru.get(999), std::out_of_range);
}

TEST(LRUCacheTest, MultipleInserts) {
    LRUCache<int, int> lru(10);
    for (int i = 0; i < 5; i++) {
        lru.put(i, i * 10);
    }
    
    ASSERT_EQ(lru.get(0), 0);
    ASSERT_EQ(lru.get(1), 10);
    ASSERT_EQ(lru.get(2), 20);
    ASSERT_EQ(lru.get(3), 30);
    ASSERT_EQ(lru.get(4), 40);
}

TEST(LRUCacheTest, UpdateExistingKey) {
    LRUCache<int, int> lru(3);
    lru.put(1, 100);
    lru.put(2, 200);
    lru.put(1, 999);  // Update key 1
    
    ASSERT_EQ(lru.get(1), 999);
    ASSERT_EQ(lru.get(2), 200);
}

// ============= LRU BEHAVIOR TESTS =============

TEST(LRUCacheTest, LRUEvictionOrder) {
    LRUCache<int, int> lru(3);
    lru.put(1, 1);
    lru.put(2, 2);
    lru.put(3, 3);
    
    // Cache is now: [1, 2, 3]
    lru.put(4, 4);  // Evicts 1 (least recently used)
    
    ASSERT_THROW(lru.get(1), std::out_of_range);
    ASSERT_EQ(lru.get(2), 2);
    ASSERT_EQ(lru.get(3), 3);
    ASSERT_EQ(lru.get(4), 4);
}

TEST(LRUCacheTest, GetRefreshesRecency) {
    LRUCache<int, int> lru(3);
    lru.put(1, 1);
    lru.put(2, 2);
    lru.put(3, 3);
    
    // Access key 1 to make it most recently used
    lru.get(1);
    
    // Now order is: [2, 3, 1]
    lru.put(4, 4);  // Should evict 2, not 1
    
    ASSERT_EQ(lru.get(1), 1);  // Still present
    ASSERT_THROW(lru.get(2), std::out_of_range);  // Evicted
    ASSERT_EQ(lru.get(3), 3);
    ASSERT_EQ(lru.get(4), 4);
}

TEST(LRUCacheTest, ComplexLRUScenario) {
    LRUCache<int, int> lru(2);
    lru.put(1, 1);
    lru.put(2, 2);
    ASSERT_EQ(lru.get(1), 1);  // 1 becomes most recent
    
    lru.put(3, 3);  // Evicts 2
    ASSERT_THROW(lru.get(2), std::out_of_range);
    
    lru.put(4, 4);  // Evicts 1
    ASSERT_THROW(lru.get(1), std::out_of_range);
    
    ASSERT_EQ(lru.get(3), 3);
    ASSERT_EQ(lru.get(4), 4);
}

// ============= COPY CONSTRUCTOR TESTS =============

TEST(LRUCacheTest, CopyConstructorBasic) {
    LRUCache<int, int> lru(3);
    lru.put(0, 0);
    lru.put(1, 1);
    
    LRUCache<int, int> l2 = lru;
    
    ASSERT_EQ(l2.get(0), 0);
    ASSERT_EQ(l2.get(1), 1);
    
    // Original should still work
    ASSERT_EQ(lru.get(0), 0);
    ASSERT_EQ(lru.get(1), 1);
}

TEST(LRUCacheTest, CopyConstructorIndependence) {
    LRUCache<int, int> lru(2);
    lru.put(0, 0);
    
    LRUCache<int, int> l2 = lru;
    
    // Modify original
    lru.put(1, 1);
    lru.put(2, 2);  // Evicts 0
    
    // Copy should still have original data
    ASSERT_EQ(l2.get(0), 0);
    ASSERT_THROW(lru.get(0), std::out_of_range);
}

// ============= MOVE CONSTRUCTOR TESTS =============

TEST(LRUCacheTest, MoveConstructorBasic) {
    LRUCache<int, int> l(2);
    l.put(0, 0);
    l.put(1, 1);
    
    LRUCache<int, int> lru = std::move(l);
    
    ASSERT_EQ(lru.get(0), 0);
    ASSERT_EQ(lru.get(1), 1);
}

TEST(LRUCacheTest, MoveConstructorEviction) {
    LRUCache<int, int> l(1);
    l.put(0, 0);
    
    LRUCache<int, int> lru = std::move(l);
    
    ASSERT_EQ(lru.get(0), 0);
    lru.put(1, 1);
    ASSERT_EQ(lru.get(1), 1);
    ASSERT_THROW(lru.get(0), std::out_of_range);
}

// ============= COPY ASSIGNMENT TESTS =============

TEST(LRUCacheTest, CopyAssignmentBasic) {
    LRUCache<int, int> lru(3);
    lru.put(0, 0);
    lru.put(1, 1);
    
    LRUCache<int, int> l2(5);
    l2.put(10, 10);
    l2.put(20, 20);
    
    l2 = lru;  // Copy assignment
    
    ASSERT_THROW(l2.get(10), std::out_of_range);
    ASSERT_THROW(l2.get(20), std::out_of_range);
    ASSERT_EQ(l2.get(0), 0);
    ASSERT_EQ(l2.get(1), 1);
}

TEST(LRUCacheTest, CopyAssignmentIndependence) {
    LRUCache<int, int> lru(2);
    lru.put(0, 0);
    
    LRUCache<int, int> l2(2);
    l2 = lru;
    
    // Modify original
    lru.put(1, 1);
    lru.put(2, 2);
    
    // l2 should be unaffected
    ASSERT_EQ(l2.get(0), 0);
    ASSERT_THROW(l2.get(1), std::out_of_range);
}

TEST(LRUCacheTest, CopyAssignmentSelfAssignment) {
    LRUCache<int, int> lru(2);
    lru.put(0, 0);
    lru.put(1, 1);
    
    lru = lru;  // Self-assignment
    
    ASSERT_EQ(lru.get(0), 0);
    ASSERT_EQ(lru.get(1), 1);
}

// ============= MOVE ASSIGNMENT TESTS =============

TEST(LRUCacheTest, MoveAssignmentBasic) {
    LRUCache<int, int> lru(3);
    lru.put(0, 0);
    lru.put(1, 1);
    
    LRUCache<int, int> l2(5);
    l2.put(10, 10);
    l2.put(20, 20);
    
    l2 = std::move(lru);  // Move assignment
    
    ASSERT_THROW(l2.get(10), std::out_of_range);
    ASSERT_THROW(l2.get(20), std::out_of_range);
    ASSERT_EQ(l2.get(0), 0);
    ASSERT_EQ(l2.get(1), 1);
}

TEST(LRUCacheTest, MoveAssignmentSelfAssignment) {
    LRUCache<int, int> lru(2);
    lru.put(0, 0);
    lru.put(1, 1);
    
    lru = std::move(lru);  // Self-assignment
    
    ASSERT_EQ(lru.get(0), 0);
    ASSERT_EQ(lru.get(1), 1);
}

// ============= EDGE CASES =============

TEST(LRUCacheTest, CapacityOne) {
    LRUCache<int, int> lru(1);
    lru.put(1, 100);
    ASSERT_EQ(lru.get(1), 100);
    
    lru.put(2, 200);
    ASSERT_THROW(lru.get(1), std::out_of_range);
    ASSERT_EQ(lru.get(2), 200);
    
    lru.put(3, 300);
    ASSERT_THROW(lru.get(2), std::out_of_range);
    ASSERT_EQ(lru.get(3), 300);
}

TEST(LRUCacheTest, LargeCapacity) {
    LRUCache<int, int> lru(100);
    for (int i = 0; i < 100; i++) {
        lru.put(i, i * 2);
    }
    
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(lru.get(i), i * 2);
    }
    
    // Adding one more should evict the oldest
    lru.put(100, 200);
    ASSERT_THROW(lru.get(0), std::out_of_range);
    ASSERT_EQ(lru.get(100), 200);
}

TEST(LRUCacheTest, StringKeys) {
    LRUCache<std::string, int> lru(3);
    lru.put("apple", 1);
    lru.put("banana", 2);
    lru.put("cherry", 3);
    
    ASSERT_EQ(lru.get("apple"), 1);
    ASSERT_EQ(lru.get("banana"), 2);
    ASSERT_EQ(lru.get("cherry"), 3);
    
    lru.put("date", 4);
    ASSERT_THROW(lru.get("apple"), std::out_of_range);
}

TEST(LRUCacheTest, RepeatedUpdates) {
    LRUCache<int, int> lru(2);
    lru.put(1, 1);
    lru.put(1, 10);
    lru.put(1, 100);
    lru.put(1, 1000);
    
    ASSERT_EQ(lru.get(1), 1000);
}

// ============= STRESS TESTS =============

TEST(LRUCacheTest, ManyOperations) {
    LRUCache<int, int> lru(10);
    
    // Insert 100 items (will evict oldest 90)
    for (int i = 0; i < 100; i++) {
        lru.put(i, i);
    }
    
    // Only last 10 should remain
    for (int i = 0; i < 90; i++) {
        ASSERT_THROW(lru.get(i), std::out_of_range);
    }
    for (int i = 90; i < 100; i++) {
        ASSERT_EQ(lru.get(i), i);
    }
}

TEST(LRUCacheTest, InterleavedGetPut) {
    LRUCache<int, int> lru(3);
    lru.put(1, 1);
    lru.put(2, 2);
    ASSERT_EQ(lru.get(1), 1);
    lru.put(3, 3);
    ASSERT_EQ(lru.get(2), 2);
    lru.put(4, 4);
    
    ASSERT_THROW(lru.get(1), std::out_of_range);
    ASSERT_EQ(lru.get(2), 2);
    ASSERT_EQ(lru.get(3), 3);
    ASSERT_EQ(lru.get(4), 4);
}