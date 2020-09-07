#include "HW3_HashTable.h"

int main() {

	HashTable<int> *map = new HashTable<int>(7);

	cout << "Insert Node (Key : 1, Value : 10)" << endl;
	map->insertNode(1, 10);

	cout << "Insert Node (Key : 11, Value : 11)" << endl;
	map->insertNode(11, 11);

	cout << "Insert Node (Key : 8, Value : 12), induce collision" << endl;
	map->insertNode(8, 12);

	cout << "<Current HashTable>" << endl;
	map->display();

	cout << "Insert Node (Key : 21, Value : 13), need capacity doubling" << endl;
	map->insertNode(21, 13);
	cout << "<Current HashTable>" << endl;
	map->display();

	cout << "Delete Node (Key : 11)" << endl;
	map->deleteNode(11);
	cout << "<Current HashTable>" << endl;
	map->display();

	cout << "Insert Node (Key : 11, Value : 20), key 11 is already existed, only update value" << endl;
	map->insertNode(11, 20);
	cout << "<Current HashTable>" << endl;
	map->display();

	cout << "Delete Node (Key : 27), but doesn't exist" << endl;
	map->deleteNode(27);
	cout << endl;

	cout << "Search node that key is 21" << endl;
	cout << "Value : " << map->search(21) << endl;

	delete map;

	return 0;
}