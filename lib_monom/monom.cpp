#include "../lib_monom/monom.h"
#include <cctype>

Monom::Monom(double _coefficent, int x, int y, int z) {
	factor.coefficient = _coefficent;
	factor.powers[0] = x;
	factor.powers[1] = y;
	factor.powers[2] = z;
}
Monom::Monom(double _coefficent, int fr_power, int sc_power, char val1, char val2) : factor{ _coefficent, {0,0,0} } {
	factor.coefficient = _coefficent;
	if (val1 == val2) throw std::invalid_argument("Identical variables");

	if (val1 == 'x')      factor.powers[0] = fr_power;
	else if (val1 == 'y') factor.powers[1] = fr_power;
	else if (val1 == 'z') factor.powers[2] = fr_power;
	else throw std::invalid_argument("Invalid variable");

	if (val2 == 'x')      factor.powers[0] = sc_power;
	else if (val2 == 'y') factor.powers[1] = sc_power;
	else if (val2 == 'z') factor.powers[2] = sc_power;
	else throw std::invalid_argument("Invalid variable");

}
Monom::Monom(double _coefficent, int power, char val) : factor{ _coefficent, {0,0,0} }
{
	factor.coefficient = _coefficent;
	if (val == 'x') factor.powers[0] = power;
	else if (val == 'y') factor.powers[1] = power;
	else if (val == 'z') factor.powers[2] = power;
	else throw std::invalid_argument("Invalid variable");
}
Monom::Monom(double _coefficent) : factor{ _coefficent, {0,0,0} }
{

}
Monom::Monom() {
	factor.coefficient = 0.0;
	for (int i = 0; i < MONOM; i++) {
		factor.powers[i] = 0;
	}
}
Monom::Monom(const Monom& other) 
	:factor(other.factor)
{

}

//################################################################
bool Monom::operator==(const Monom& other) const {
	return powerCompare(other);
}
bool Monom::operator!=(const Monom& other) const {
	return !(*this == other);
}
Monom Monom::operator*(const Monom& other) const{
	return Monom(
		factor.coefficient * other.factor.coefficient,
		factor.powers[0] + other.factor.powers[0],
		factor.powers[1] + other.factor.powers[1],
		factor.powers[2] + other.factor.powers[2]);
}
//Monom Monom::operator*(double k) const {
//	return Monom(
//		factor.coefficient * k,
//		factor.powers[0], factor.powers[1], factor.powers[2]
//	);
//}
Monom Monom::operator/(const Monom& other) const{ 
	double denom = other.getCoefficient();
	if (std::abs(denom)<1e-11) {
		throw std::invalid_argument("Division by zero");
	}
	return Monom(
		factor.coefficient / other.factor.coefficient,
		factor.powers[0] - other.factor.powers[0],
		factor.powers[1] - other.factor.powers[1],
		factor.powers[2] - other.factor.powers[2]);
}
//Monom Monom::operator/(double k) const {
//	if (k < 1e-12 && k > 1e-12) {
//		throw std::runtime_error("Division by zero");
//	}
//	return Monom(
//		factor.coefficient / k,
//		factor.powers[0], factor.powers[1], factor.powers[2]
//	);
//}
Monom Monom::operator+(const Monom& other) const {
	if (!powerCompare(other)) {
		throw std::invalid_argument("You cannot add dissimilar monomials");
	}
	return Monom(
		factor.coefficient + other.factor.coefficient,
		factor.powers[0], factor.powers[1], factor.powers[2]
	);
}

Monom Monom::operator-(const Monom& other) const {
	if (!powerCompare(other)) {
		throw std::invalid_argument("You cannot add dissimilar monomials");
	}
	return Monom(
		factor.coefficient - other.factor.coefficient,
		factor.powers[0], factor.powers[1], factor.powers[2]
	);
}

Monom Monom::operator-() const {
	return Monom(
		-factor.coefficient,
		factor.powers[0], factor.powers[1], factor.powers[2]
	);
}
Monom& Monom::operator=(const Monom& other) {
	if (this != &other) {
		factor = other.factor;
	}
	return *this;
}
Monom Monom::operator*=(const Monom& other) {
	setCoefficient(getCoefficient() * other.getCoefficient());
	setXPower(getXPower() + other.getXPower());
	setYPower(getZPower() + other.getYPower());
	setZPower(getZPower() + other.getZPower());
	return *this;
}
Monom Monom::operator-=(const Monom& other) {
	setCoefficient(getCoefficient() - other.getCoefficient());
	return *this;
}
Monom Monom::operator+=(const Monom& other) {
	setCoefficient(getCoefficient() + other.getCoefficient());
	return *this;
}
Monom Monom::operator/=(const Monom& other) {
	setCoefficient(getCoefficient() / other.getCoefficient());
	setXPower(getXPower() - other.getXPower());
	setYPower(getZPower() - other.getYPower());
	setZPower(getZPower() - other.getZPower());
	return *this;
}
//################################################################
double Monom::solve(double _x, double  _y, double _z)
{
	return factor.coefficient * pow(_x, getXPower()) * pow(_y, getYPower()) * pow(_z, getZPower());
}
bool Monom::powerCompare(const Monom& other) const {
	return factor.powers[0] == other.factor.powers[0] &&
		factor.powers[1] == other.factor.powers[1] &&
		factor.powers[2] == other.factor.powers[2];
}

double Monom::pow(double x, int power) {
	if (power < 0) {
		if (std::abs(x) < 1e-11) {
			throw std::invalid_argument("Division by zero");
		}
	}
	if (power == 0) return 1.0;
	if (power < 0) return 1.0 / pow(x, -power);
	if (power % 2 == 0) {
		double half = pow(x, power / 2);
		return half * half;
	}
	else {
		return x * pow(x, power - 1);
	}
}
//################################################################
std::ostream& operator<<(std::ostream& os, const Monom& m) {
	if (m.getCoefficient() != 0) {
		os << m.getCoefficient();
		if (m.getXPower() != 0) {
			os << "x^" << m.getXPower();
		}
		if (m.getYPower() != 0) {
			os << "y^" << m.getYPower();
		}
		if (m.getZPower() != 0) {
			os << "z^" << m.getZPower();
		}
	}
	else { return os; }
	return os;
}
std::istream& operator>>(std::istream& is, Monom& m) {
	double c; int ix, iy, iz;
	is >> c >> ix >> iy >> iz;
	if (is) {
		m = Monom(c, ix, iy, iz);
	}
	return is;
}