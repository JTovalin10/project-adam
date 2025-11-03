#include "gtest/gtest.h"
#include "LinkedList.h"

TEST(LinkedListTest, empty_constructor) {
    LinkedList<int> list;
    ASSERT_EQ(list.empty(), true);
}

TEST(LinkedListTest, copy_constructor) {
    LinkedList<int> list;
    for (int i = 0; i < 10; i++) {
        list.push_back(i);
    }
    LinkedList<int> dupeList = list;
    ASSERT_EQ(list.size(), dupeList.size());
    ASSERT_EQ(dupeList[0], 0);
    ASSERT_EQ(dupeList[1], 1);
    ASSERT_EQ(dupeList[2], 2);
    ASSERT_EQ(dupeList[3], 3);
    ASSERT_EQ(dupeList[4], 4);
    ASSERT_EQ(dupeList[5], 5);
    ASSERT_EQ(dupeList[6], 6);
    ASSERT_EQ(dupeList[7], 7);
    ASSERT_EQ(dupeList[8], 8);
    ASSERT_EQ(dupeList[9], 9);
}

TEST(LinkedListTest, move_constructor) {
    LinkedList<int> list1;
    for (int i = 0; i < 3; i++) {
        list1.push_back(i);
    }
    LinkedList<int> list2 = std::move(list1);
    ASSERT_EQ(list1.size(), 0);
    ASSERT_TRUE(list1.empty());
    ASSERT_THROW(list1.front(), std::out_of_range);
    ASSERT_THROW(list1.back(), std::out_of_range);

    ASSERT_EQ(list2.size(), 3);
    ASSERT_FALSE(list2.empty());
    ASSERT_EQ(list2[0], 0);
    ASSERT_EQ(list2[1], 1);
    ASSERT_EQ(list2[2], 2);
}

TEST(LinkedListTest, assignment_operator) {
    LinkedList<int> list1;
    for (int i = 0; i < 3; i++) {
        list1.push_back(i);
    }
    LinkedList<int> list2;
    for (int i = 3; i < 6; i++) {
        list2.push_back(i);
    }
    list2 = list1;
    ASSERT_EQ(list2[0], 0);
    ASSERT_EQ(list2[1], 1);
    ASSERT_EQ(list2[2], 2);
}

TEST(LinkedListTest, move_assignment_operator) {
    LinkedList<int> list1;
    for (int i = 0; i < 3; i++) {
        list1.push_back(i);
    }

}

TEST(LinkedListTest, operator_bracket) {
    LinkedList<int> list;

    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    ASSERT_EQ(list[0], 0);
    ASSERT_EQ(list[1], 1);
    ASSERT_EQ(list[2], 2);

    list[0] = 9;
    list[1] = 8;
    list[2] = 7;
    ASSERT_EQ(list[0], 9);
    ASSERT_EQ(list[1], 8);
    ASSERT_EQ(list[2], 7);
    ASSERT_THROW(list[3], std::out_of_range);
    ASSERT_THROW(list[4] = 100, std::out_of_range);
}

TEST(LinkedListTest, const_operator_bracket) {
    LinkedList<int> temp_list;

    for (int i = 0; i < 3; i++) {
        temp_list.push_back(i);
    }
    const LinkedList<int> list = temp_list;
    ASSERT_EQ(list[0], 0);
    ASSERT_EQ(list[1], 1);
    ASSERT_EQ(list[2], 2);
}

TEST(LinkedListTest, push_front) {
    LinkedList<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_front(i);
    }
    ASSERT_EQ(list[0], 2);
    ASSERT_EQ(list[1], 1);
    ASSERT_EQ(list[2], 0);
}

TEST(LinkedListTest, pop_front) {
    LinkedList<int> list;
    ASSERT_THROW(list.pop_front(), std::out_of_range);
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    ASSERT_EQ(list[0], 0);
    list.pop_front();
    ASSERT_EQ(list[0], 1);
    list.pop_front();
    ASSERT_EQ(list[0], 2);
    list.pop_front();
    ASSERT_THROW(list[0], std::out_of_range);
}

TEST(LinkedListTest, push_back) {
    LinkedList<int> list;
    ASSERT_THROW(list[0], std::out_of_range);
    list.push_back(1);
    ASSERT_EQ(list[0], 1);
    list.push_back(2);
    ASSERT_EQ(list[1], 2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    
    ASSERT_EQ(list[2], 3);
    ASSERT_EQ(list[3], 4);
    ASSERT_EQ(list[4], 5);
    ASSERT_THROW(list[6], std::out_of_range);
}

TEST(LinkedListTest, pop_back) {
    LinkedList<int> list;
    ASSERT_THROW(list.pop_back(), std::out_of_range);
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list[2], 2);

    list.pop_back();
    ASSERT_EQ(list[1], 1);
    ASSERT_EQ(list.size(), 2);
    ASSERT_THROW(list[2], std::out_of_range);

    list.pop_back();
    ASSERT_EQ(list[0], 0);
    ASSERT_EQ(list.size(), 1);
    ASSERT_THROW(list[1], std::out_of_range);

    list.pop_back();
    ASSERT_EQ(list.size(), 0);
    ASSERT_THROW(list[0], std::out_of_range);
    ASSERT_THROW(list.pop_back(), std::out_of_range);
}

TEST(LinkedListTest, insert) {
    LinkedList<int> list;
    list.insert(100,  0); // val, index
    ASSERT_EQ(list[0], 100);
    list.insert(200, 1);
    ASSERT_EQ(list[1], 200);
    list.insert(300, 2);
    ASSERT_EQ(list[2], 300);
    list.insert(400, 3);
    ASSERT_EQ(list[3], 400);
    list.insert(500, 2);
    ASSERT_EQ(list[0], 100);
    ASSERT_EQ(list[1], 200);
    ASSERT_EQ(list[2], 500);
    ASSERT_EQ(list[3], 300);
    ASSERT_EQ(list[4], 400);
}

TEST(LinkedListTest, erase) {
    LinkedList<int> list;
    /// test out of range
    ASSERT_THROW(list.erase(0), std::out_of_range);
    //// now with list we will test removing at the front
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    list.erase(0);
    ASSERT_EQ(list[0], 1);
    ASSERT_EQ(list[1], 2);

    LinkedList<int> list2;
    for (int i = 0; i < 3; i++) {
        list2.push_back(i);
    }
    list2.erase(1);
    ASSERT_EQ(list2[0], 0);
    ASSERT_EQ(list2[1], 2);

    LinkedList<int> list3;
    for (int i = 0; i < 3; i++) {
        list3.push_back(i);
    }
    list3.erase(2);
    ASSERT_EQ(list3[0], 0);
    ASSERT_EQ(list3[1], 1);
    EXPECT_THROW(list3[2], std::out_of_range);
}

TEST(LinkedListTest, find) {
    LinkedList<int> list;
    ASSERT_EQ(list.find(0), nullptr);
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    Node<int>* node1 = list.find(0);
    Node<int>* node2 = list.find(1);
    Node<int>* node3 = list.find(2);
    ASSERT_EQ(node1->val, 0);
    ASSERT_EQ(node1->next, node2);

    ASSERT_EQ(node2->val, 1);
    ASSERT_EQ(node2->next, node3);

    ASSERT_NE(node3->next, nullptr);
    ASSERT_EQ(node3->val, 2);
}

TEST(LinkedListTest, FindConst) {
    LinkedList<int> temp;
    const LinkedList<int> emptyTest = temp;
    ASSERT_EQ(emptyTest.find(0), nullptr);
    for (int i = 0; i < 3; i++) {
        temp.push_back(i);
    }
    const LinkedList<int> list = temp;
    
    const Node<int>* node1 = list.find(0);
    const Node<int>* node2 = list.find(1);
    const Node<int>* node3 = list.find(2);
    ASSERT_EQ(node1->val, 0);
    ASSERT_EQ(node1->next, node2);

    ASSERT_EQ(node2->val, 1);
    ASSERT_EQ(node2->next, node3);

    ASSERT_NE(node3->next, nullptr);
    ASSERT_EQ(node3->val, 2);
}

TEST(LinkedListTest, size) {
    LinkedList<int> list;
    ASSERT_EQ(list.size(), 0);
    list.push_back(0);
    ASSERT_EQ(list.size(), 1);
    list.push_back(1);
    list.push_back(2);
    ASSERT_EQ(list.size(), 3);
    const LinkedList<int> list2 = list;
    ASSERT_EQ(list2.size(), 3);
}

TEST(LinkedListTest, empty) {
    LinkedList<int> list1;
    const LinkedList<int> list2;
    ASSERT_TRUE(list1.empty());
    ASSERT_TRUE(list2.empty());
    list1.push_back(0);
    const LinkedList<int> list3 = list1;
    ASSERT_FALSE(list1.empty());
    ASSERT_FALSE(list3.empty());
}

TEST(LinkedListTesting, front) {
    LinkedList<int> list;
    ASSERT_THROW(list.front(), std::out_of_range);
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    ASSERT_EQ(list.front(), 0);
}

TEST(LinkedListTesting, frontconst) {
    LinkedList<int> list;
    const LinkedList<int> empty_list = list;
    ASSERT_THROW(empty_list.front(), std::out_of_range);
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    const LinkedList<int> list2 = list;
    ASSERT_EQ(list2.front(), 0);
}

TEST(LinkedListTesting, back) {
    LinkedList<int> list;
    ASSERT_THROW(list.back(), std::out_of_range);
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    ASSERT_EQ(list.back(), 2);
}

TEST(LinkedListTesting, backconst) {
    LinkedList<int> list;
    const LinkedList<int> empty_list = list;
    ASSERT_THROW(empty_list.back(), std::out_of_range);
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    const LinkedList<int> list2 = list;
    ASSERT_EQ(list2.back(), 2);
}

TEST(LinkedListIterator, hasNext) {
    LinkedList<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    
    LinkedList<int>::Iterator iter = list.begin();
    
    // Test iteration through all elements
    ASSERT_TRUE(iter.hasNext());
    ASSERT_EQ(iter.next(), 1);
    
    ASSERT_TRUE(iter.hasNext());
    ASSERT_EQ(iter.next(), 2);
    
    ASSERT_FALSE(iter.hasNext());
}

TEST(LinkedListTest, begin) {
    LinkedList<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    LinkedList<int>::Iterator iter = list.begin();
    ASSERT_EQ(*iter, 0);  // begin() should point to first element
    ASSERT_EQ(iter.next(), 1);  // next() advances and returns next value
}

TEST(LinkedListTest, end) {
    LinkedList<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    
    auto iter = list.begin();
    auto end_iter = list.end();
    
    ASSERT_TRUE(iter != end_iter);
    
    // Iterate through all elements
    ++iter;  // Move to element 1
    ++iter;  // Move to element 2
    ++iter;  // Move past last element (to tail)
    
    ASSERT_FALSE(iter != end_iter);  // Should now equal end
}

TEST(LinkedListIterator, operatorDereference) {
    LinkedList<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    
    auto iter = list.begin();
    ASSERT_EQ(*iter, 0);
    
    ++iter;
    ASSERT_EQ(*iter, 1);
    
    ++iter;
    ASSERT_EQ(*iter, 2);
}

TEST(LinkedListIterator, operatorIncrement) {
    LinkedList<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    
    auto iter = list.begin();
    ASSERT_EQ(*iter, 0);
    
    ++iter;
    ASSERT_EQ(*iter, 1);
    
    ++iter;
    ASSERT_EQ(*iter, 2);
    
    ++iter;
    ASSERT_FALSE(iter != list.end());
}

TEST(LinkedListIterator, rangeBasedFor) {
    LinkedList<int> list;
    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }
    
    int expected = 0;
    for (auto num : list) {
        ASSERT_EQ(num, expected);
        expected++;
    }
    ASSERT_EQ(expected, 5);  // Verify we iterated through all 5 elements
}

TEST(LinkedListIterator, traditionalForLoop) {
    LinkedList<int> list;
    for (int i = 0; i < 5; i++) {
        list.push_back(i * 2);  // 0, 2, 4, 6, 8
    }
    
    int count = 0;
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        ASSERT_EQ(*iter, count * 2);
        count++;
    }
    ASSERT_EQ(count, 5);
}

TEST(LinkedListIterator, emptyListIteration) {
    LinkedList<int> list;
    
    auto iter = list.begin();
    auto end_iter = list.end();
    
    ASSERT_FALSE(iter != end_iter);  // begin equals end for empty list
    
    int count = 0;
    for (auto num : list) {
        (void)num;  // Suppress unused variable warning
        count++;
    }
    ASSERT_EQ(count, 0);  // Should not iterate at all
}

TEST(LinkedList, reverse) {
    LinkedList<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    list.reverse();
    ASSERT_EQ(list[0], 2);
    ASSERT_EQ(list[1], 1);
    ASSERT_EQ(list[2], 0);
}