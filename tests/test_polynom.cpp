#include <gtest/gtest.h>
#include <iostream>
#include "../lib_polynom/polynom.h"

TEST(PolynomTest, DefaultConstructor_Empty) {
    Polynom p;
    EXPECT_TRUE(p.isEmpty());
}


TEST(PolynomTest, CopyConstructor) {
    Polynom p1;
    p1.insertSorted(Monom(3.0, 2, 1, 0));
    p1.insertSorted(Monom(5.0, 0, 0, 3));

    Polynom p2(p1);

    EXPECT_EQ(p2.size(), 2);
}

TEST(PolynomTest, String) {
    Polynom p1("123.1x^2 + 34x^3y^4z^5");
    std::ostringstream oss1;
    oss1 << p1;

    EXPECT_EQ(oss1.str(), "34x^3y^4z^5 + 123.1x^2");
}

TEST(PolynomTest, InsertSorted_BasicOrder) {
    Polynom p;
    p.insertSorted(Monom(4.0, 1, 0, 0));   
    p.insertSorted(Monom(2.0, 2, 0, 0));  
    p.insertSorted(Monom(7.0, 0, 3, 0));   

    auto it = p.begin();
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 2.0);
    EXPECT_EQ(it->getXPower(), 2);

    ++it;
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 4.0);
    EXPECT_EQ(it->getXPower(), 1);

    ++it;
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 7.0);
    EXPECT_EQ(it->getYPower(), 3);
}


TEST(PolynomTest, InsertSorted_ZeroCoefficientIgnored) {
    Polynom p;
    p.insertSorted(Monom(0.0, 5, 5, 5));
    p.insertSorted(Monom(1.0, 1, 0, 0));
    EXPECT_EQ(p.size(), 1);
}


TEST(PolynomTest, InsertSorted_MergeSameTerms) {
    Polynom p;
    p.insertSorted(Monom(3.0, 2, 1, 0));
    p.insertSorted(Monom(5.0, 2, 1, 0));
    p.insertSorted(Monom(-2.0, 2, 1, 0));

    EXPECT_EQ(p.size(), 1);
    auto it = p.begin();
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 6.0);
    EXPECT_EQ(it->getXPower(), 2);
    EXPECT_EQ(it->getYPower(), 1);
}


TEST(PolynomTest, OperatorPlus_Monom) {
    Polynom p;
    p.insertSorted(Monom(3.0, 1, 0, 0));

    Polynom res = p + Monom(4.0, 0, 2, 0);

    EXPECT_EQ(res.size(), 2);
    auto it = res.begin();
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 3.0); EXPECT_EQ(it->getXPower(), 1);
    ++it;
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 4.0); EXPECT_EQ(it->getYPower(), 2);
}


TEST(PolynomTest, OperatorMinus_Monom) {
    Polynom p;
    p.insertSorted(Monom(5.0, 2, 0, 0));

    Polynom res = p - Monom(2.0, 2, 0, 0);

    EXPECT_EQ(res.size(), 1);
    EXPECT_DOUBLE_EQ(res.begin()->getCoefficient(), 3.0);
}


TEST(PolynomTest, OperatorMultiply_Monom) {
    Polynom p;
    p.insertSorted(Monom(2.0, 1, 1, 0));   // 2xy
    p.insertSorted(Monom(3.0, 0, 0, 2));   // 3z²

    Polynom res = p * Monom(4.0, 1, 0, 1); // * 4xz

    EXPECT_EQ(res.size(), 2);

    // 2xy * 4xz = 8 x² y z
    // 3z²  * 4xz = 12 x z³

    auto it = res.begin();
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 8.0);
    EXPECT_EQ(it->getXPower(), 2); EXPECT_EQ(it->getYPower(), 1); EXPECT_EQ(it->getZPower(), 1);

    ++it;
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 12.0);
    EXPECT_EQ(it->getXPower(), 1); EXPECT_EQ(it->getYPower(), 0); EXPECT_EQ(it->getZPower(), 3);
}


TEST(PolynomTest, OperatorPlus_Polynom) {
    Polynom p1, p2;
    p1.insertSorted(Monom(1.0, 2, 0, 0));
    p1.insertSorted(Monom(4.0, 0, 1, 0));

    p2.insertSorted(Monom(5.0, 1, 0, 0));
    p2.insertSorted(Monom(-4.0, 0, 1, 0));

    Polynom res = p1 + p2;

    //  x² + 4y  +  5x - 4y  →  x² + 5x
    EXPECT_EQ(res.size(), 2);
    auto it = res.begin();
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 1.0); EXPECT_EQ(it->getXPower(), 2);
    ++it;
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 5.0); EXPECT_EQ(it->getXPower(), 1);
}


TEST(PolynomTest, OperatorMinus_Polynom) {
    Polynom p1, p2;
    p1.insertSorted(Monom(7.0, 1, 1, 0));
    p2.insertSorted(Monom(3.0, 1, 1, 0));

    Polynom res = p1 - p2;
    EXPECT_EQ(res.size(), 1);
    EXPECT_DOUBLE_EQ(res.begin()->getCoefficient(), 4.0);
}


TEST(PolynomTest, OperatorMultiply_Polynom_Simple) { //сложнее сделать 
    Polynom p1, p2;
    // Полином p1: 2x + 3y + 1
    p1.insertSorted(Monom(2.0, 1, 0, 0));  // 2x
    p1.insertSorted(Monom(3.0, 0, 1, 0));  // 3y
    p1.insertSorted(Monom(1.0, 0, 0, 0));  // 1

    // Полином p2: x - y + 2
    p2.insertSorted(Monom(1.0, 1, 0, 0));   // x
    p2.insertSorted(Monom(-1.0, 0, 1, 0));  // -y
    p2.insertSorted(Monom(2.0, 0, 0, 0));   // 2


    Polynom res = p1 * p2;                  // 2x^2 + xy - 3y^2 + 5x + 5y + 2

    EXPECT_EQ(res.size(), 6);
    auto it = res.begin();

    EXPECT_DOUBLE_EQ(it->getCoefficient(), 2.0); // 2x^2
    EXPECT_EQ(it->getXPower(), 2);
    EXPECT_EQ(it->getYPower(), 0);
    ++it;

    EXPECT_DOUBLE_EQ(it->getCoefficient(), 1.0); // xy
    EXPECT_EQ(it->getXPower(), 1);
    EXPECT_EQ(it->getYPower(), 1);
    ++it;

    EXPECT_DOUBLE_EQ(it->getCoefficient(), 5.0); // 5x
    EXPECT_EQ(it->getXPower(), 1);
    EXPECT_EQ(it->getYPower(), 0);
    ++it;

    EXPECT_DOUBLE_EQ(it->getCoefficient(), -3.0); // -3y^2
    EXPECT_EQ(it->getXPower(), 0);
    EXPECT_EQ(it->getYPower(), 2);
    ++it;

    EXPECT_DOUBLE_EQ(it->getCoefficient(), 5.0); // 5y
    EXPECT_EQ(it->getXPower(), 0);
    EXPECT_EQ(it->getYPower(), 1);
    ++it;

    EXPECT_DOUBLE_EQ(it->getCoefficient(), 2.0); // 2
    EXPECT_EQ(it->getXPower(), 0);
    EXPECT_EQ(it->getYPower(), 0);
}
TEST(PolynomTest, Output) {
    Polynom p1;
    p1.insertSorted(Monom(2.0, 3, 2, 1));
    p1.insertSorted(Monom(-4.0, 5, 0, 0));
    std::ostringstream oss1;
    oss1 << p1;
    EXPECT_EQ(oss1.str(), "-4x^5 + 2x^3y^2z^1");
}
TEST(MonomTest, Input) {
    std::istringstream iss("3.5 2 1 0");

    Monom m;
    iss >> m;

    EXPECT_DOUBLE_EQ(m.getCoefficient(), 3.5);
    EXPECT_EQ(m.getXPower(), 2);
    EXPECT_EQ(m.getYPower(), 1);
    EXPECT_EQ(m.getZPower(), 0);
}