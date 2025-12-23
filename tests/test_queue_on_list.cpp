#include <gtest/gtest.h>
#include "..\lib_queue_on_list\QueueOnList.h"

TEST(QueueOnListTest, DefaultConstructor) {
    QueueOnList<int> queue;

    EXPECT_TRUE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.sizeReal(), 0);
    EXPECT_EQ(queue.size(), QUEUE_DEFAULT_SIZE);
}

TEST(QueueOnListTest, ConstructorWithSize) {
    QueueOnList<int> queue(5);

    EXPECT_TRUE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.sizeReal(), 0);
    EXPECT_EQ(queue.size(), 5);
}

TEST(QueueOnListTest, ConstructorWithSizeZero) {
    EXPECT_THROW(QueueOnList<int> queue(0), std::invalid_argument);
}

TEST(QueueOnListTest, ConstructorWithSizeAndValue) {
    QueueOnList<int> queue(3, 42);

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

TEST(QueueOnListTest, CopyConstructor) {
    QueueOnList<int> original(3);
    original.push(10);
    original.push(20);

    QueueOnList<int> copy(original);

    EXPECT_EQ(original.sizeReal(), copy.sizeReal());
    EXPECT_EQ(original.size(), copy.size());

    EXPECT_EQ(original.head(), copy.head());
    original.pop();
    copy.pop();
    EXPECT_EQ(original.head(), copy.head());
}

TEST(QueueTestOnList, PushAndPop) {
    QueueOnList<int> queue(3);

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

TEST(QueueTestOnList, PushWhenFull) {
    QueueOnList<int> queue(2);

    queue.push(10);
    queue.push(20);

    EXPECT_TRUE(queue.isFull());
    EXPECT_THROW(queue.push(30), std::logic_error);
}

TEST(QueueOnListTest, PopWhenEmpty) {
    QueueOnList<int> queue(2);

    EXPECT_TRUE(queue.isEmpty());
    EXPECT_THROW(queue.pop(), std::logic_error);
}

TEST(QueueOnListTest, HeadWhenEmpty) {
    QueueOnList<int> queue(2);

    EXPECT_TRUE(queue.isEmpty());
    EXPECT_THROW(queue.head(), std::logic_error);
}

TEST(QueueOnListTest, TailWhenEmpty) {
    QueueOnList<int> queue(2);

    EXPECT_TRUE(queue.isEmpty());
    EXPECT_THROW(queue.tail(), std::logic_error);
}

TEST(QueueOnListTest, Clear) {
    QueueOnList<int> queue(3);
    queue.push(10);
    queue.push(20);

    EXPECT_FALSE(queue.isEmpty());
    queue.clear();
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_EQ(queue.sizeReal(), 0);
    EXPECT_EQ(queue.size(), 3);
}

TEST(QueueOnListTest, CircularBehavior) {
    QueueOnList<int> queue(3);

    queue.push(1);
    queue.push(2);
    queue.push(3);

    queue.pop();
    queue.pop();
    queue.shrinkToFit();
    // [_, _, 3], head=2, tail=0
    EXPECT_EQ(queue.head(), 3);
    EXPECT_EQ(queue.tail(), 3);
    queue.reserve(5);
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

TEST(QueueOnListTest, Assign) {
    QueueOnList<int> queue1(3);
    queue1.push(100);
    queue1.push(200);

    QueueOnList<int> queue2(1, 50);

    queue2.assign(queue1);

    EXPECT_EQ(queue2.sizeReal(), 2);
    EXPECT_EQ(queue2.size(), 3);
    EXPECT_EQ(queue2.head(), 100);
    EXPECT_EQ(queue2.tail(), 200);
}

TEST(QueueOnListTest, SelfAssign) {
    QueueOnList<int> queue(3, 42);
    QueueOnList<int>& ref = queue;

    queue.assign(ref);

    EXPECT_EQ(queue.sizeReal(), 3);
    EXPECT_EQ(queue.head(), 42);
}

TEST(QueueOnListTest, AssignmentOperator) {
    QueueOnList<int> queue1(3);
    queue1.push(100);
    queue1.push(200);

    QueueOnList<int> queue2(1, 1);

    queue2 = queue1;

    EXPECT_EQ(queue2.sizeReal(), 2);
    EXPECT_EQ(queue2.size(), 3);
    EXPECT_EQ(queue2.head(), 100);
    EXPECT_EQ(queue2.tail(), 200);
}

TEST(QueueOnListTest, Reserve) {
    QueueOnList<int> queue(2);
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

TEST(QueueOnListTest, ShrinkToFit) {
    QueueOnList<int> queue(10);

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

TEST(QueueOnListTest, ShrinkToFitWhenEmpty) {
    QueueOnList<int> queue(5);

    EXPECT_TRUE(queue.isEmpty());
    queue.shrinkToFit();
    EXPECT_EQ(queue.size(), 0);
}

TEST(QueueOnListTest, ShrinkToFitWhenFull) {
    QueueOnList<int> queue(3, 42);

    size_t initialSize = queue.size();
    queue.shrinkToFit();
    EXPECT_EQ(queue.size(), initialSize);
}