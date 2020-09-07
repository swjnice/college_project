#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

/* --- DO NOT MODIFY --- */
template <class T>
class Stack {
private:
	class Node {
	private:
		Node * next;
		T data;

	public:
		Node(T d) {
			data = d;
		}
		Node(T d, Node* n) {
			data = d;
			next = n;
		}
		void setNext(Node* n) {
			next = n;
		}
		Node* getNext() {
			return next;
		}
		T getData() {
			return data;
		}
	};

private:
	Node * top;
	
public:
	Stack();
	~Stack();
	bool isEmpty() const;
	T getTop() const;
	int getSize() const;
	void push(const T&);
	T pop();
	void print() const;

};
/* --- DO NOT MODIFY --- */

template <class T>
Stack<T>::Stack() {
	// TODO
}

template <class T>
Stack<T>::~Stack() {
	// TODO
}

template <class T>
bool Stack<T>::isEmpty() const {
	// TODO
}

template <class T>
T Stack<T>::getTop() const {
	// TODO
}

template <class T>
int Stack<T>::getSize() const {
	// TODO
}

template <class T>
void Stack<T>::push(const T& newData) {
	// TODO
}

template <class T>
T Stack<T>::pop() {
	// TODO
}

template <class T>
void Stack<T>::print() const {
	// TODO
}

#endif