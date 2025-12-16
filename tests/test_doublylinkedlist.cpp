#include <gtest/gtest.h>
#include "DoublyLinkedList.h"

TEST(DoublyLinkedListTest, EmptyList) {
    DoublyLinkedList<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}
TEST(DoublyLinkedListTest, CopyConstructor) {
    DoublyLinkedList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    DoublyLinkedList<int> list2(list1);

    EXPECT_EQ(list1.size(), list2.size());

    auto it1 = list1.begin();
    auto it2 = list2.begin();

    while (it1 != list1.end() && it2 != list2.end()) {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

    list1.push_back(4);
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list2.size(), 3);
}

TEST(DoublyLinkedListTest, PushBack) {
    DoublyLinkedList<int> list;

    list.push_back(1);
    EXPECT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(*list.begin(), 1);

    list.push_back(2);
    EXPECT_EQ(list.size(), 2);

    list.push_back(3);
    EXPECT_EQ(list.size(), 3);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(DoublyLinkedListTest, PushFront) {
    DoublyLinkedList<int> list;

    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    EXPECT_EQ(list.size(), 3);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(DoublyLinkedListTest, PopFront) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.size(), 3);

    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(*list.begin(), 2);

    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(*list.begin(), 3);

    list.pop_front();
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);

    EXPECT_THROW(list.pop_front(), std::logic_error);
}

TEST(DoublyLinkedListTest, PopBack) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.size(), 3);

    list.pop_back();
    EXPECT_EQ(list.size(), 2);

    auto it = list.begin();
    ++it;
    EXPECT_EQ(*it, 2);

    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(*list.begin(), 1);

    list.pop_back();
    EXPECT_TRUE(list.is_empty());

    EXPECT_THROW(list.pop_back(), std::logic_error);
}

TEST(DoublyLinkedListTest, PopByValue) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    list.pop_by_val(2);
    EXPECT_EQ(list.size(), 3);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 4);

    list.pop_by_val(1);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(*list.begin(), 3);

    list.pop_by_val(4);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(*list.begin(), 3);

    EXPECT_THROW(list.pop_by_val(99), std::logic_error);
}

TEST(DoublyLinkedListTest, Insert) {
    DoublyLinkedList<int> list;

    list.insert(0, 100);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(*list.begin(), 100);

    list.insert(0, 50);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(*list.begin(), 50);

    list.insert(2, 200);
    EXPECT_EQ(list.size(), 3);

    list.insert(1, 75);
    EXPECT_EQ(list.size(), 4);

    int expected[] = { 50, 75, 100, 200 };
    int i = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected[i]);
        i++;
    }
}

TEST(DoublyLinkedListTest, Erase) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    list.erase(1);
    EXPECT_EQ(list.size(), 3);

    // 1, 3, 4
    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 4);


    list.erase(0);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(*list.begin(), 3);

    list.erase(1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(*list.begin(), 3);

    EXPECT_THROW(list.erase(5), std::out_of_range);
}

TEST(DoublyLinkedListTest, Clear) {
    DoublyLinkedList<int> list;
    list.clear();
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);

    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }

    EXPECT_EQ(list.size(), 5);
    list.clear();

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}

TEST(DoublyLinkedListTest, Iterators) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 60); // 10 + 20 + 30 = 60

    auto it = list.begin();
    EXPECT_EQ(*it, 10);

    ++it;
    EXPECT_EQ(*it, 20);

    ++it;
    EXPECT_EQ(*it, 30);

    ++it;
    EXPECT_EQ(it, list.end());

    it = list.begin();
    *it = 100;
    EXPECT_EQ(list.front(), 100);

    EXPECT_EQ(*list.rbegin(), 30);
}

TEST(DoublyLinkedListTest, FindNode) {
    DoublyLinkedList<int> list;
    EXPECT_THROW(list.find_node_by_val(1), std::logic_error);

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    auto* node = list.find_node_by_val(20);
    EXPECT_NE(node, nullptr);

    EXPECT_EQ(list.find_node_by_val(99), nullptr);
}
