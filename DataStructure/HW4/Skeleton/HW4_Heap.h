#ifndef HW4_HEAP_H
#define HW4_HEAP_H

#include "HW4_Edge.h"
#include "HW4_Node.h"

template <class T>
void swapPos(T* arr, int* pos, int a, int b) {
	if (a != b) {
		pos[arr[a].getIdx()] = b;
		pos[arr[b].getIdx()] = a;
	}
}

template <class T>
void swap(T* arr, int a, int b) {
	T temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

template <class T>
void maxHeapify(T* arr, int* pos, int size_heap, int idx)
{
	int maximum = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < size_heap && arr[left] > arr[maximum])
		maximum = left;

	if (right < size_heap && arr[right] > arr[maximum])
		maximum = right;

	if (maximum != idx)
	{
		swapPos(arr, pos, idx, maximum);
		swap(arr, idx, maximum);
		maxHeapify(arr, pos, size_heap, maximum);
	}
}

template <class T>
void heapSort(T* arr, int* pos, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		maxHeapify(arr, pos, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swapPos(arr, pos, 0, i);
		swap(arr, 0, i);
		maxHeapify(arr, pos, i, 0);
	}

}

#endif