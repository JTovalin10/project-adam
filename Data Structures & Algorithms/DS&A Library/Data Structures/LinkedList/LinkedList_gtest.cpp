#include "gtest/gtest.h"
#include "LinkedList.h"

TEST(LinkedListTest, emptyConstructor) {
    LinkedList<int> list;
    ASSERT_EQ(list.empty(), true);
}

TEST(LinkedListTest, copyConstructor) {
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

TEST(LinkedListTest, assignmentOperator) {
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

TEST(LinkedListTest, operatorBracket) {
    LinkedList<int> list;

    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    ASSERT_EQ(list[0], 0);
    ASSERT_EQ(list[1], 1);
    ASSERT_EQ(list[2], 2);
}

TEST(LinkedListTest, operatorBracketsCont) {
    LinkedList<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }
    const LinkedList<int> list2 = list;
    ASSERT_EQ(list2[0], 0);
    ASSERT_EQ(list2[1], 1);
    ASSERT_EQ(list2[2], 2);

    // testing:
    // list2[0] = 100;
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