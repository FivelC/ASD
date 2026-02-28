#include <gtest/gtest.h>
#include <iostream>
#include "../lib_monom/monom.h"

//TEST(MonomTest, Input) {
//	Monom monom;
//	unsigned int x_deg = 0, y_deg = 0, z_deg = 0;
//	double coef = 0.0;
//	monom.expression("123x^2y^3z^4", &x_deg, &y_deg, &z_deg, &coef);
//
//	EXPECT_EQ(coef, 123.0);  // коэффициент
//	EXPECT_EQ(x_deg, 2);       // степень x
//	EXPECT_EQ(y_deg, 3);       // степень y
//	EXPECT_EQ(z_deg, 4);
//}
TEST(Monom_test, DefaultConstraction) {
    Monom a;
    EXPECT_EQ(a.getCoefficient(), 0.0);
    EXPECT_EQ(a.getXPower(), 0);
    EXPECT_EQ(a.getYPower(), 0);
    EXPECT_EQ(a.getZPower(), 0);
}
TEST(Monom_test, ThreeInit) {
    Monom a(123.1, 1, 2, 3);
    EXPECT_EQ(a.getCoefficient(), 123.1);
    EXPECT_EQ(a.getXPower(), 1);
    EXPECT_EQ(a.getYPower(), 2);
    EXPECT_EQ(a.getZPower(), 3);
}
TEST(Monom_test, TwoInit) {
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
TEST(Monom_test, OneInit) {
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
TEST(Monom_test, Copy) {
    Monom a(123.1, 1, 'y');
    Monom b(a);
    EXPECT_EQ(b.getCoefficient(), a.getCoefficient());
    EXPECT_EQ(b.getXPower(), a.getXPower());
    EXPECT_EQ(b.getYPower(), a.getYPower());
    EXPECT_EQ(b.getZPower(), a.getZPower());
}
//TEST(Monom_test, )