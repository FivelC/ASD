#ifndef MONOM_H
#define MONOM_H
#include <iostream>
#include <string>
#include <math.h>
#include "../lib_stack/stack.h"
#include <cfloat>
#include <ostream>
#define MONOM 3
class Monom {
	struct Factor {
		double coefficient;
		unsigned int powers[MONOM];
	};
	Factor factor;

public:

	Monom(double _coefficent, int x, int y, int z);
	Monom(double _coefficent, int x, int y, char val1, char val2);
	Monom(double _coefficent, int x, char val);
	Monom(double _coefficent);
	Monom();
	Monom(const Monom& other);

	double getCoefficient() const { return factor.coefficient; }
	int getXPower() const { return factor.powers[0]; }
	int getYPower() const { return factor.powers[1]; }
	int getZPower() const { return factor.powers[2]; }

	void setCoefficient(double coef) { factor.coefficient = coef; }
	void setXPower(int x) { factor.powers[0] = x; }
	void setYPower(int y) { factor.powers[1] = y; }
	void setZPower(int z) { factor.powers[2] = z; }

	bool powerCompare(const Monom& other) const;

	double solve(double _x, double  _y, double _z);


	bool operator==(const Monom& other) const;
	bool operator!=(const Monom& other) const;
	Monom operator*(const Monom& other) const;
	//Monom operator*(double k) const;
	Monom operator/(const Monom& other) const;
	//Monom operator/(double k) const;
	Monom operator+(const Monom& other) const;
	Monom operator-(const Monom& other) const;
	Monom operator-() const;
	Monom& operator=(const Monom& other);
	Monom operator*=(const Monom& other);
	Monom operator-=(const Monom& other);
	Monom operator+=(const Monom& other);
	Monom operator/=(const Monom& other);

	friend std::ostream& operator<<(std::ostream& ostr, const Monom& m);
	friend std::istream& operator>>(std::istream& istr, Monom& m);
};
double pow(double x, int power);
#endif