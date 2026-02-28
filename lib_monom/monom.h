#include <iostream>
#include <string>
#include <math.h>
#include "../lib_stack/stack.h"
//class Monom {
//	std::string expr;
//	unsigned int x_degre = 0, y_degre = 0, z_degre = 0;
//	double coef;
//public:
//	std::string getExpr() { return expr; }
//	unsigned int getXdegree() { return x_degre; }
//	unsigned int getYdegree() { return y_degre; }
//	unsigned int getZdegree() { return z_degre; }
//	double getCoef() { return coef; }
//	void expression(std::string, unsigned int*, unsigned int*, unsigned int*, double* coef);
//
//};
//
//void Monom::expression(std::string exem, unsigned int* x_degre, unsigned int* y_degre, unsigned int* z_degre, double* coef) {
//	int i = 0;
//	double tmp_coef = 0.0;
//	while (i < exem.size() - 1 && (std::isdigit(exem[i]) || exem[i] == '.')) {
//		if (exem[i] == '.') {
//			i++;
//			while (i < exem.size() && std::isdigit(exem[i])) {
//				tmp_coef *= 0.1;
//				tmp_coef = tmp_coef * 10 + (exem[i] - '0');
//				i++;
//			}
//			break;
//		}
//		tmp_coef = tmp_coef * 10 + (exem[i] - '0');
//		i++;
//	}
//	*coef = tmp_coef;
//
//
//	while (i < exem.size()) {
//		if (!std::isalpha(exem[i])) {
//			i++;              // ← гарантированный сдвиг
//			continue;
//		}
//
//		char var = exem[i++];
//		unsigned int deg = 1;
//
//		if (i < exem.size() && exem[i] == '^') {
//			i++;
//			deg = 0;
//			while (i < exem.size() && std::isdigit(exem[i])) {
//				deg = deg * 10 + (exem[i] - '0');
//				i++;
//			}
//		}
//
//		if (var == 'x') *x_degre = deg;
//		else if (var == 'y') *y_degre = deg;
//		else if (var == 'z') *z_degre = deg;
//	}
//
//}
#include <string>
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

	double pow(double x, int power);
	bool powerCompare(const Monom& other) const;

	double solve(double _x, double  _y, double _z);


	bool operator==(const Monom& other) const;
	bool operator!=(const Monom& other) const;
	Monom operator*(const Monom& other);
	Monom operator*(double k) const;
	Monom operator/(const Monom& other);
	Monom operator/(double k) const;
	Monom operator+(const Monom& other) const;
	Monom operator-(const Monom& other) const;
	Monom operator-() const;
	Monom& operator=(const Monom& other) const;
	Monom operator*=(const Monom& other);
	Monom operator-=(const Monom& other);
	Monom operator+=(const Monom& other);
	Monom operator/=(const Monom& other);

	friend std::ostream& operator<<(std::ostream& ostr, const Monom& m);
	friend std::istream& operator>>(std::istream& istr, Monom& m);
	bool isNull();
};