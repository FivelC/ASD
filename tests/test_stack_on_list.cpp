#include <gtest/gtest.h>
#include "..\lib_stack_on_list\StackOnList.h"

TEST(StackOnListTest, DefaultConstructor) {
    StackOnList<int> stack;

    EXPECT_TRUE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.sizeReal(), 0);
    EXPECT_EQ(stack.size(), STACK_DEFAULT_SIZE);
}

TEST(StackOnListTest, ConstructorWithSize) {
    StackOnList<int> stack(5);

    EXPECT_TRUE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.sizeReal(), 0);
    EXPECT_EQ(stack.size(), 5);
}

TEST(StackOnListTest, ConstructorWithSizeZero) {
    EXPECT_THROW(StackOnList<int> stack(0), std::logic_error);
}
TEST(StackOnListTest, ConstructorWithSizeAndValueZero) {
    EXPECT_THROW(StackOnList<int> stack(0, 42), std::logic_error);
}

TEST(StackOnListTest, ConstructorWithSizeAndValue) {
    StackOnList<int> stack(3, 42);

    EXPECT_FALSE(stack.isEmpty());
    EXPECT_TRUE(stack.isFull());
    EXPECT_EQ(stack.sizeReal(), 3);
    EXPECT_EQ(stack.size(), 3);

    EXPECT_EQ(stack.top(), 42);
    stack.pop();
    EXPECT_EQ(stack.top(), 42);
    stack.pop();
    EXPECT_EQ(stack.top(), 42);
}

TEST(StackOnListTest, CopyConstructor) {
    StackOnList<int> original(3, 100);
    StackOnList<int> copy(original);

    EXPECT_EQ(original.sizeReal(), copy.sizeReal());
    EXPECT_EQ(original.size(), copy.size());

    while (!original.isEmpty()) {
        EXPECT_EQ(original.top(), copy.top());
        original.pop();
        copy.pop();
    }
}

TEST(StackOnListTest, PushAndPop) {
    StackOnList<int> stack(3);

    int value1 = 10;
    int value2 = 20;
    int value3 = 30;

    stack.push(value1);
    EXPECT_EQ(stack.sizeReal(), 1);
    EXPECT_EQ(stack.top(), 10);

    stack.push(value2);
    EXPECT_EQ(stack.sizeReal(), 2);
    EXPECT_EQ(stack.top(), 20);

    stack.push(value3);
    EXPECT_EQ(stack.sizeReal(), 3);
    EXPECT_EQ(stack.top(), 30);
    EXPECT_TRUE(stack.isFull());

    stack.pop();
    EXPECT_EQ(stack.sizeReal(), 2);
    EXPECT_EQ(stack.top(), 20);

    stack.pop();
    EXPECT_EQ(stack.sizeReal(), 1);
    EXPECT_EQ(stack.top(), 10);

    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.sizeReal(), 0);
}

TEST(StackOnListTest, PushWhenFull) {
    StackOnList<int> stack(2);

    int val1 = 10;
    int val2 = 20;
    int val3 = 30;

    stack.push(val1);
    stack.push(val2);

    EXPECT_TRUE(stack.isFull());
    EXPECT_THROW(stack.push(val3), std::logic_error);
}


TEST(StackOnListTest, PopWhenEmpty) {
    StackOnList<int> stack(2);

    EXPECT_TRUE(stack.isEmpty());
    EXPECT_THROW(stack.pop(), std::logic_error);
}

TEST(StackOnListTest, TopWhenEmpty) {
    StackOnList<int> stack(2);

    EXPECT_TRUE(stack.isEmpty());
    EXPECT_THROW(stack.top(), std::logic_error);
}

TEST(StackOnListTest, Clear) {
    StackOnList<int> stack(3, 42);

    EXPECT_FALSE(stack.isEmpty());
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.sizeReal(), 0);
    EXPECT_EQ(stack.size(), 3);
}

TEST(StackOnListTest, Assign) {
    StackOnList<int> stack1(3, 100);
    StackOnList<int> stack2(2, 50);

    stack2.assign(stack1);

    EXPECT_EQ(stack2.sizeReal(), 3);
    EXPECT_EQ(stack2.size(), 3);

    while (!stack1.isEmpty()) {
        EXPECT_EQ(stack1.top(), stack2.top());
        stack1.pop();
        stack2.pop();
    }
}

TEST(StackOnListTest, SelfAssign) {
    StackOnList<int> stack(3, 42);
    StackOnList<int>& ref = stack;

    stack.assign(ref);

    EXPECT_EQ(stack.sizeReal(), 3);
    EXPECT_EQ(stack.top(), 42);
}

TEST(StackOnListTest, AssignmentOperator) {
    StackOnList<int> stack1(3, 100);
    StackOnList<int> stack2(1, 1);

    stack2 = stack1;

    EXPECT_EQ(stack2.sizeReal(), 3);
    EXPECT_EQ(stack2.size(), 3);

    while (!stack1.isEmpty()) {
        EXPECT_EQ(stack1.top(), stack2.top());
        stack1.pop();
        stack2.pop();
    }
}

TEST(StackOnListTest, SizeReal) {
    StackOnList<int> stack(5);

    EXPECT_EQ(stack.sizeReal(), 0);

    int val1 = 10;
    stack.push(val1);
    EXPECT_EQ(stack.sizeReal(), 1);

    int val2 = 20;
    stack.push(val2);
    EXPECT_EQ(stack.sizeReal(), 2);

    stack.pop();
    EXPECT_EQ(stack.sizeReal(), 1);

    stack.clear();
    EXPECT_EQ(stack.sizeReal(), 0);
}


TEST(StackOnListTest, ComplexOperations) {
    StackOnList<int> stack(5);

    for (int i = 1; i <= 5; i++) {
        int val = i * 10;
        stack.push(val);
    }

    EXPECT_TRUE(stack.isFull());
    EXPECT_EQ(stack.top(), 50);

    stack.pop();
    stack.pop();

    EXPECT_EQ(stack.top(), 30);
    EXPECT_EQ(stack.sizeReal(), 3);

    stack.clear();
    EXPECT_TRUE(stack.isEmpty());

    int newVal = 99;
    stack.push(newVal);
    EXPECT_EQ(stack.top(), 99);
}

TEST(StackOnListTest, CopyWithPartialFill) {
    StackOnList<int> original(5);

    int val1 = 10;
    int val2 = 20;
    original.push(val1);
    original.push(val2);

    StackOnList<int> copy(original);

    EXPECT_EQ(original.sizeReal(), copy.sizeReal());
    EXPECT_EQ(original.size(), copy.size());

    EXPECT_EQ(original.top(), copy.top());
    original.pop();
    copy.pop();
    EXPECT_EQ(original.top(), copy.top());
}