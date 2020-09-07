#include "HW1_NaryBigNum.h"

void main() {
	NaryBigNum a(16, "3G@36");
	NaryBigNum b(16, "c6C77");
	NaryBigNum c(8, "1941");
	NaryBigNum d(8, "1554A12");

	cout << "a : " << a << endl;
	cout << "b : " << b << endl;
	cout << "c : " << c << endl;
	cout << "d : " << d << endl;

	NaryBigNum e = a + b;
	cout << "a + b : " << e << endl;

	NaryBigNum f(a * b);
	cout << "a * b : " << f << endl;

	NaryBigNum g;
	g = c + d;
	cout << "c + d : " << g << endl;

	cout << "c * d : " << c * d << endl;
}