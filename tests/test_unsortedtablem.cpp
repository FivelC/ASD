#include <gtest/gtest.h>
#include "../lib_unsortedtable/unsortedtable.h"
#include "../lib_polynom/polynom.h"
TEST(UnsortedTableTest, InsertFindSize) {
	UnsortedTable<std::string, Polynom> table;
	Polynom p1("2x^2 + 3z");
	Polynom p2("3x^3");

	table.insert("P1", p1);
	table.insert("P2", p2);

	auto* val = table.find("P1");
	ASSERT_NE(val, nullptr);
	std::stringstream ss;
	ss << *val;
	EXPECT_EQ(ss.str(), "2x^2 + 3z^1");
	EXPECT_EQ(table.find("P4"), nullptr);
	EXPECT_THROW(table.insert("P1", p1), std::logic_error);
	EXPECT_EQ(table.size(), 2);
}

TEST(UnsortedTableTest, ChangeVal) {
	UnsortedTable<std::string, Polynom> table;

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

TEST(UnsortedTableTest, ChangeKey) {
	UnsortedTable<std::string, Polynom> table;

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

TEST(UnsortedTableTest, Remove) {
	UnsortedTable<std::string, Polynom> table;

	Polynom p1("2x^2 + 3z");
	Polynom p2("3x^3");

	table.insert("P1", p1);
	table.insert("P2", p2);

	table.remove("P1");
	EXPECT_EQ(table.find("P1"), nullptr);

	EXPECT_NE(table.find("P2"), nullptr);
}

TEST(UnsortedTableTest, IsEmpty) {
	UnsortedTable<std::string, Polynom> table;
	Polynom p1("2x^2 + 3z");
	Polynom p2("3x^3");

	EXPECT_TRUE(table.isEmpty());

	table.insert("P1", p1);
	EXPECT_FALSE(table.isEmpty());

	table.remove("P1");
	EXPECT_TRUE(table.isEmpty());
}