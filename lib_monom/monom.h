#include <iostream>
#include <string>
#include "../lib_stack/stack.h"
class Monom {
	unsigned int x_degre = 0, y_degre = 0, z_degre = 0;
	double coef;
public:
	void expression(std::string, unsigned int*, unsigned int*, unsigned int*, double* coef);

};