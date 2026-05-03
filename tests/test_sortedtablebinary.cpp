#include <gtest/gtest.h>
#include "../lib_sortedtablebinarytree/sortedtablebinarytree.h"
#include "../lib_polynom/polynom.h"

TEST(SortedTreeTableTest, InsertFindSize) {
    SortedTreeTable<int, std::string> table;
    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(4, "four");
    table.insert(3, "three");
    table.insert(2, "two");

    std::vector<int> keys = table.getKeys();
    for (size_t i = 1; i < keys.size(); ++i) {
        EXPECT_LT(keys[i - 1], keys[i]);
    }

}

TEST(SortedTreeTableTest, ChangeVal) {
    SortedTreeTable<std::string, Polynom> table;
    Polynom p1("2x^2 + 3z");
    Polynom p2("3x^3");
    table.insert("P1", p1);
    table.changeVal("P1", p2);
    auto* val = table.find("P1");
    ASSERT_NE(val, nullptr);
    std::stringstream ss;
    ss << *val;
    EXPECT_EQ(ss.str(), "3x^3");


}

TEST(SortedTreeTableTest, ChangeKey) {
    SortedTreeTable<std::string, Polynom> table;
    Polynom p1("2x^2 + 3z");
    table.insert("P1", p1);
    table.changeKey("P1", "P3");
    auto* val = table.find("P3");
    ASSERT_NE(val, nullptr);
    std::stringstream ss;
    ss << *val;
    EXPECT_EQ(ss.str(), "2x^2 + 3z^1");


    std::vector<std::string> keys = table.getKeys();
    for (size_t i = 1; i < keys.size(); ++i) {
        EXPECT_LT(keys[i - 1], keys[i]);
    }
}

TEST(SortedTreeTableTest, Remove) {
    SortedTreeTable<int, std::string> table;

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

    // ── Случай 1: удаление листа (нет потомков) ──────────────────────────
    table.remove(1);
    EXPECT_EQ(table.find(1), nullptr);
    ASSERT_NE(table.find(2), nullptr);
    EXPECT_EQ(table.size(), 8);
    std::vector<int> keys1 = table.getKeys();
    for (size_t i = 1; i < keys1.size(); ++i) {
        EXPECT_LT(keys1[i - 1], keys1[i]);
    }
    //           5
    //         /   \
    //        3     8
    //       / \   / \
    //      2   4 7   9
    //           /
    //          6

    // ── Случай 2: удаление узла с только левым потомком ──────────────────
    table.remove(7);
    EXPECT_EQ(table.find(7), nullptr);
    ASSERT_NE(table.find(6), nullptr); 
    ASSERT_NE(table.find(8), nullptr); 
    EXPECT_EQ(table.size(), 7);
    std::vector<int> keys2 = table.getKeys();
    for (size_t i = 1; i < keys2.size(); ++i) {
        EXPECT_LT(keys2[i - 1], keys2[i]);
    }
    //           5
    //         /   \
    //        3     8
    //       / \   / \
    //      2   4 6   9

    // ── Случай 3: удаление узла с только правым потомком ─────────────────
    table.insert(10, "ten");
    table.remove(9);
    EXPECT_EQ(table.find(9), nullptr);
    ASSERT_NE(table.find(10), nullptr);
    ASSERT_NE(table.find(8), nullptr); 
    EXPECT_EQ(table.size(), 7);

    //           5
    //         /   \
    //        3     8
    //       / \   / \
    //      2   4 6   10

    // ── Случай 4: удаление узла с двумя потомками ────────────────────────
    table.remove(3);
    EXPECT_EQ(table.find(3), nullptr);
    ASSERT_NE(table.find(2), nullptr);
    ASSERT_NE(table.find(4), nullptr);
    ASSERT_NE(table.find(5), nullptr);

    //           5
    //         /   \
    //        2     8
    //         \   / \
    //          4 6   10
    table.remove(5);
    EXPECT_EQ(table.find(5), nullptr);
    ASSERT_NE(table.find(4), nullptr);
    ASSERT_NE(table.find(2), nullptr);
    ASSERT_NE(table.find(8), nullptr);

    //           4
    //         /   \
    //        2     8
    //             / \
    //            6   10

    EXPECT_EQ(table.size(), 5);

    EXPECT_EQ(*table.find(2), "two");
    EXPECT_EQ(*table.find(4), "four");
    EXPECT_EQ(*table.find(6), "six");
    EXPECT_EQ(*table.find(8), "eight");
    EXPECT_EQ(*table.find(10), "ten");
    std::vector<int> keys = table.getKeys();
    for (size_t i = 1; i < keys.size(); ++i) {
        EXPECT_LT(keys[i - 1], keys[i]);
    }
}

TEST(SortedTreeTableTest, IsEmpty) {
    SortedTreeTable<std::string, Polynom> table;
    Polynom p1("2x^2 + 3z");
    EXPECT_TRUE(table.isEmpty());
    table.insert("P1", p1);
    EXPECT_FALSE(table.isEmpty());
    table.remove("P1");
    EXPECT_TRUE(table.isEmpty());
}