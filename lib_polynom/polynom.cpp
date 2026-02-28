#include "polynom.h"

Polynom::Polynom() {
	
}

Polynom::Polynom(const Polynom& other) {
	polynom = other.polynom;
}
Polynom::Polynom(std::string expression) {
	//парсер
}

Polynom Polynom::operator+(const Monom& other) {
	Polynom res = Polynom(*this);
	for (auto it = polynom.begin(); it != polynom.end(); ++it) {

	}
}