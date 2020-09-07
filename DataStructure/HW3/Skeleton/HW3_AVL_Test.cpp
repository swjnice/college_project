#include <iostream>
#include "HW3_AVL.h"
using namespace std;

int main() {
	AVL *dict = new AVL();
	dict->insert(30, 3.3);
	dict->insert(40, 4.4);
	dict->insert(50, 5.5);
	cout << dict->getHeight() << endl;
	dict->insert(80, 8.8);
	dict->insert(60, 6.6);
	dict->preorder(); cout << endl;
	dict->postorder(); cout << endl;
	dict->levelorder(); cout << endl;
	dict->insert(90, 9.9);
	dict->levelorder(); cout << endl;
	dict->insert(40, 4.444);
	cout << dict->getHeight() << endl;
	dict->levelorder(); cout << endl;
	dict->insert(42, 4.2);
	dict->insert(41, 4.1);
	cout << dict->getHeight() << endl;
	dict->levelorder(); cout << endl;
	dict->remove(40);
	cout << dict->getHeight() << endl;
	dict->levelorder(); cout << endl;
	dict->insert(20, 2.2);
	dict->insert(32, 3.2);
	dict->insert(31, 3.1);
	dict->insert(70, 7.7);
	dict->insert(68, 6.8);
	cout << dict->getHeight() << endl;
	dict->levelorder(); cout << endl;
	dict->remove(20);
	cout << dict->getHeight() << endl;
	dict->levelorder(); cout << endl;
}