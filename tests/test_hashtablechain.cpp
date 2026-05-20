#include <gtest/gtest.h>
#include "../lib_polynom/polynom.h"
#include "../lib_hashtablechain/hashtablechain.h"

TEST(HashChain, InsertAndFind) {
    HashChain<std::string, Polynom> table(17);
    table.insert({ "P1", Polynom("2x^2 + 3z") });
    ASSERT_NE(table.find("P1"), nullptr);
    std::stringstream ss;
    ss << *table.find("P1");
    EXPECT_EQ(ss.str(), "2x^2 + 3z^1");
}

TEST(HashChain, FindNotExisting) {
    HashChain<std::string, Polynom> table(17);
    EXPECT_EQ(table.find("P1"), nullptr);
}

TEST(HashChain, UpdateExisting) {
    HashChain<std::string, Polynom> table(17);
    table.insert({ "P1", Polynom("2x^2 + 3z") });
    table.insert({ "P1", Polynom("3x^3") });
    std::stringstream ss;
    ss << *table.find("P1");
    EXPECT_EQ(ss.str(), "3x^3");
    EXPECT_EQ(table.size(), 1);
}

///////////////////////////////////////////////////////

TEST(HashChain, RemoveExisting) {
    HashChain<std::string, Polynom> table(17);
    table.insert({ "P1", Polynom("2x^2 + 3z") });
    EXPECT_EQ(table.remove("P1"), 0);
    EXPECT_EQ(table.find("P1"), nullptr);
    EXPECT_EQ(table.size(), 0);
}

TEST(HashChain, RemoveNotExisting) {
    HashChain<std::string, Polynom> table(17);
    EXPECT_EQ(table.remove("P1"), -1);
}

TEST(HashChain, InsertAfterRemove) {
    HashChain<std::string, Polynom> table(17);
    table.insert({ "P1", Polynom("2x^2 + 3z") });
    table.remove("P1");
    table.insert({ "P1", Polynom("5x^5") });
    ASSERT_NE(table.find("P1"), nullptr);
    std::stringstream ss;
    ss << *table.find("P1");
    EXPECT_EQ(ss.str(), "5x^5");
    EXPECT_EQ(table.size(), 1);
}

///////////////////////////////////////////////////////

TEST(HashChain, TwoKeysCollision) {
    HashChain<int, Polynom> table(7);
    table.insert({ 0, Polynom("2x^2") });
    table.insert({ 7, Polynom("3x^3") });
    ASSERT_NE(table.find(0), nullptr);
    ASSERT_NE(table.find(7), nullptr);
    std::stringstream ss1, ss2;
    ss1 << *table.find(0);
    ss2 << *table.find(7);
    EXPECT_EQ(ss1.str(), "2x^2");
    EXPECT_EQ(ss2.str(), "3x^3");
}

TEST(HashChain, ThreeKeysCollision) {
    HashChain<int, Polynom> table(7);
    table.insert({ 0,  Polynom("x^1") });
    table.insert({ 7,  Polynom("2x^2") });
    table.insert({ 14, Polynom("3x^3") });
    ASSERT_NE(table.find(0), nullptr);
    ASSERT_NE(table.find(7), nullptr);
    ASSERT_NE(table.find(14), nullptr);
    EXPECT_EQ(table.size(), 3);
}

TEST(HashChain, CollisionThenDelete) {
    HashChain<int, Polynom> table(7);
    table.insert({ 0,  Polynom("x^1") });
    table.insert({ 7,  Polynom("2x^2") });
    table.insert({ 14, Polynom("3x^3") });
    table.remove(0);
    EXPECT_EQ(table.find(0), nullptr);
    ASSERT_NE(table.find(7), nullptr);
    ASSERT_NE(table.find(14), nullptr);
    std::stringstream ss;
    ss << *table.find(14);
    EXPECT_EQ(ss.str(), "3x^3");
}

TEST(HashChain, CollisionUpdateValue) {
    HashChain<int, Polynom> table(7);
    table.insert({ 0, Polynom("x^1") });
    table.insert({ 7, Polynom("2x^2") });
    table.insert({ 7, Polynom("9x^9") });
    std::stringstream ss;
    ss << *table.find(7);
    EXPECT_EQ(ss.str(), "9x^9");
    EXPECT_EQ(table.size(), 2);
}

TEST(HashChain, ManyCollisionsSameSlot) {
    HashChain<int, Polynom> table(17);
    std::vector<int> keys = { 0, 17, 34, 51, 68, 85 };
    for (int k : keys)
        table.insert({ k, Polynom("x^1") });
    for (int k : keys)
        ASSERT_NE(table.find(k), nullptr) << "не нашли ключ " << k;
    EXPECT_EQ(table.size(), keys.size());
}

TEST(HashChain, CollisionDeleteMiddle) {
    HashChain<int, Polynom> table(17);
    table.insert({ 0,  Polynom("x^1") });
    table.insert({ 17, Polynom("2x^2") });
    table.insert({ 34, Polynom("3x^3") });
    table.remove(17);
    ASSERT_NE(table.find(0), nullptr);
    EXPECT_EQ(table.find(17), nullptr);
    ASSERT_NE(table.find(34), nullptr);
    std::stringstream ss;
    ss << *table.find(34);
    EXPECT_EQ(ss.str(), "3x^3");
}

TEST(HashChain, CollisionDeleteAll) {
    HashChain<int, Polynom> table(17);
    table.insert({ 0,  Polynom("x^1") });
    table.insert({ 17, Polynom("2x^2") });
    table.insert({ 34, Polynom("3x^3") });
    table.remove(0);
    table.remove(17);
    table.remove(34);
    EXPECT_EQ(table.find(0), nullptr);
    EXPECT_EQ(table.find(17), nullptr);
    EXPECT_EQ(table.find(34), nullptr);
    EXPECT_EQ(table.size(), 0);
}

TEST(HashChain, CollisionAfterRehash) {
    HashChain<int, Polynom> table(7);
    std::vector<int> keys = { 0, 7, 14, 21, 28, 35 };
    for (int k : keys)
        table.insert({ k, Polynom("x^1") });
    for (int k : keys)
        ASSERT_NE(table.find(k), nullptr) << "не нашли ключ " << k << " после rehash";
}

///////////////////////////////////////////////////////

TEST(HashChain, RehashPreservesElements) {
    HashChain<std::string, Polynom> table(7);
    std::vector<std::string> keys = { "P1","P2","P3","P4","P5","P6","P7","P8" };
    for (auto& k : keys)
        table.insert({ k, Polynom("x^1") });
    for (auto& k : keys)
        ASSERT_NE(table.find(k), nullptr) << "не нашли " << k << " после rehash";
}

TEST(HashChain, RehashIncreasesCapacity) {
    HashChain<std::string, Polynom> table(7);
    size_t oldCapacity = table.capacity();
    std::vector<std::string> keys = { "P1","P2","P3","P4","P5","P6","P7","P8" };
    for (auto& k : keys)
        table.insert({ k, Polynom("x^1") });
    EXPECT_GT(table.capacity(), oldCapacity);
}
