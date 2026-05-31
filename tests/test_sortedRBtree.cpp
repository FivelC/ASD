#include <gtest/gtest.h>
#include <sstream>
#include "../lib_sortedtableRB/sortedtableRB.h"  
#include "../lib_polynom/polynom.h"

template<typename TKey>
static void checkSorted(const std::vector<TKey>& keys) {
    for (size_t i = 1; i < keys.size(); ++i)
        EXPECT_LT(keys[i - 1], keys[i]);
}

TEST(RBTableTest, Insert102030) {
    RBTable<int, std::string> table;

    table.insert(10, "ten");
    table.insert(20, "twenty");
    table.insert(30, "thirty");
    checkSorted(table.getKeys());
}

TEST(RBTableTest, Insert51537) {
    RBTable<int, std::string> table;

    table.insert(10, "ten");
    table.insert(20, "twenty");
    table.insert(30, "thirty");

    table.insert(5, "five");
    table.insert(15, "fifteen");
    table.insert(3, "three");
    table.insert(7, "seven");
    checkSorted(table.getKeys());
}

TEST(RBTableTest, InsertSize) {
    RBTable<int, std::string> table;

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

TEST(RBTableTest, InsertFind) {
    RBTable<int, std::string> table;
    table.insert(10, "ten");
    table.insert(20, "twenty");

    ASSERT_NE(table.find(10), nullptr);
    EXPECT_EQ(*table.find(10), "ten");
    EXPECT_EQ(*table.find(20), "twenty");
    checkSorted(table.getKeys());
}

TEST(RBTableTest, FindMissingKeyReturnsNull) {
    RBTable<int, std::string> table;
    table.insert(10, "ten");
    EXPECT_EQ(table.find(99), nullptr);

    checkSorted(table.getKeys());
}

TEST(RBTableTest, InsertDuplicateThrows) {
    RBTable<int, std::string> table;
    table.insert(1, "one");
    EXPECT_THROW(table.insert(1, "another"), std::logic_error);

    EXPECT_EQ(table.size(), 1);
    checkSorted(table.getKeys());
}

TEST(RBTableTest, IsEmpty) {
    RBTable<int, std::string> table;
    EXPECT_TRUE(table.isEmpty());

    table.insert(1, "one");
    EXPECT_FALSE(table.isEmpty());
    checkSorted(table.getKeys());
}

TEST(RBTableTest, InsertFindPolynom) {
    RBTable<std::string, Polynom> table;
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

TEST(RBTableTest, BalanceOnAscendingInsert) {
    RBTable<int, std::string> table;
    for (int i = 1; i <= 7; ++i)
        table.insert(i, std::to_string(i));

    EXPECT_EQ(table.size(), 7);
    for (int i = 1; i <= 7; ++i) {
        ASSERT_NE(table.find(i), nullptr);
        EXPECT_EQ(*table.find(i), std::to_string(i));
    }
    checkSorted(table.getKeys());
}

TEST(RBTableTest, BalanceOnDescendingInsert) {
    RBTable<int, std::string> table;
    for (int i = 7; i >= 1; --i)
        table.insert(i, std::to_string(i));

    EXPECT_EQ(table.size(), 7);
    for (int i = 1; i <= 7; ++i)
        ASSERT_NE(table.find(i), nullptr);
    checkSorted(table.getKeys());
}