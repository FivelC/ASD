#include <iostream>
#include "../lib_doubly_linked_list/DoublyLinkedList.h"
#include "../lib_monom/monom.h"
class Polynom {
	DoublyLinkedList<Monom> polynom;
public: 
	Polynom();
	Polynom(const Polynom& other);
	Polynom(std::string expression);

    bool lexGreater(const Monom& a, const Monom& b) {
        if (a.getXPower() != b.getXPower())   return a.getXPower() > b.getXPower();
        if (a.getYPower() != b.getYPower())   return a.getYPower() > b.getYPower();
        return a.getZPower() > b.getZPower();
    }

    Polynom operator+(const Monom& other);
    Polynom operator-(const Monom& other);
    Polynom operator*(const Monom& other);

    Polynom operator+(const Polynom& other);
    Polynom operator-(const Polynom& other);
};