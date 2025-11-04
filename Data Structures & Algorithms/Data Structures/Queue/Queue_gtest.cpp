#include "gtest/gtest.h"
#include "Queue.h"

TEST(Queue_Test, Default_Constructor) {
    Queue<int> q;
    ASSERT_EQ(q.size(), 0);
    ASSERT_TRUE(q.empty());
}

TEST(Queue_Test, Copy_Constructor) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    Queue<int> q2 = q;
    ASSERT_FALSE(q2.empty());
    ASSERT_EQ(q2.size(), 3);
    ASSERT_EQ(q2.front(), 1);
    ASSERT_EQ(q2.back(), 3);
}

TEST(Queue_Test, Move_Constructor) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    Queue<int> q2 = std::move(q);
    ASSERT_FALSE(q2.empty());
    ASSERT_EQ(q2.size(), 3);
    ASSERT_EQ(q2.front(), 1);
    ASSERT_EQ(q2.back(), 3);

    ASSERT_TRUE(q.empty());
    ASSERT_EQ(q.size(), 0);
}

TEST(Queue_Test, Copy_Assignment_Operator) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    Queue<int> q2;
    q2.push(10);
    q2.push(20);
    q2.push(30);
    q2 = q;
    ASSERT_FALSE(q2.empty());
    ASSERT_EQ(q2.size(), 3);
    ASSERT_EQ(q2.front(), 1);
    ASSERT_EQ(q2.back(), 3);
}

TEST(Queue_Test, Move_Assignment_Operator) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    Queue<int> q2;
    q2.push(10);
    q2.push(20);
    q2.push(30);
    q2 = std::move(q);
    ASSERT_FALSE(q2.empty());
    ASSERT_EQ(q2.size(), 3);
    ASSERT_EQ(q2.front(), 1);
    ASSERT_EQ(q2.back(), 3);
    ASSERT_TRUE(q.empty());
    ASSERT_EQ(q.size(), 0);
}

TEST(Queue_Test, front) {
    Queue<int> q;
    ASSERT_THROW(q.front(), std::out_of_range);
    q.push(1);
    ASSERT_EQ(q.front(), 1);
    q.push(2);
    ASSERT_EQ(q.front(), 1);
    q.push(3);
    ASSERT_EQ(q.front(), 1);
}

TEST(Queue_Test, front_const) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    const Queue<int> const_q = q;
    ASSERT_EQ(const_q.front(), 1);
}

TEST(Queue_Test, back) {
    Queue<int> q;
    ASSERT_THROW(q.back(), std::out_of_range);
    q.push(1);
    ASSERT_EQ(q.back(), 1);
    q.push(2);
    ASSERT_EQ(q.back(), 2);
    q.push(3);
    ASSERT_EQ(q.back(), 3);
}

TEST(Queue_Test, back_const) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    const Queue<int> const_q = q;
    ASSERT_EQ(const_q.back(), 3);
}

TEST(Queue_Test, empty) {
    Queue<int> q;
    ASSERT_TRUE(q.empty());
    q.push(1);
    ASSERT_FALSE(q.empty());
}

TEST(Queue_Test, size) {
    Queue<int> q;
    ASSERT_EQ(q.size(), 0);
    q.push(1);
    ASSERT_EQ(q.size(), 1);
}

TEST(Queue_Test, push) {
    Queue<int> q;
    q.push(0);
    ASSERT_EQ(q.back(), 0);

    q.push(1);
    ASSERT_EQ(q.back(), 1);

    q.push(2);
    ASSERT_EQ(q.back(), 2);
}

TEST(Queue_Test, Move_Push) {
    Queue<std::string> q;
    q.push("Hello");
    ASSERT_EQ(q.back(), "Hello");

    q.push("World");
    ASSERT_EQ(q.back(), "World");

    q.push("!");
    ASSERT_EQ(q.back(), "!");
}

TEST(Queue_Test, pop) {
    Queue<int> q;
    ASSERT_THROW(q.pop(), std::out_of_range);
    for (int i = 0; i < 10; i++) {
        q.push(i);
    }
    q.pop();
    ASSERT_EQ(q.front(), 1);
    q.pop();
    ASSERT_EQ(q.front(), 2);
    q.pop();
    ASSERT_EQ(q.front(), 3);
    q.pop();
    ASSERT_EQ(q.front(), 4);
    q.pop();
    ASSERT_EQ(q.front(), 5);
    q.pop();
    ASSERT_EQ(q.front(), 6);
    q.pop();
    ASSERT_EQ(q.front(), 7);
    q.pop();
    ASSERT_EQ(q.front(), 8);
    q.pop();
    ASSERT_EQ(q.front(), 9);
    q.pop();
    ASSERT_EQ(q.size(), 0);
    ASSERT_THROW(q.pop(), std::out_of_range);
}

TEST(Queue_Test, swap) {
    Queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);

    Queue<int> q2;
    q2.push(10);
    q2.push(20);
    q2.push(30);

    q1.swap(q2);
    ASSERT_EQ(q1.front(), 10);
    ASSERT_EQ(q1.back(), 30);

    ASSERT_EQ(q2.front(), 1);
    ASSERT_EQ(q2.back(), 3);
}

TEST(Queue_Test, equals) {
    Queue<int> q1;
    Queue<int> q2;
    ASSERT_TRUE(q1 == q2);  // Empty queues are equal
    
    q1.push(1);
    q1.push(2);
    q1.push(3);
    
    ASSERT_FALSE(q1 == q2);  // Different sizes
    
    q2.push(1);
    q2.push(2);
    q2.push(3);
    
    ASSERT_TRUE(q1 == q2);  // Same elements
    
    q2.pop();
    q2.push(4);
    
    ASSERT_FALSE(q1 == q2);  // Different elements
}

TEST(Queue_Test, not_equals) {
    Queue<int> q1;
    Queue<int> q2;
    ASSERT_FALSE(q1 != q2);  // Empty queues are equal
    
    q1.push(1);
    ASSERT_TRUE(q1 != q2);  // Different sizes
    
    q2.push(1);
    ASSERT_FALSE(q1 != q2);  // Same elements
    
    q2.push(2);
    ASSERT_TRUE(q1 != q2);  // Different elements
}

TEST(Queue_Test, less_than) {
    Queue<int> q1;
    Queue<int> q2;
    
    q1.push(1);
    q1.push(2);
    q1.push(3);
    
    q2.push(2);
    q2.push(3);
    q2.push(4);
    
    ASSERT_TRUE(q1 < q2);   // [1,2,3] < [2,3,4]
    ASSERT_FALSE(q2 < q1);  // [2,3,4] not < [1,2,3]
    
    Queue<int> q3;
    q3.push(1);
    q3.push(2);
    
    ASSERT_TRUE(q3 < q1);   // [1,2] < [1,2,3] (shorter)
    ASSERT_FALSE(q1 < q3);  // [1,2,3] not < [1,2]
    
    Queue<int> q4;
    q4.push(1);
    q4.push(2);
    q4.push(3);
    
    ASSERT_FALSE(q1 < q4);  // Equal queues, not less than
}

TEST(Queue_Test, less_than_or_equal) {
    Queue<int> q1;
    Queue<int> q2;
    
    q1.push(1);
    q1.push(2);
    
    q2.push(1);
    q2.push(2);
    
    ASSERT_TRUE(q1 <= q2);  // Equal queues
    
    q2.push(3);
    ASSERT_TRUE(q1 <= q2);  // q1 is shorter
    ASSERT_FALSE(q2 <= q1); // q2 is longer
}

TEST(Queue_Test, greater_than) {
    Queue<int> q1;
    Queue<int> q2;
    
    q1.push(2);
    q1.push(3);
    q1.push(4);
    
    q2.push(1);
    q2.push(2);
    q2.push(3);
    
    ASSERT_TRUE(q1 > q2);   // [2,3,4] > [1,2,3]
    ASSERT_FALSE(q2 > q1);  // [1,2,3] not > [2,3,4]
    
    Queue<int> q3;
    q3.push(2);
    q3.push(3);
    q3.push(4);
    
    ASSERT_FALSE(q1 > q3);  // Equal queues, not greater than
}

TEST(Queue_Test, greater_than_or_equal) {
    Queue<int> q1;
    Queue<int> q2;
    
    q1.push(1);
    q1.push(3);
    q1.push(5);
    
    q2.push(1);
    q2.push(2);
    
    ASSERT_TRUE(q1 >= q2);
    ASSERT_FALSE(q2 >= q1);
    
    Queue<int> q3;
    q3.push(1);
    q3.push(3);
    q3.push(5);
    
    ASSERT_TRUE(q1 >= q3);
    
    Queue<int> q4;
    q4.push(1);
    q4.push(3);
    
    ASSERT_TRUE(q1 >= q4);
}
