#include <iostream>
#include "Sort.h"

using namespace std;

bool check_quick(QuickSort *quick_sort) {
	// check the result of quick sort algorithm
	for (int i = 0; i < quick_sort->size - 1; i++) {
		if (quick_sort->arr[i] > quick_sort->arr[i + 1]) {
			return false;
		}
	}
	return true;
}

bool check_merge(MergeSort *merge_sort) {
	// check the result of merge sort algorithm
	for (int i = 0; i < merge_sort->size - 1; i++) {
		if (merge_sort->arr[i] > merge_sort->arr[i + 1]) {
			return false;
		}
	}
	return true;
}

bool check_insertion(InsertionSort *insertion_sort) {
	// check the result of insertion sort algorithm
	for (int i = 0; i < insertion_sort->size - 1; i++) {
		if (insertion_sort->arr[i] > insertion_sort->arr[i + 1]) {
			return false;
		}
	}
	return true;
}

bool check_stooge(StoogeSort *stooge_sort) {
	// check the result of insertion sort algorithm
	for (int i = 0; i < stooge_sort->size - 1; i++) {
		if (stooge_sort->arr[i] > stooge_sort->arr[i + 1]) {
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	double *input_array;
	int n;
	cin >> n;

	// implement here
	// generate random numbers and apply each sorting algorithms
	srand(0);
	input_array = new double[n];
	for (int i = 0; i < n; i++) {
		input_array[i] = (double)(rand());
	}



	// QuickSort
	QuickSort *quick_sort = new QuickSort();
	// implement here
	quick_sort->set(input_array, n);
	quick_sort->run();
	quick_sort->print_time();

	if (check_quick(quick_sort)) {
		cout << "QuickSort is validated" << endl << endl;
	}
	delete quick_sort;


	// MergeSort
	MergeSort *merge_sort = new MergeSort();
	// implement here
	merge_sort->set(input_array, n);
	merge_sort->run();
	merge_sort->print_time();


	if (check_merge(merge_sort)) {
		cout << "MergeSort is validated" << endl << endl;
	}
	delete merge_sort;


	// InsertionSort
	InsertionSort *insertion_sort = new InsertionSort();
	// implement here
	insertion_sort->set(input_array, n);
	insertion_sort->run();
	insertion_sort->print_time();

	if (check_insertion(insertion_sort)) {
		cout << "InsertionSort is validated" << endl << endl;
	}
	delete insertion_sort;

	// StoogeSort
	StoogeSort *stooge_sort = new StoogeSort();
	// implement here
	stooge_sort->set(input_array, n);
	stooge_sort->run();
	stooge_sort->print_time();

	if (check_stooge(stooge_sort)) {
		cout << "StoogeSort is validated" << endl;
	}
	delete stooge_sort;

	system("pause");

	return 0;
}