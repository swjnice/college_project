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
	void display();
};

template <class V>
HashTable<V>::HashTable(int cap) {
	// TODO
}


template <class V>
HashTable<V>::~HashTable() {
	// TODO
}

template <class V>
void HashTable<V>::tableDoubling() {
	// TODO
}


template <class V>
void HashTable<V>::insertNode(int key, V value) {
	// TODO
}

template <class V>
V HashTable<V>::deleteNode(int key) {
	// TODO
}

template <class V>
V HashTable<V>::search(int key) {
	//TODO
}


template <class V>
void HashTable<V>::display() {
	//TODO
}

#endif
