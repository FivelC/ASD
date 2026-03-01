#ifndef POLYNOM_H
#define POLYNOM_H
#include <iostream>
#include "../lib_doubly_linked_list/DoublyLinkedList.h"
#include "../lib_monom/monom.h"
class Polynom {
	DoublyLinkedList<Monom> polynom;
public: 
    bool isEmpty() const { return polynom.is_empty(); }
    size_t size() const { return polynom.size(); }

    using Iterator = DoublyLinkedList<Monom>::Iterator;
    Iterator begin() { return polynom.begin(); }
    Iterator end() { return polynom.end(); }

	Polynom();
	Polynom(const Polynom& other);
	Polynom(std::string expression);

    bool lexGreater(const Monom& a, const Monom& b);
    void insertSorted(const Monom& m);
    void normalize();

    Polynom& operator=(const Polynom& other);
    Polynom operator+(const Monom& other);
    Polynom operator-(const Monom& other);
    Polynom operator*(const Monom& other);

    Polynom operator+(Polynom& other);
    Polynom operator-(Polynom& other);
    Polynom operator*(Polynom& other);

    friend std::ostream& operator<<(std::ostream& ostr, Polynom& p);
};
#endif