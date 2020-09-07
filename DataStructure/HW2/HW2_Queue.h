#ifndef HW2_QUEUE_H
#define HW2_QUEUE_H

#include <iostream>

using namespace std;

/* --- DO NOT MODIFY --- */
template <class T>
class Queue
{
private:
	int front;
	int rear;
	T* array;
	int capacity;
public:
	Queue(int c);
	~Queue();
	bool isEmpty() const;
	T getFront() const;
	T getRear() const;
	int getSize() const;
	int getCapacity() const;
	void push(const T& x);
	T pop();
	void print() const;
	void shift(int amount);
};
/* --- DO NOT MODIFY --- */

template <class T>
Queue<T>::Queue(int c) {
	// TODO
}

template <class T>
Queue<T>::~Queue() {
	// TODO
}

template <class T>
bool Queue<T>::isEmpty() const {
	// TODO
}

template <class T>
T Queue<T>::getFront() const {
	// TODO
}

template <class T>
T Queue<T>::getRear() const {
	// TODO
}

template <class T>
int Queue<T>::getSize() const {
	// TODO
}

template <class T>
int Queue<T>::getCapacity() const {
	// TODO
}

template <class T>
void Queue<T>::push(const T& x) {
	// TODO
}

template <class T>
T Queue<T>::pop() {
	// TODO
}

template <class T>
void Queue<T>::print() const {
	// TODO
}

template <class T>
void Queue<T>::shift(int amount) {
	// TODO
}

#endif