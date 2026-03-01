#include "polynom.h"

Polynom::Polynom() {
	
}

Polynom::Polynom(const Polynom& other) {
	polynom = other.polynom;
}
Polynom::Polynom(std::string expression) {
	//парсер
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
//			i++;              
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
}
//##########################################################
Polynom& Polynom::operator=(const Polynom& other) {
	if (this != &other) {
		polynom = other.polynom;
	}
	return *this;
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
	Polynom res;
	for (auto it1 = polynom.begin(); it1 != polynom.end(); ++it1) {
		for (auto it2 = other.polynom.begin(); it2 != other.polynom.end(); ++it2) {
			res.insertSorted((*it1) * (*it2));
		}
	}
	return res;
}
//##########################################################
void Polynom::insertSorted(const Monom& m) {
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
void Polynom::normalize() {

	for (auto it = polynom.begin(); it != polynom.end(); ) {

		auto jt = it;
		++jt;

		while (jt != polynom.end()) {

			if (*it == *jt) {

				it->setCoefficient(
					it->getCoefficient() + jt->getCoefficient()
				);

				jt = polynom.erase(jt); //special for iterator
			}
			else {
				++jt;
			}
		}

		if (it->getCoefficient() == 0.0) {
			it = polynom.erase(it);
		}
		else {
			++it;
		}
	}
}
bool Polynom::lexGreater(const Monom& a, const Monom& b) {
	if (a.getXPower() != b.getXPower())   return a.getXPower() > b.getXPower();
	if (a.getYPower() != b.getYPower())   return a.getYPower() > b.getYPower();
	return a.getZPower() > b.getZPower();
}
//##########################################################
std::ostream& operator<<(std::ostream& ostr, Polynom& p) {
	if (p.isEmpty()) {
		ostr << "0";
		return ostr;
	}

	auto it = p.begin();
	ostr << *it;

	++it;
	for (it; it != p.end(); ++it) {
		const Monom& m = *it;
		if (m.getCoefficient() >= 0) {
			ostr << " + ";
		}
		else {
			ostr << " - ";
		}
		ostr << m;
	}

	return ostr;
}
