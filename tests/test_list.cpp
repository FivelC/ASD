#include <gtest/gtest.h>
#include <iostream>
#include "../lib_list/list.h"

TEST(SinglyLinkedListTest, DefaultConstructor) {
    List<int> list;

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}


TEST(SinglyLinkedListTest, CopyConstructor) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    List<int> list2(list1);

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


TEST(SinglyLinkedListTest, PushBack) {
    List<int> list;

    list.push_back(10);
    EXPECT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(*list.begin(), 10);

    list.push_back(20);
    EXPECT_EQ(list.size(), 2);

    auto it = list.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
}

TEST(SinglyLinkedListTest, PushFront) {
    List<int> list;

    list.push_front(30);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(*list.begin(), 30);

    list.push_front(20);
    EXPECT_EQ(list.size(), 2);
    auto it = list.begin();
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
}

TEST(SinglyLinkedListTest, PopFront) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

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

TEST(SinglyLinkedListTest, PopBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.back(), 2);

    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list.front(), 1);

    list.pop_back();
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);

    EXPECT_THROW(list.pop_back(), std::logic_error);
}

TEST(SinglyLinkedListTest, FrontAndBack) {
    List<int> list;

    EXPECT_THROW(list.front(), std::logic_error);
    EXPECT_THROW(list.back(), std::logic_error);

    list.push_back(10);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 10);

    list.push_front(20);
    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(list.back(), 10);
}


TEST(SinglyLinkedListTest, RemoveByValue) {
    List<int> list;
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
    EXPECT_EQ(list.front(), 3);

    list.pop_by_val(4);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 3);

    EXPECT_THROW(list.pop_by_val(99), std::logic_error);

    list.pop_by_val(3);
    EXPECT_TRUE(list.is_empty());
    EXPECT_THROW(list.pop_by_val(1), std::logic_error);
}

TEST(SinglyLinkedListTest, InsertAtPosition) {
    List<int> list;

    list.insert(0, 100);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 100);

    list.insert(0, 50);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 50);

    list.insert(2, 150);
    EXPECT_EQ(list.size(), 3);

    list.insert(1, 75);
    EXPECT_EQ(list.size(), 4);

    int expected[] = { 50, 75, 100, 150 };
    int i = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected[i++]);
    }

    EXPECT_THROW(list.insert(10, 999), std::out_of_range);
}

TEST(SinglyLinkedListTest, EraseAtPosition) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    list.erase(1);
    EXPECT_EQ(list.size(), 3);

    //1,3,4
    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 4);

    list.erase(0);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 3);

    list.erase(1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 3);

    EXPECT_THROW(list.erase(5), std::out_of_range);

    list.erase(0);
    EXPECT_TRUE(list.is_empty());
    EXPECT_THROW(list.erase(0), std::logic_error);
}

TEST(SinglyLinkedListTest, Clear) {
    List<int> list;

    list.clear();
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);

    for (int i = 0; i < 5; ++i) {
        list.push_back(i * 10);
    }

    EXPECT_EQ(list.size(), 5);
    list.clear();

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}

TEST(SinglyLinkedListTest, Iterators) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    int expected = 10;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected);
        expected += 10;
    }

    auto it = list.begin();
    auto it2 = it++;
    EXPECT_EQ(*it2, 10);
    EXPECT_EQ(*it, 20);

    ++it;
    EXPECT_EQ(*it, 30);

    it = list.begin();
    it += 2;
    EXPECT_EQ(*it, 30);


    auto it_start = list.begin();
    auto it_end = list.end();
    EXPECT_NE(it_start, it_end);

    EXPECT_THROW(*it_end, std::logic_error);

    it = list.begin();
    *it = 99;
    EXPECT_EQ(list.front(), 99);
}

TEST(SinglyLinkedListTest, FindNodeByValue) {
    List<int> list;

    EXPECT_EQ(list.find_node_by_val(1), nullptr);

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    auto* node2 = list.find_node_by_val(30);
    EXPECT_NE(node2, nullptr);

    auto* node3 = list.find_node_by_val(10);
    EXPECT_NE(node3, nullptr);

    auto* node4 = list.find_node_by_val(30);
    EXPECT_NE(node4, nullptr);
}

TEST(SinglyLinkedListTest, ComplexOperations) {
    List<int> list;

    list.push_back(100);
    list.push_front(50);
    list.push_back(150);
    list.insert(1, 75);
    list.insert(3, 125);

    // 50, 75, 100, 125, 150
    EXPECT_EQ(list.size(), 5);

    int expected_sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        expected_sum += *it;
    }
    EXPECT_EQ(expected_sum, 50 + 75 + 100 + 125 + 150);

    list.pop_by_val(100);
    list.erase(2);

    // 50, 75, 150
    EXPECT_EQ(list.size(), 3);

    auto it = list.begin();
    EXPECT_EQ(*it, 50);
    ++it;
    EXPECT_EQ(*it, 75);
    ++it;
    EXPECT_EQ(*it, 150);
}