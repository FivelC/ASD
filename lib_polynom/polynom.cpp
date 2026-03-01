#include "polynom.h"

Polynom::Polynom() {
	
}

Polynom::Polynom(const Polynom& other) {
	polynom = other.polynom;
}
Polynom::Polynom(std::string expression) {
	//парсер
}
void Polynom::insertSorted(const Monom& m){
	if (m.getCoefficient() == 0) return;

	auto it = polynom.begin();
	size_t pos = 0;
	while (it != polynom.end() && !lexGreater(m, *it)) {
		++it;
		pos++;
	}
	polynom.insert(pos, m);
	normalize();
}

Polynom Polynom::operator+(const Monom& other) {
	Polynom res = *this;
	res.insertSorted(other);
	return res;
}

Polynom Polynom::operator-(const Monom& other) {
	Polynom res = *this;
	Monom neg = other;
	neg.setCoefficient(-neg.getCoefficient());
	res.insertSorted(neg);
	return res;
}

Polynom Polynom::operator*(const Monom& other){
	Polynom res;
	for (auto it = polynom.begin(); it != polynom.end(); ++it) {
		Monom prod = *it * other;
		res.insertSorted(prod);
	}
	return res;
}

Polynom Polynom::operator+( Polynom& other){
	Polynom result = *this;

	for (auto it = other.polynom.begin(); it != other.polynom.end(); ++it) {
		result.insertSorted(*it);
	}

	return result;
}

Polynom Polynom::operator-(Polynom& other) {
	Polynom result = *this;

	for (auto it = other.polynom.begin(); it != other.polynom.end(); ++it) {
		Monom negated = *it;
		negated.setCoefficient(-negated.getCoefficient());
		result.insertSorted(negated);
	}
	return result;
}
Polynom Polynom::operator*(Polynom& other)
{
	Polynom res = *this;
	for (auto it = other.polynom.begin(); it != other.polynom.end(); ++it)
	{
		res = res + (*this) * (*it);
	}
	return res;
}

void Polynom::normalize() {
	if (polynom.is_empty()) return;
	auto cur = polynom.begin();
	size_t pos = 0;
	while (cur != nullptr) {
		auto next = cur;
		++next;
		while (cur != polynom.end()) {
			if (*cur == *next) {
				double new_coef = cur->getCoefficient() + next->getCoefficient();
				cur->setCoefficient(new_coef);
				polynom.erase(pos + 1);
			}
			else {
				++cur;
				++pos;
			}
		}
		if (cur->getCoefficient() == 0.0) {
			polynom.erase(pos);
		}
		else {
			++cur;
			++pos;
		}
	}
}
bool Polynom::lexGreater(const Monom& a, const Monom& b) {
	if (a.getXPower() != b.getXPower())   return a.getXPower() > b.getXPower();
	if (a.getYPower() != b.getYPower())   return a.getYPower() > b.getYPower();
	return a.getZPower() > b.getZPower();
}

//ostream& operator<<(ostream& ostr, const Polynomial& p)
//{
//	for (auto it = p.monoms.begin(); it != p.monoms.end(); ++it)
//	{
//		ostr << *it << " + ";
//	}
//	return ostr;
//}
