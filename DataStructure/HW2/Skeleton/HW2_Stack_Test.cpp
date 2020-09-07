#include "HW2_Stack.h"

#include <iostream>
using namespace std;


void main() {
	int i;
	Stack<int> *a = new Stack<int>;

	cout << "# initialization" << endl;
	cout << "Top : " << a->getTop() << endl;
	a->print();
	cout << endl;

	cout << "# Push 10 times" << endl;
	for (i = 1; i <= 10; i++) {
		cout << "Push " << i << endl;
		a->push(i);
	}
	cout << "Top : " << a->getTop() << endl;
	a->print();
	cout << endl;

	cout << "# Pop 4 times" << endl;
	for (i = 1; i <= 4; i++) {
		cout << "Pop " << a->pop() << endl;
	}
	cout << "Top : " << a->getTop() << endl;
	a->print();
	cout << endl;

	cout << "# Push 2 times" << endl;
	for (i = 1; i <= 2; i++) {
		cout << "Push : " << i * 100 << endl;
		a->push(i * 100);
	}
	cout << "Top : " << a->getTop() << endl;
	a->print();
	cout << endl;

	cout << "# Pop 6 times" << endl;
	for (i = 1; i <= 6; i++) {
		cout << "Pop " << a->pop() << endl;
	}
	cout << "Top : " << a->getTop() << endl;
	a->print();
	cout << endl;


	delete a;
}