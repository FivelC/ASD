#include <gtest/gtest.h>
#include "..\lib_queue\queue.h"

TEST(QueueTest, DefaultConstructor) {
    Queue<int> queue;

    EXPECT_TRUE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.sizeReal(), 0);
    EXPECT_EQ(queue.size(), QUEUE_DEFAULT_SIZE);
}

TEST(QueueTest, ConstructorWithSize) {
    Queue<int> queue(5);

    EXPECT_TRUE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.sizeReal(), 0);
    EXPECT_EQ(queue.size(), 5);
}

TEST(QueueTest, ConstructorWithSizeZero) {
    EXPECT_THROW(Queue<int> queue(0), std::invalid_argument);
}

TEST(QueueTest, ConstructorWithSizeAndValue) {
    Queue<int> queue(3, 42);

    EXPECT_FALSE(queue.isEmpty());
    EXPECT_TRUE(queue.isFull());
    EXPECT_EQ(queue.sizeReal(), 3);
    EXPECT_EQ(queue.size(), 3);

    EXPECT_EQ(queue.head(), 42);
    queue.pop();
    EXPECT_EQ(queue.head(), 42);
    queue.pop();
    EXPECT_EQ(queue.head(), 42);
}

TEST(QueueTest, CopyConstructor) {
    Queue<int> original(3);
    original.push(10);
    original.push(20);

    Queue<int> copy(original);

    EXPECT_EQ(original.sizeReal(), copy.sizeReal());
    EXPECT_EQ(original.size(), copy.size());

    EXPECT_EQ(original.head(), copy.head());
    original.pop();
    copy.pop();
    EXPECT_EQ(original.head(), copy.head());
}

TEST(QueueTest, PushAndPop) {
    Queue<int> queue(3);

    queue.push(10);
    EXPECT_EQ(queue.sizeReal(), 1);
    EXPECT_EQ(queue.head(), 10);
    EXPECT_EQ(queue.tail(), 10);

    queue.push(20);
    EXPECT_EQ(queue.sizeReal(), 2);
    EXPECT_EQ(queue.head(), 10);
    EXPECT_EQ(queue.tail(), 20);

    queue.push(30);
    EXPECT_EQ(queue.sizeReal(), 3);
    EXPECT_EQ(queue.head(), 10);
    EXPECT_EQ(queue.tail(), 30);
    EXPECT_TRUE(queue.isFull());

    queue.pop();
    EXPECT_EQ(queue.sizeReal(), 2);
    EXPECT_EQ(queue.head(), 20);
    EXPECT_EQ(queue.tail(), 30);

    queue.pop();
    EXPECT_EQ(queue.sizeReal(), 1);
    EXPECT_EQ(queue.head(), 30);
    EXPECT_EQ(queue.tail(), 30);

    queue.pop();
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_EQ(queue.sizeReal(), 0);
}

TEST(QueueTest, PushWhenFull) {
    Queue<int> queue(2);

    queue.push(10);
    queue.push(20);

    EXPECT_TRUE(queue.isFull());
    EXPECT_THROW(queue.push(30), std::logic_error);
}

TEST(QueueTest, PopWhenEmpty) {
    Queue<int> queue(2);

    EXPECT_TRUE(queue.isEmpty());
    EXPECT_THROW(queue.pop(), std::logic_error);
}

TEST(QueueTest, HeadWhenEmpty) {
    Queue<int> queue(2);

    EXPECT_TRUE(queue.isEmpty());
    EXPECT_THROW(queue.head(), std::logic_error);
}

TEST(QueueTest, TailWhenEmpty) {
    Queue<int> queue(2);

    EXPECT_TRUE(queue.isEmpty());
    EXPECT_THROW(queue.tail(), std::logic_error);
}

TEST(QueueTest, Clear) {
    Queue<int> queue(3);
    queue.push(10);
    queue.push(20);

    EXPECT_FALSE(queue.isEmpty());
    queue.clear();
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_EQ(queue.sizeReal(), 0);
    EXPECT_EQ(queue.size(), 3);
}

TEST(QueueTest, CircularBehavior) {
    Queue<int> queue(3);

    queue.push(1);
    queue.push(2);
    queue.push(3);

    queue.pop();
    queue.pop(); 

    // [_, _, 3], head=2, tail=0
    queue.push(4); 
    queue.push(5); 

    EXPECT_EQ(queue.sizeReal(), 3);
    EXPECT_EQ(queue.head(), 3);
    EXPECT_EQ(queue.tail(), 5);

    EXPECT_EQ(queue.head(), 3);
    queue.pop();
    EXPECT_EQ(queue.head(), 4);
    queue.pop();
    EXPECT_EQ(queue.head(), 5);
}

TEST(QueueTest, Assign) {
    Queue<int> queue1(3);
    queue1.push(100);
    queue1.push(200);

    Queue<int> queue2(1, 50);

    queue2.assign(queue1);

    EXPECT_EQ(queue2.sizeReal(), 2);
    EXPECT_EQ(queue2.size(), 3);
    EXPECT_EQ(queue2.head(), 100);
    EXPECT_EQ(queue2.tail(), 200);
}

TEST(QueueTest, SelfAssign) {
    Queue<int> queue(3, 42);
    Queue<int>& ref = queue;

    queue.assign(ref);

    EXPECT_EQ(queue.sizeReal(), 3);
    EXPECT_EQ(queue.head(), 42);
}

TEST(QueueTest, AssignmentOperator) {
    Queue<int> queue1(3);
    queue1.push(100);
    queue1.push(200);

    Queue<int> queue2(1, 1);

    queue2 = queue1;

    EXPECT_EQ(queue2.sizeReal(), 2);
    EXPECT_EQ(queue2.size(), 3);
    EXPECT_EQ(queue2.head(), 100);
    EXPECT_EQ(queue2.tail(), 200);
}

TEST(QueueTest, Reserve) {
    Queue<int> queue(2);
    queue.push(10);
    queue.push(20);

    EXPECT_EQ(queue.size(), 2);
    EXPECT_TRUE(queue.isFull());

    queue.reserve(5);
    EXPECT_EQ(queue.size(), 5);
    EXPECT_EQ(queue.sizeReal(), 2);
    EXPECT_EQ(queue.head(), 10);
    EXPECT_EQ(queue.tail(), 20);

    queue.push(30);
    EXPECT_EQ(queue.sizeReal(), 3);
    EXPECT_EQ(queue.tail(), 30);
}

TEST(QueueTest, ShrinkToFit) {
    Queue<int> queue(10);

    queue.push(10);
    queue.push(20);
    queue.push(30);

    EXPECT_EQ(queue.size(), 10);
    EXPECT_EQ(queue.sizeReal(), 3);

    queue.shrinkToFit();

    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.sizeReal(), 3);
    EXPECT_TRUE(queue.isFull());

    EXPECT_EQ(queue.head(), 10);
    queue.pop();
    EXPECT_EQ(queue.head(), 20);
    queue.pop();
    EXPECT_EQ(queue.head(), 30);
}

TEST(QueueTest, ShrinkToFitWhenEmpty) {
    Queue<int> queue(5);

    EXPECT_TRUE(queue.isEmpty());
    EXPECT_THROW(queue.shrinkToFit(), std::logic_error);
}

TEST(QueueTest, ShrinkToFitWhenFull) {
    Queue<int> queue(3, 42);

    size_t initialSize = queue.size();
    queue.shrinkToFit();
    EXPECT_EQ(queue.size(), initialSize);
}