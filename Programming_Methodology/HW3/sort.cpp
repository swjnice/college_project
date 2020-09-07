#include "sort.h"

void sort(int arr[], int len) {
	QuickSort(arr, 0, len - 1);
	return;
};

void QuickSort(int arr[], int start, int finish) { // QuickSort arr[start] to arr[finish]
	if (start < finish) {
		int q = partition(arr, start, finish);
		QuickSort(arr, start, q-1); //quicksort start to pivot
		QuickSort(arr, q + 1, finish); // quickosrt pivot + 1 to finish
	}
	return;
}

int partition(int arr[], int p, int r) {
	int pivot = arr[r];
	int i = p - 1;
	for (int j = p; j < r; j++) { //the number smaller than pivot is filled arr[start] to arr[i]
		if (arr[j] <= pivot) {
			i++;
			int temp = arr[j];  //exchangge arr[i] and arr[j]
			arr[j] = arr[i];
			arr[i] = temp;
		}
	}
	int temp2 = pivot;		//exchange arr[i+1] and arr[pivot]. so the position of the pivot is arr[i+1]
	arr[r] = arr[i + 1];
	arr[i + 1] = temp2;
	return i + 1;	
}