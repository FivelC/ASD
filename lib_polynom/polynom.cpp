#include "polynom.h"

Polynom::Polynom() {
	
}

Polynom::Polynom(const Polynom& other) {
	polynom = other.polynom;
}
Polynom::Polynom(std::string expression) {
    *this = parse(expression);
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
	for (auto it = begin(); it != end(); ++it) {
		Monom prod = *it * other;
		res.insertSorted(prod);
	}
	return res;
}

Polynom Polynom::operator+( Polynom& other){
	Polynom result = *this;

	for (auto it = other.begin(); it != other.end(); ++it) {
		result.insertSorted(*it);
	}

	return result;
}

Polynom Polynom::operator-(Polynom& other) {
	Polynom result = *this;

	for (auto it = other.begin(); it != other.end(); ++it) {
		Monom negated = *it;
		negated.setCoefficient(-negated.getCoefficient());
		result.insertSorted(negated);
	}
	return result;
}
Polynom Polynom::operator*(Polynom& other)
{
	Polynom res;
	for (auto it1 = begin(); it1 != end(); ++it1) {
		for (auto it2 = other.begin(); it2 != other.end(); ++it2) {
			res.insertSorted((*it1) * (*it2));
		}
	}
	return res;
}
//##########################################################
void Polynom::insertSorted(const Monom& m) {
	if (m.getCoefficient() == 0) return;

	auto it = begin();
    size_t pos = 0;
	while (it != end() && !lexGreater(m, *it)) {
        if (it->powerCompare(m)) {
            Monom sum = *it + m;
            if (sum.getCoefficient() == 0.0) {
                it = polynom.erase(it);
            }
            else {
                *it = sum;
                ++it;
                pos++;
            }
            return;
        }
		++it;
        pos++;
	}

	polynom.insert(pos, m);
}

bool Polynom::lexGreater(const Monom& a, const Monom& b) {
	if (a.getXPower() != b.getXPower())   return a.getXPower() > b.getXPower();
	if (a.getYPower() != b.getYPower())   return a.getYPower() > b.getYPower();
	return a.getZPower() > b.getZPower();
}

Polynom Polynom::parse(const std::string& s) { //улучшить читабельность

    enum class State {
        Start,
        Coefficient,
        Variable,
        PowerStart,
        Power
    };

    Polynom result;

    State state = State::Start;

    double coef = 1.0;
    int x = 0, y = 0, z = 0;
    int sign = 1;

    std::string buffer;
    char currentVar;

    auto flushTerm = [&]() {
        result.insertSorted(Monom(sign * coef, x, y, z));
        coef = 1.0;
        x = 0;
        y = 0;
        z = 0;
        sign = 1;
    };

    for (size_t i = 0; i <= s.size(); ++i) {

        char c = (i < s.size()) ? s[i] : '\0';

        if (c == ' ') continue;

        switch (state) {

        case State::Start:
            if (c == '+' || c == '-') {
                if (i != 0) {
                    flushTerm();
                }
                sign = (c == '+') ? 1 : -1;
            }
            else if (isdigit(c) || c == '.') {
                buffer += c;
                state = State::Coefficient;
            }
            else if (c == 'x' || c == 'y' || c == 'z') {
                currentVar = c;
                state = State::Variable;
            }
            else if (c == '\0') {
                flushTerm();
            }
            else {
                throw std::invalid_argument("Unexpected character");
            }

            break;

        case State::Coefficient:
            if (isdigit(c) || c == '.') {
                buffer += c;
            }
            else {
                coef = std::stod(buffer);
                buffer.clear();
                state = State::Start;
                --i;
            }
            break;

        case State::Variable:
            if (c == '^') {
                state = State::PowerStart;
            }
            else {
                if (currentVar == 'x') x = 1;
                if (currentVar == 'y') y = 1;
                if (currentVar == 'z') z = 1;

                state = State::Start;
                --i;
            }
            break;

        case State::PowerStart:
            if (!isdigit(c))
                throw std::invalid_argument("Expected digit after ^");

            buffer += c;
            state = State::Power;
            break;

        case State::Power:
            if (isdigit(c)) {
                buffer += c;
            }
            else {
                int power = std::stoi(buffer);
                buffer.clear();

                if (currentVar == 'x') x = power;
                if (currentVar == 'y') y = power;
                if (currentVar == 'z') z = power;

                state = State::Start;
                --i;
            }
            break;
        }
    }

    return result;
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
