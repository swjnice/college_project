#include "HW1_Figure.h"

int main() {
	Figure* r1 = new Rectangle(0, 0, 5, 4);
	Figure* r2 = new Rectangle(-1, -3, 2, 3);
	Figure* c1 = new Circle(0, 0, 3);
	Figure* c2 = new Circle(1, 3, 9);

	cout << *r1 << *r2 << *c1 << *c2 << endl;

	r1->shift(-1, -1);
	r2->shift(1, 3);
	c1->shift(3, 3);
	c2->shift(-1, -3);

	cout << *r1 << *r2 << *c1 << *c2 << endl;

	delete r1;
	delete r2;
	delete c1;
	delete c2;

	return 0;
}