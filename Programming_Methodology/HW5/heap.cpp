#include "heap.h"

#include <iostream>

using namespace std;



int lc(int i)	//index of left child
{
	return 2 * i;
}

int rc(int i)	//index of right child
{
	return (2 * i) + 1;
}

	MinHeap::MinHeap(int* &buf, int input_size)
	{
		this->arr = buf;
		this->arr_size = input_size;
		this->heap_size = input_size;
	}

	MinHeap::~MinHeap()
	{

	}

	inline void MinHeap::swap(int i, int j)	//swap elements of arr
	{
		int temp = *(arr + (i - 1));
		*(arr + (i - 1)) = *(arr + (j - 1));
		*(arr + (j - 1)) = temp;
	}

	void MinHeap::setheapsize(int heapsize) { // set heapsize
		this->heap_size = heapsize;
	}

	void MinHeap::setsize(int size) { // if data_size < initial buffe rsize get the all size as data size
		this->arr_size = size;
		this->heap_size = size;
	}

	void MinHeap::min_heapify(int i) // heapify the number of position 'i'
	{
		int smallest;
		int Left = lc(i);
		int Right = rc(i);

		if (Left <= heap_size && *(arr + (Left - 1)) < *(arr + (i - 1))) { //if Left > i
			smallest = Left;
		}
		else {
			smallest = i;
		}
		if (Right <= heap_size && *(arr + (Right - 1)) < *(arr + (smallest - 1))) { //if Right > i
			smallest = Right;
		}

		if (smallest != i) { //if i is not the smallest among i, Left, Right swap i with largest one and heapify the swapped one
			swap(smallest, i);
			min_heapify(smallest);
		}

	}

	void MinHeap::build_minheap() // heapify the whole heap at the first time
	{
		for (int i = arr_size / 2; i >= 1; i--) {
			min_heapify(i);
		}
	}

	int MinHeap::getheapsize() { // reuturn heapsize
		return heap_size;
	}

	void MinHeap::min_heapify2(){ // if smaller number is read on the top of the heap get that number on outside of the heap
		swap(1, heap_size);
		heap_size--;
		min_heapify(1);
	}

	void MinHeap::restheapify(int restnumber) { // make new heap with the outside numbers of the heap
		int temp = restnumber;
		for (int i = arr_size - restnumber; i >= 1; --i) {
			swap(i, temp);
			temp++;
		}
		heap_size = arr_size - restnumber;
	}

	void MinHeap::heapsizereturn() { // reset heapsize
		this->heap_size = this->arr_size;
	}
