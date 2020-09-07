#include "HW1_Complex.h"

int main() {
	Complex<int> a;
	Complex<int> b(5, 3);
	Complex<double> c(2.1542, 7);
	Complex<double> d(-3.2121, -4.6089);

	cout << "a : " << a;
	cout << "b : " << b;
	cout << "c : " << c;
	cout << "d : " << d;

	cout << "a + b : " << a + b;
	cout << "c - d : " << c - d;
	cout << "a * b : " << a * b;
	cout << "d * c : " << d * c;

	cout << endl;

	Complex<double> x1, x2;
	int a1 = 1, a2 = 4, a3 = 3;
	solveQuadratic(x1, x2, a1, a2, a3);
	cout << "The solution of " << a1 << "x^2 + " << a2 << "x + " << a3 << " = 0 : " << endl;
	cout << x1 << x2;

	a3 = 4;
	solveQuadratic(x1, x2, a1, a2, a3);
	cout << "The solution of " << a1 << "x^2 + " << a2 << "x + " << a3 << " = 0 : " << endl;
	cout << x1 << x2;

	a3 = 5;
	solveQuadratic(x1, x2, a1, a2, a3);
	cout << "The solution of " << a1 << "x^2 + " << a2 << "x + " << a3 << " = 0 : " << endl;
	cout << x1 << x2;


	return 0;
}