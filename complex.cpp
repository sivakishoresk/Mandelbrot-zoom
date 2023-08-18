#include "complex.h"
#include <cmath>

/*Default Constructor*/
complex::complex() {
	x = 0;
	y = 0;
}

/*Constructor with parameters*/
complex::complex(long double a, long double b) {
	x = a;
	y = b;
}

/*Returns the magnitude of the complex number*/
long double complex::mag() {
	return sqrt(x*x + y*y);
}

/*Overloading the addition operator*/
complex complex::operator+ (const complex &b) const {
	long double X = (this->x + b.x);
	long double Y = (this->y + b.y);
	return complex(X, Y);
}

/*Overloading the multiplication operator*/
complex complex::operator* (const complex &b) const {
	long double X = (this->x * b.x) - (this->y * b.y);
	long double Y = (this->x * b.y) + (this->y * b.x);
	return complex(X, Y);
}
