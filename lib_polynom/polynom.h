#include <iostream>
#include "../lib_doubly_linked_list/DoublyLinkedList.h"
#include "../lib_monom/monom.h"
class Polynom {
	DoublyLinkedList<Monom> polynom;
public: 
	Polynom();
	Polynom(const Polynom& other);
	Polynom(std::string expression);

    bool lexGreater(const Monom& a, const Monom& b);
    void insertSorted(const Monom& m);
    void normalize();

    Polynom operator+(const Monom& other);
    Polynom operator-(const Monom& other);
    Polynom operator*(const Monom& other);

    Polynom operator+(Polynom& other);
    Polynom operator-(Polynom& other);
    Polynom operator*(Polynom& other);
};