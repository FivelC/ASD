#include <gtest/gtest.h>
#include <iostream>
#include "../lib_list/list.h"

TEST(List, EmptyList) {
    List<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.begin(), list.end());
}

TEST(List, PushFront) {
    List<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    EXPECT_FALSE(list.is_empty());

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

TEST(List, PushBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

TEST(List, InsertAtPosition) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    list.insert(1, 2);

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

TEST(List, InsertAtFront) {
    List<int> list;
    list.push_back(2);
    list.push_back(3);

    list.insert(0, 1);

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

TEST(List, PopBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2 }));

    list.pop_back();
    values.clear();
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1 }));
}

TEST(List, PopBackSingleElement) {
    List<int> list;
    list.push_back(42);

    list.pop_back();

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.begin(), list.end());
}

TEST(List, CopyConstructor) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    List<int> copy(original);

    std::vector<int> original_values;
    for (int val : original) {
        original_values.push_back(val);
    }

    std::vector<int> copy_values;
    for (int val : copy) {
        copy_values.push_back(val);
    }

    EXPECT_EQ(original_values, copy_values);
    EXPECT_EQ(original_values, std::vector<int>({ 1, 2, 3 }));
}

TEST(List, CopyConstructorEmpty) {
    List<int> original;
    List<int> copy(original);

    EXPECT_TRUE(copy.is_empty());
    EXPECT_EQ(copy.begin(), copy.end());
}

TEST(List, Exceptions) {
    List<int> list;

    EXPECT_THROW(list.pop_back(), std::logic_error);

    EXPECT_THROW(list.insert(5, 42), std::logic_error);

    list.push_back(1);
    EXPECT_THROW(list.insert(5, 42), std::logic_error);
}

TEST(List, DifferentTypes) {
    List<std::string> string_list;
    string_list.push_back("hello");
    string_list.push_back("world");

    std::vector<std::string> values;
    for (const auto& val : string_list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<std::string>({ "hello", "world" }));
}

TEST(List, DoubleType) {
    List<double> double_list;
    double_list.push_back(1.1);
    double_list.push_back(2.2);
    double_list.push_back(3.3);

    auto it = double_list.begin();
    EXPECT_DOUBLE_EQ(*it, 1.1);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 2.2);
}

TEST(List, ModifyThroughIterator) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    for (auto it = list.begin(); it != list.end(); ++it) {
        *it = *it * 2;
    }

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 2, 4, 6 }));
}

TEST(List, SequenceOfOperations) {
    List<int> list;

    list.push_front(2);
    list.push_back(3);
    list.push_front(1);


    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));

    list.pop_back();

    values.clear();
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2 }));

    list.insert(1, 99);

    values.clear();
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 99, 2 }));
}



TEST(ListIterator, EmptyList) {
    List<int> list;

    EXPECT_EQ(list.begin(), list.end());

    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

TEST(ListIterator, ReadOperations) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);

    ++it;
    EXPECT_EQ(*it, 2);

    ++it;
    EXPECT_EQ(*it, 3);

    std::vector<int> values;
    for (int val : list) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

TEST(ListIterator, WriteOperations) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    auto it = list.begin();
    *it = 100;
    ++it;
    *it = 200;

    it = list.begin();
    EXPECT_EQ(*it, 100);
    ++it;
    EXPECT_EQ(*it, 200);
}