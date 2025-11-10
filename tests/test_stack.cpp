#include <gtest/gtest.h>
#include "../lib_stack/stack.h"


TEST(StackTest, DefaultConstructor) {
    Stack<int> s;
    EXPECT_EQ(s.is_empty(), true);
    EXPECT_EQ(s.is_full(), false);
}

TEST(StackTest, SizeConstructor) {
    Stack<int> s(10);
    EXPECT_EQ(s.is_empty(), true);
    EXPECT_EQ(s.is_full(), false);
    ASSERT_ANY_THROW(s.top());
}

TEST(StackTest, CopyConstructor) {
    Stack<int> s1(5);
    s1.push(10);
    s1.push(20);
    s1.push(30);

    Stack<int> s2(s1);
    EXPECT_EQ(s2.top(), 30);
    s1.pop();
    EXPECT_EQ(s2.top(), 30);
}

TEST(StackTest, InitListConstructor) {
    Stack<int> s({ 2, 7, 45, -88 });
    EXPECT_EQ(s.is_empty(), false);
    EXPECT_EQ(s.is_full(), true);
    EXPECT_EQ(s.top(), -88);
}

TEST(StackTest, Push) {
    Stack<int> s(3);
    s.push(5);
    EXPECT_EQ(s.top(), 5);
    s.push(10);
    EXPECT_EQ(s.top(), 10);
    s.push(15);
    EXPECT_EQ(s.is_full(), true);
    ASSERT_ANY_THROW(s.push(100));
}

TEST(StackTest, Pop) {
    Stack<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);

    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
    s.pop();
    EXPECT_EQ(s.is_empty(), true);
    ASSERT_ANY_THROW(s.pop());
}

TEST(StackTest, Clear) {
    Stack<int> s(5);
    s.push(10);
    s.push(20);
    s.clear();
    EXPECT_EQ(s.is_empty(), true);
    EXPECT_EQ(s.is_full(), false);
    ASSERT_ANY_THROW(s.top());
}

TEST(StackTest, Top) {
    Stack<int> s(5);
    s.push(1);
    s.push(2);
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
    s.pop();
    ASSERT_ANY_THROW(s.top());
}

TEST(StackTest, IsEmpty) {
    Stack<int> s(5);
    EXPECT_EQ(s.is_empty(), true);
    s.push(10);
    EXPECT_EQ(s.is_empty(), false);
    s.pop();
    EXPECT_EQ(s.is_empty(), true);
}

TEST(StackTest, IsFull) {
    Stack<int> s(2);
    EXPECT_EQ(s.is_full(), false);
    s.push(1);
    EXPECT_EQ(s.is_full(), false);
    s.push(2);
    EXPECT_EQ(s.is_full(), true);
    s.pop();
    EXPECT_EQ(s.is_full(), false);
}
