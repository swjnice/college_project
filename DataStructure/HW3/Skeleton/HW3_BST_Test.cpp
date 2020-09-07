#include "HW3_BST.h"

int main() {
	BST* dict = new BST();
	dict->insert(4, 4.44);
	dict->insert(3, 3.33);
	dict->insert(6, 6.66);
	dict->insert(1, 1.11);
	dict->insert(5, 5.55);
	dict->insert(8, 8.88);
	dict->insert(7, 7.77);
	dict->insert(9, 9.99);

	cout << "Preorder : \n"; dict->preorder(); cout << endl;
	cout << "Postorder : \n"; dict->postorder(); cout << endl;
	cout << "Levelorder : \n"; dict->levelorder(); cout << endl << endl;

	BST* dict2 = new BST();
	dict2->insert(3, 1.33);
	dict2->insert(0, 0.12);
	dict2->insert(10, 10.1);
	dict2->insert(6, 0.66);

	cout << "Preorder : \n"; dict2->preorder(); cout << endl;
	cout << "Postorder : \n"; dict2->postorder(); cout << endl;
	cout << "Levelorder : \n"; dict2->levelorder(); cout << endl << endl;

	dict->merge(*dict2);

	cout << "Preorder after merge (dict) : \n"; dict->preorder(); cout << endl;
	cout << "Postorder after merge (dict) : \n"; dict->postorder(); cout << endl;
	cout << "Levelorder after merge (dict) : \n"; dict->levelorder(); cout << endl << endl;

	cout << "Preorder after merge (dict2) : \n"; dict2->preorder(); cout << endl;
	cout << "Postorder after merge (dict2) : \n"; dict2->postorder(); cout << endl;
	cout << "Levelorder after merge (dict2) : \n"; dict2->levelorder(); cout << endl;

	delete dict;
	delete dict2;
}