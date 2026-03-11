#include <gtest/gtest.h>
#include <iostream>
#include "../lib_monom/monom.h"

TEST(MonomTest, DefaultConstraction) {
    Monom a;
    EXPECT_EQ(a.getCoefficient(), 0.0);
    EXPECT_EQ(a.getXPower(), 0);
    EXPECT_EQ(a.getYPower(), 0);
    EXPECT_EQ(a.getZPower(), 0);
}
TEST(MonomTest, ThreeInit) {
    Monom a(123.1, 1, 2, 3);
    EXPECT_EQ(a.getCoefficient(), 123.1);
    EXPECT_EQ(a.getXPower(), 1);
    EXPECT_EQ(a.getYPower(), 2);
    EXPECT_EQ(a.getZPower(), 3);
}
TEST(MonomTest, TwoInit) {
    Monom a(123.1, 1, 2, 'x', 'y');
    EXPECT_EQ(a.getCoefficient(), 123.1);
    EXPECT_EQ(a.getXPower(), 1);
    EXPECT_EQ(a.getYPower(), 2);
    EXPECT_EQ(a.getZPower(), 0);

    Monom b(123.1, 1, 2, 'z', 'y');
    EXPECT_EQ(b.getCoefficient(), 123.1);
    EXPECT_EQ(b.getXPower(), 0);
    EXPECT_EQ(b.getYPower(), 2);
    EXPECT_EQ(b.getZPower(), 1);

    EXPECT_THROW(Monom c(123.1, 1, 2, 'z', 'z'), std::invalid_argument);
    EXPECT_THROW(Monom c(123.1, 1, 2, 'u', 'z'), std::invalid_argument);
}
TEST(MonomTest, OneInit) {
    Monom a(123, 1, 'y');
    EXPECT_EQ(a.getCoefficient(), 123.0);
    EXPECT_EQ(a.getXPower(), 0);
    EXPECT_EQ(a.getYPower(), 1);
    EXPECT_EQ(a.getZPower(), 0);

    Monom b(123.1, 2, 'z');
    EXPECT_EQ(b.getCoefficient(), 123.1);
    EXPECT_EQ(b.getXPower(), 0);
    EXPECT_EQ(b.getYPower(), 0);
    EXPECT_EQ(b.getZPower(), 2);

    EXPECT_THROW(Monom c(123.1, 1, 'u'), std::invalid_argument);
}

TEST(MonomTest, Copy) {
    Monom a(123.1, 1, 'y');
    Monom b(a);
    EXPECT_EQ(b.getCoefficient(), a.getCoefficient());
    EXPECT_EQ(b.getXPower(), a.getXPower());
    EXPECT_EQ(b.getYPower(), a.getYPower());
    EXPECT_EQ(b.getZPower(), a.getZPower());
}

TEST(MonomTest, CoefficientOnlyConstructor) {
    Monom a(7.5);
    EXPECT_DOUBLE_EQ(a.getCoefficient(), 7.5);
    EXPECT_EQ(a.getXPower(), 0);
    EXPECT_EQ(a.getYPower(), 0);
    EXPECT_EQ(a.getZPower(), 0);

    Monom b(-0.0);
    EXPECT_DOUBLE_EQ(b.getCoefficient(), 0.0);
}
//#############################################

TEST(MonomTest, EqualityAndInequality) {
    Monom a(4.0, 2, 1, 0);
    Monom b(4.0, 2, 1, 0);
    Monom c(4.1, 2, 1, 0);
    Monom d(4.0, 3, 1, 0);

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a == c);
    EXPECT_FALSE(a == d);

    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a != c);
    EXPECT_TRUE(a != d);
}

TEST(MonomTest, MultiplicationMonomByMonom) {
    Monom a(3.0, 2, 1, 0);
    Monom b(2.0, -1, 0, -3);
    Monom res = a * b;

    EXPECT_DOUBLE_EQ(res.getCoefficient(), 6.0);
    EXPECT_EQ(res.getXPower(), 1);
    EXPECT_EQ(res.getYPower(), 1);
    EXPECT_EQ(res.getZPower(), -3);
}

TEST(MonomTest, MultiplicationByScalar) {
    Monom a(5.0, 1, 2, 3);
    Monom b = a * 4.0;
    Monom c = a * (-1.5);

    EXPECT_DOUBLE_EQ(b.getCoefficient(), 20.0);
    EXPECT_EQ(b.getXPower(), 1);
    EXPECT_EQ(b.getYPower(), 2);
    EXPECT_EQ(b.getZPower(), 3);

    EXPECT_DOUBLE_EQ(c.getCoefficient(), -7.5);
    EXPECT_EQ(c.getXPower(), 1);
    EXPECT_EQ(c.getYPower(), 2);
    EXPECT_EQ(c.getZPower(), 3);
}

TEST(MonomTest, DivisionMonomByMonom) {
    Monom a(12.0, 4, 3, 2);
    Monom b(3.0, 1, 1, 0);
    Monom res = a / b;

    EXPECT_DOUBLE_EQ(res.getCoefficient(), 4.0);
    EXPECT_EQ(res.getXPower(), 3);
    EXPECT_EQ(res.getYPower(), 2);
    EXPECT_EQ(res.getZPower(), 2);
}

TEST(MonomTest, DivisionByScalar) {
    Monom a(10.0, 2, 0, 1);
    double k = 2.0;
    Monom b = a / k;
    EXPECT_DOUBLE_EQ(b.getCoefficient(), 5.0);

    Monom c = a / (-0.5);
    EXPECT_DOUBLE_EQ(c.getCoefficient(), -20.0);
}

TEST(MonomTest, DivisionByZeroScalarThrows) {
    Monom a(7.0, 1, 1, 1);
    EXPECT_THROW(a / 0.0, std::invalid_argument);
    EXPECT_THROW(a / 1e-15, std::invalid_argument);
    EXPECT_NO_THROW(a / 1e-11);                          
}

TEST(MonomTest, AdditionSamePowers) {
    Monom a(5.0, 2, 1, 0);
    Monom b(3.0, 2, 1, 0);
    Monom c(-2.0, 2, 1, 0);

    Monom sum1 = a + b;
    EXPECT_DOUBLE_EQ(sum1.getCoefficient(), 8.0);
    EXPECT_EQ(sum1.getXPower(), 2);
    EXPECT_EQ(sum1.getYPower(), 1);
    EXPECT_EQ(sum1.getZPower(), 0);

    Monom sum2 = a + c;
    EXPECT_DOUBLE_EQ(sum2.getCoefficient(), 3.0);
}

TEST(MonomTest, AdditionDifferentPowersThrows) {
    Monom a(1.0, 1, 0, 0);
    Monom b(1.0, 0, 1, 0);
    EXPECT_THROW(a + b, std::invalid_argument);
}

TEST(MonomTest, SubtractionSamePowers) {
    Monom a(7.5, 3, 0, 2);
    Monom b(2.5, 3, 0, 2);

    Monom diff = a - b;
    EXPECT_DOUBLE_EQ(diff.getCoefficient(), 5.0);
    EXPECT_EQ(diff.getXPower(), 3);
    EXPECT_EQ(diff.getZPower(), 2);
}

TEST(MonomTest, SubtractionDifferentPowersThrows) {
    Monom a(4.0, 0, 2, 0);
    Monom b(1.0, 1, 0, 0);
    EXPECT_THROW(a - b, std::invalid_argument);
}

TEST(MonomTest, UnaryMinus) {
    Monom a(6.4, 1, 2, 1);
    Monom b = -a;

    EXPECT_DOUBLE_EQ(b.getCoefficient(), -6.4);
    EXPECT_EQ(b.getXPower(), 1);
    EXPECT_EQ(b.getYPower(), 2);
    EXPECT_EQ(b.getZPower(), 1);

    Monom c(0.0, 5, 0, 0);
    Monom d = -c;
    EXPECT_DOUBLE_EQ(d.getCoefficient(), 0.0);
}

TEST(MonomTest, CompoundAssignmentOperators) {
    Monom a(2.0, 1, 0, 0);
    Monom b(3.0, 0, 1, 0);

    a *= Monom(4.0, 1, 0, 0);
    EXPECT_DOUBLE_EQ(a.getCoefficient(), 8.0);
    EXPECT_EQ(a.getXPower(), 2);

    Monom c(10.0, 2, 2, 2);
    c /= 5.0;
    EXPECT_DOUBLE_EQ(c.getCoefficient(), 2.0);

    Monom d(7.0, 1, 1, 1);
    d += Monom(3.0, 1, 1, 1);
    EXPECT_DOUBLE_EQ(d.getCoefficient(), 10.0);

    Monom e(8.0, 3, 0, 0);
    e -= Monom(5.0, 3, 0, 0);
    EXPECT_DOUBLE_EQ(e.getCoefficient(), 3.0);
}
//######################################################
TEST(MonomTest, EvaluateSimple) {
    Monom m(4.0, -2, 1, 0); 

    EXPECT_DOUBLE_EQ(m.solve(2.0, 3.0, 5.0), 4.0 * 0.25 * 3.0);
    EXPECT_DOUBLE_EQ(m.solve(1.0, 1.0, 1.0), 4.0);
    EXPECT_THROW(m.solve(0.0, 5.0, 7.0), std::invalid_argument);
}

TEST(MonomTest, EvaluateZeroCoefficient) {
    Monom m(0.0, 10, 10, 10);
    EXPECT_DOUBLE_EQ(m.solve(2.0, 3.0, 4.0), 0.0);
    EXPECT_DOUBLE_EQ(m.solve(0.0, 0.0, 0.0), 0.0);
}

TEST(MonomTest, PowerCompareInternal) {
    Monom a(1.0, 2, 3, 4);
    Monom b(9.9, 2, 3, 4);
    Monom c(1.0, 2, 4, 4);

    EXPECT_TRUE(a.powerCompare(b));
    EXPECT_FALSE(a.powerCompare(c));
}
TEST(MonomTest, Output) {
    Monom a(1.2, 2, 3, 4);
    std::ostringstream oss1;
    oss1 << a;
    EXPECT_EQ(oss1.str(), "1.2x^2y^3z^4");

    Monom b(1.2);
    std::ostringstream oss2;
    oss2 << b;
    EXPECT_EQ(oss2.str(), "1.2");

    Monom c(1.2, 0, 3, 0);
    std::ostringstream oss3;
    oss3 << c;
    EXPECT_EQ(oss3.str(), "1.2y^3");
}