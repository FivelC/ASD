#include <gtest/gtest.h>
#include "../lib_unsortedtabletree/unsortedtabletree.h"
#include "../lib_polynom/polynom.h"
TEST(UnsortedTableTreeTest, InsertFindSize) {
	UnsortedTableTree<std::string, Polynom> table;
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

TEST(UnsortedTableTreeTest, ChangeVal) {
	UnsortedTableTree<std::string, Polynom> table;

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

TEST(UnsortedTableTreeTest, ChangeKey) {
	UnsortedTableTree<std::string, Polynom> table;

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

TEST(UnsortedTableTreeTest, Remove) {
	UnsortedTableTree<std::string, Polynom> table;

	Polynom p1("2x^2 + 3z");
	//Polynom p2("3x^3");

	table.insert("P1", p1);
	//table.insert("P2", p2);

	table.remove("P1");
	EXPECT_EQ(table.find("P1"), nullptr);

	//EXPECT_EQ(table.find("P2"), nullptr);
}

TEST(UnsortedTableTreeTest, IsEmpty) {
	UnsortedTableTree<std::string, Polynom> table;
	Polynom p1("2x^2 + 3z");
	Polynom p2("3x^3");

	EXPECT_TRUE(table.isEmpty());

	table.insert("P1", p1);
	EXPECT_FALSE(table.isEmpty());

	table.remove("P1");
	EXPECT_TRUE(table.isEmpty());
}

TEST(UnsortedTableTreeTest, Capacity) {
	UnsortedTableTree<std::string, Polynom> table;
	Polynom p("x + y + z");
	for (int i = 0; i < 10; ++i) {
		table.insert("P" + std::to_string(i), p);
	}

}