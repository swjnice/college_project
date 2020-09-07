#pragma once
#include <iostream>

using namespace std;

int lc(int i);
int rc(int i);

class MinHeap
{
private:
	int* arr;
	size_t arr_size;
	size_t heap_size;
public:
	MinHeap(int* &buf, int input_size);
	~MinHeap();
	inline void swap(int i, int j);
	void setheapsize(int heapsize);
	void setsize(int size);
	void min_heapify(int i);
	void build_minheap();
	int getheapsize();
	void min_heapify2();
	void restheapify(int restnumber);
	void heapsizereturn();
};