#include <gtest/gtest.h>
#include "../lib_sortedtable/sortedtable.h"
#include "../lib_polynom/polynom.h"
TEST(SortedTableTest, InsertFindSize) {
	SortedTable<int, std::string> table;
	Polynom p1("2x^2 + 3z");
	Polynom p2("3x^3");

	table.insert(5, "five");
	table.insert(1, "one");
	table.insert(4, "four");
	table.insert(3, "three");
	table.insert(2, "two");
	
	TVector<int> keys;
	for (size_t i = 0; i < table.size(); ++i) {
		keys.push_back(table.getKeyAt(i));
	}
	for (size_t i = 1; i < keys.size(); ++i) {
		EXPECT_LT(keys[i - 1], keys[i]); 
	}
	EXPECT_EQ(*table.find(1), "one");
	EXPECT_EQ(*table.find(2), "two");
	EXPECT_EQ(*table.find(3), "three");
	EXPECT_EQ(*table.find(4), "four");
	EXPECT_EQ(*table.find(5), "five");
}

TEST(SortedTableTest, ChangeVal) {
	SortedTable<std::string, Polynom> table;

	Polynom p1("2x^2 + 3z");
	Polynom p2("3x^3");

	table.insert("P1", p1);
	table.changeVal("P1", p2);

	auto* val = table.find("P1");
	std::stringstream ss;
	ss << *val;
	EXPECT_NE(val, nullptr);
	EXPECT_EQ(ss.str(), "3x^3");
}

TEST(SortedTableTest, ChangeKey) {
	SortedTable<std::string, Polynom> table;

	Polynom p1("2x^2 + 3z");
	Polynom p2("3x^3");

	table.insert("P1", p1);
	table.changeKey("P1", "P3");

	auto* val = table.find("P3");
	std::stringstream ss;
	ss << *val;
	EXPECT_NE(val, nullptr);
	EXPECT_EQ(ss.str(), "2x^2 + 3z^1");
}

TEST(SortedTableTest, Remove) {
	SortedTable<std::string, Polynom> table;

	Polynom p1("2x^2 + 3z");
	Polynom p2("3x^3");

	table.insert("P1", p1);
	table.insert("P2", p2);

	table.remove("P1");
	EXPECT_EQ(table.find("P1"), nullptr);

	EXPECT_NE(table.find("P2"), nullptr);
}

TEST(SortedTableTest, IsEmpty) {
	SortedTable<std::string, Polynom> table;
	Polynom p1("2x^2 + 3z");
	Polynom p2("3x^3");

	EXPECT_TRUE(table.isEmpty());

	table.insert("P1", p1);
	EXPECT_FALSE(table.isEmpty());

	table.remove("P1");
	EXPECT_TRUE(table.isEmpty());
}