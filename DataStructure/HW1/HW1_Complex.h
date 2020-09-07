#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

using namespace std;

template <class T>
class Complex {
private:
	T re;
	T im;

public:
	// TODO: Define member functions declared as below
	// You can add other member functions if you need
	Complex();
	Complex(T, T);
	Complex operator+ (const Complex&);
	Complex operator- (const Complex&);
	Complex operator* (const Complex&);
	Complex operator~ () const;

	template <class U>
	friend ostream& operator<< (ostream&, const Complex<U>&);
};


void solveQuadratic(Complex<double>&, Complex<double>&, int, int, int);
// TODO: Define a global function declared as below

#endif