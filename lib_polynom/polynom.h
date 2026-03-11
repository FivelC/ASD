#ifndef POLYNOM_H
#define POLYNOM_H
#include <iostream>
#include "../lib_doubly_linked_list/DoublyLinkedList.h"
#include "../lib_monom/monom.h"
//#include "../lib_parser/Parser.h"
class Polynom {
	DoublyLinkedList<Monom> polynom;
public: 
    bool isEmpty() const { return polynom.is_empty(); }
    size_t size() const { return polynom.size(); }

    DoublyLinkedList<Monom>::Iterator begin() { return polynom.begin(); }
    DoublyLinkedList<Monom>::Iterator end() { return polynom.end(); }

	Polynom();
	Polynom(const Polynom& other);
	Polynom(std::string expression);

    bool lexGreater(const Monom& a, const Monom& b);
    void insertSorted(const Monom& m);
    void normalize();
    Polynom parse(const std::string& s);

    Polynom& operator=(const Polynom& other);
    Polynom operator+(const Monom& other);
    Polynom operator-(const Monom& other);
    Polynom operator*(const Monom& other);

    Polynom operator+(Polynom& other);
    Polynom operator-(Polynom& other);
    Polynom operator*(Polynom& other);
     //+= через + ..

    friend std::ostream& operator<<(std::ostream& ostr, Polynom& p);
};
#endif