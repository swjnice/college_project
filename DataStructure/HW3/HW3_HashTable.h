#ifndef HW3_HASH_H
#define HW3_HASH_H

#include <iostream>
using namespace std;

template <class V>

class HashTable {
private:
	template <class V>
	class HashNode {
	public:
		int key;
		V value;
		HashNode(int key_, V value_) {
			key = key_;
			value = value_;
		}
	};
	HashNode<V> **table;
	int capacity;
	int number;
	HashNode<V> *dummy;

public:
	HashTable(int cap);
	~HashTable();
	void tableDoubling();
	int hashFunction(int key) {
		return key % capacity;
	}
	void insertNode(int key, V value);
	V deleteNode(int key);
	V search(int key);
	int pos_search(int key);
	void display();
};

template <class V>
HashTable<V>::HashTable(int cap) {
	this->capacity = cap;
	int number = 0;
	dummy = new HashNode<V>(-1, NULL);
	table = new HashNode<V>* [cap];
	for (int i = 0; i < cap; i++) { // All table value initialized as nullptr
		table[i] = nullptr;
	}
}


template <class V>
HashTable<V>::~HashTable() {
	for (int i = 0; i < capacity; i++) {
		if (table[i] != nullptr) {
			delete table[i];
		}
	}
	delete[] table;
	delete dummy;
}

template <class V>
void HashTable<V>::tableDoubling() {
	if (number > capacity / 2) {
		// Copy all origin value before doubling
		int orig_capacity = this->capacity;
		HashNode<V>** orig_table = new HashNode<V>*[orig_capacity];
		for (int i = 0; i < capacity; i++) { 
			orig_table[i] = this->table[i];
		}

		// delete and update
		delete[] this->table;
		this->capacity = 2 * orig_capacity;
		this->number = 0;
		
		// re-Hashing doubled table
		this->table = new HashNode<V> * [this->capacity];
		for (int j = 0; j < capacity; j++) {
			table[j] = nullptr;
		}
		for (int j = 0; j < orig_capacity; j++) {
			if (orig_table[j] != nullptr && orig_table[j] != dummy) {
				this->insertNode(orig_table[j]->key, orig_table[j]->value);
			}
		}

		// delete copied table
		for (int i = 0; i < orig_capacity; i++) {
			if (orig_table[i] != nullptr && orig_table[i] != dummy) {
				delete orig_table[i];
			}
		}
		delete[] orig_table;
	}
}


template <class V>
void HashTable<V>::insertNode(int key, V value) {
	int pos = key % capacity;
	if (table[pos] == nullptr || table[pos] == dummy) {
		table[pos] = new HashNode<V>(key, value);
		number++;
		// table doubling
		if (number > capacity / 2) {
			this->tableDoubling();
		}
	}
	//when have same key
	else if (table[pos]->key == key) {
		table[pos]->value = value;
	}
	// find empty space and insert
	else { 
		while (table[pos] != nullptr && table[pos] != dummy) { 
			pos = (pos + 1) % (capacity + 1);
		}
		table[pos] = new HashNode<V>(key, value);
		number++;
		//table doubling
		if (number > capacity / 2) {
			this->tableDoubling();
		}
	}
}

template <class V>
V HashTable<V>::deleteNode(int key) {
	int key_search = this->pos_search(key);
	// if there is same key
	if (key_search == NULL) {
		cout << "key <" << key << "> does not exist." << endl;
		return NULL;
	}

	delete this->table[key_search];
	this->table[key_search] = dummy;
	number--;
}

template <class V>
V HashTable<V>::search(int key) {
	int pos = this->pos_search(key);
	if (pos == NULL) {
		return NULL;
	}
	return this->table[pos]->value;
}

// find the position where have key
template <class V>
int HashTable<V>::pos_search(int key) {
	int pos = this->hashFunction(key);
	while (this->table[pos] != nullptr && this->table[pos] != dummy) {
		if (this->table[pos]->key == key) {
			return pos;
		}
		pos++;
	}
	return NULL;
}


template <class V>
void HashTable<V>::display() {
	cout << "Capacity : " << capacity << ", The number of nodes : " << number << endl;
	for (int i = 0; i < capacity; i++) {
		if (table[i] != nullptr && table[i] != dummy) {
			cout << "address " << i << ", key = " << table[i]->key << ", value = " << table[i]->value << endl;
		}
	}
	cout << endl;
}

#endif
