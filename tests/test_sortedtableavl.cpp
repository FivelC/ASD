#include <gtest/gtest.h>
#include "../lib_sortedtableavltree/sortedtableavl.h"
#include "../lib_polynom/polynom.h"

template<typename TKey>
static void checkSorted(const std::vector<TKey>& keys) {
    for (size_t i = 1; i < keys.size(); ++i)
        EXPECT_LT(keys[i - 1], keys[i]);
}
TEST(AVLTableTest, Insert102030) {
    AVLTable<int, std::string> table;

    table.insert(10, "ten");
    table.insert(20, "twenty");
    table.insert(30, "thirty");
    checkSorted(table.getKeys());
}
TEST(AVLTableTest, Insert51537) {
    AVLTable<int, std::string> table;

    table.insert(10, "ten");
    table.insert(20, "twenty");
    table.insert(30, "thirty");

    table.insert(5, "five");
    table.insert(15, "fifteen");
    table.insert(3, "three");
    table.insert(7, "seven");
    checkSorted(table.getKeys());
}
TEST(AVLTableTest, InsertFindSize) {
    AVLTable<int, std::string> table;

    table.insert(10, "ten");
    table.insert(20, "twenty");
    table.insert(30, "thirty"); 

    table.insert(5, "five");
    table.insert(15, "fifteen"); 
    table.insert(3, "three");
    table.insert(7, "seven"); 

    table.insert(25, "twenty-five");
    table.insert(31, "thirty-one");
    table.insert(24, "twenty-four");
    EXPECT_EQ(table.size(), 10);

    checkSorted(table.getKeys());
}
TEST(AVLTableTest, FindMissingKeyReturnsNull) {
    AVLTable<int, std::string> table;
    table.insert(10, "ten");
    EXPECT_EQ(table.find(99), nullptr);

    checkSorted(table.getKeys());
}

TEST(AVLTableTest, InsertDuplicateThrows) {
    AVLTable<int, std::string> table;
    table.insert(1, "one");
    EXPECT_THROW(table.insert(1, "another"), std::logic_error);

    EXPECT_EQ(table.size(), 1);
    checkSorted(table.getKeys());
}

TEST(AVLTableTest, Contains) {
    AVLTable<int, std::string> table;
    table.insert(7, "seven");
    EXPECT_TRUE(table.contains(7));
    EXPECT_FALSE(table.contains(3));

    checkSorted(table.getKeys());
}

TEST(AVLTableTest, IsEmpty) {
    AVLTable<std::string, Polynom> table;
    EXPECT_TRUE(table.isEmpty());

    table.insert("P1", Polynom("2x^2 + 3z"));
    EXPECT_FALSE(table.isEmpty());
    checkSorted(table.getKeys());

    table.remove("P1");
    EXPECT_TRUE(table.isEmpty());
    checkSorted(table.getKeys());
}

TEST(AVLTableTest, Remove) {
    AVLTable<int, std::string> table;
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(8, "eight");
    table.insert(2, "two");
    table.insert(4, "four");
    table.insert(7, "seven");
    table.insert(9, "nine");
    table.insert(1, "one");
    table.insert(6, "six");

    //           5
    //         /   \
    //        3     8
    //       / \   / \
    //      2   4 7   9
    //     /     /
    //    1     6

    EXPECT_EQ(table.size(), 9);
    checkSorted(table.getKeys());

    table.remove(1);
    EXPECT_EQ(table.find(1), nullptr);
    ASSERT_NE(table.find(2), nullptr);
    EXPECT_EQ(table.size(), 8);
    checkSorted(table.getKeys());
    //           5
    //         /   \
    //        3     8
    //       / \   / \
    //      2   4 7   9
    //           /
    //          6

    table.remove(7);
    EXPECT_EQ(table.find(7), nullptr);
    ASSERT_NE(table.find(6), nullptr);
    ASSERT_NE(table.find(8), nullptr);
    EXPECT_EQ(table.size(), 7);
    checkSorted(table.getKeys());
    //           5
    //         /   \
    //        3     8
    //       / \   / \
    //      2   4 6   9

    table.insert(10, "ten");
    table.remove(9);
    EXPECT_EQ(table.find(9), nullptr);
    ASSERT_NE(table.find(10), nullptr);
    ASSERT_NE(table.find(8), nullptr);
    EXPECT_EQ(table.size(), 7);
    checkSorted(table.getKeys());

    table.remove(3);
    EXPECT_EQ(table.find(3), nullptr);
    ASSERT_NE(table.find(2), nullptr);
    ASSERT_NE(table.find(4), nullptr);
    checkSorted(table.getKeys());
    //           5
    //         /   \
    //        4     8
    //       /     / \
    //      2     6   10
    table.remove(5);
    EXPECT_EQ(table.find(5), nullptr);
    ASSERT_NE(table.find(4), nullptr);
    ASSERT_NE(table.find(2), nullptr);
    ASSERT_NE(table.find(8), nullptr);
    //           6
    //         /   \
    //        4     8
    //       /       \
    //      2         10
    EXPECT_EQ(table.size(), 5);
    EXPECT_EQ(*table.find(2), "two");
    EXPECT_EQ(*table.find(4), "four");
    EXPECT_EQ(*table.find(6), "six");
    EXPECT_EQ(*table.find(8), "eight");
    EXPECT_EQ(*table.find(10), "ten");
    checkSorted(table.getKeys());
}

TEST(AVLTableTest, RemoveNonexistentDoesNotThrow) {
    AVLTable<int, std::string> table;
    table.insert(1, "one");
    EXPECT_NO_THROW(table.remove(99));
    EXPECT_EQ(table.size(), 1);
    checkSorted(table.getKeys());
}

TEST(AVLTableTest, RemoveOnlyElement) {
    AVLTable<int, std::string> table;
    table.insert(42, "answer");
    table.remove(42);
    EXPECT_TRUE(table.isEmpty());
    EXPECT_EQ(table.find(42), nullptr);
    checkSorted(table.getKeys());
}

TEST(AVLTableTest, InsertFindPolynom) {
    AVLTable<std::string, Polynom> table;
    table.insert("P1", Polynom("2x^2 + 3z"));
    table.insert("P2", Polynom("3x^3"));

    EXPECT_EQ(table.size(), 2);

    auto* v1 = table.find("P1");
    ASSERT_NE(v1, nullptr);
    std::stringstream ss1; ss1 << *v1;
    EXPECT_EQ(ss1.str(), "2x^2 + 3z^1");

    auto* v2 = table.find("P2");
    ASSERT_NE(v2, nullptr);
    std::stringstream ss2; ss2 << *v2;
    EXPECT_EQ(ss2.str(), "3x^3");

    checkSorted(table.getKeys());
}

TEST(AVLTableTest, BalanceOnAscendingInsert) {
    AVLTable<int, std::string> table;
    for (int i = 1; i <= 7; ++i)
        table.insert(i, std::to_string(i));

    EXPECT_EQ(table.size(), 7);
    for (int i = 1; i <= 7; ++i) {
        ASSERT_NE(table.find(i), nullptr);
        EXPECT_EQ(*table.find(i), std::to_string(i));
    }
    checkSorted(table.getKeys());
}

TEST(AVLTableTest, BalanceOnDescendingInsert) {
    AVLTable<int, std::string> table;
    for (int i = 7; i >= 1; --i)
        table.insert(i, std::to_string(i));

    EXPECT_EQ(table.size(), 7);
    for (int i = 1; i <= 7; ++i)
        ASSERT_NE(table.find(i), nullptr);
    checkSorted(table.getKeys());
}
