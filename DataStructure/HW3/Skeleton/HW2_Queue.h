#ifndef HW2_QUEUE_H
#define HW2_QUEUE_H

#include <iostream>

using namespace std;

template <class T>
class Queue
{
private:
	int front;
	int rear;
	int size;
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

template <class T>
Queue<T>::Queue(int c) {
	array = new T[c];
	capacity = c;
	front = 0;
	rear = 0;
	size = 0;
}

template <class T>
Queue<T>::~Queue() {
	delete[] array;
}

template <class T>
bool Queue<T>::isEmpty() const {
	return getSize() == 0;
}

template <class T>
T Queue<T>::getFront() const {
	return isEmpty() ? T() : array[(front + 1) % capacity];
}

template <class T>
T Queue<T>::getRear() const {
	return isEmpty() ? T() : array[rear];
}

template <class T>
int Queue<T>::getSize() const {
	return (rear - front + capacity) % capacity;
}

template <class T>
int Queue<T>::getCapacity() const {
	return capacity;
}

template <class T>
void Queue<T>::push(const T& x) {
	if (getSize() + 1 == capacity) {
		T* newArray = new T[2 * capacity];
		int start = (front + 1) % capacity;
		if (start < 2)
			for (int i = 0; i < capacity - 1; i++)
				newArray[i] = array[start + i];
		else {
			for (int i = 0; i < capacity - start; i++)
				newArray[i] = array[start + i];
			for (int i = 0; i < rear + 1; i++)
				newArray[i + capacity - start] = array[i];
		}
		front = 2 * capacity - 1;
		rear = capacity - 2;
		capacity *= 2;
		delete[] array;
		array = newArray;
	}
	rear = (rear + 1) % capacity;
	array[rear] = x;
}

template <class T>
T Queue<T>::pop() {
	if (isEmpty())
		return T();
	else
		front = (front + 1) % capacity;
	return array[front];
}

template <class T>
void Queue<T>::print() const {
	cout << "[";
	for (int i = (front + 1) % capacity; i <= (rear < front && front + 1 != capacity ? rear + capacity : rear); i++) {
		cout << array[i % capacity];
		if ((i % capacity) != rear) cout << ", ";
	}
	cout << "]" << endl;
}

template <class T>
void Queue<T>::shift(int amount)
{
	if (!isEmpty()) {
		int curr_size = (front < rear) ? rear - front : capacity - front + rear;

		amount = amount % curr_size;
		if (amount > 0)
			amount -= curr_size;

		while (amount < 0) {
			rear = (rear + 1) % capacity;
			array[rear] = array[(front + 1) % capacity];
			front = (front + 1) % capacity;
			amount++;
		}
	}
}

#endif
