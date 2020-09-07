#include <iostream>
#include "Sort.h"

using namespace std;

bool check_quick(QuickSort *quick_sort) {
	// check the result of quick sort algorithm

}
bool check_merge(MergeSort *merge_sort) {
	// check the result of merge sort algorithm

}

bool check_insertion(InsertionSort *insertion_sort) {
	// check the result of insertion sort algorithm

}

bool check_stooge(StoogeSort *stooge_sort) {
	// check the result of insertion sort algorithm

}

int main(int argc, char *argv[]) {
	double *input_array;
	int n;
	cin >> n;

	// implement here
	// generate random numbers and apply each sorting algorithms



	// QuickSort
	QuickSort *quick_sort = new QuickSort();
		// implement here



	if (check_quick(quick_sort)) {
		cout << "QuickSort is validated" << endl << endl;
	}
	delete quick_sort;

	
	// MergeSort
	MergeSort *merge_sort = new MergeSort();
		// implement here



	if (check_merge(merge_sort)) {
		cout << "MergeSort is validated" << endl << endl;
	}
	delete merge_sort;

	
	// InsertionSort
	InsertionSort *insertion_sort = new InsertionSort();
		// implement here


	if ( check_insertion(insertion_sort) ) {
		cout << "InsertionSort is validated" << endl << endl;
	}
	delete insertion_sort;

	// StoogeSort
	StoogeSort *stooge_sort = new StoogeSort();
		// implement here

	if ( check_stooge(stooge_sort) ) {
		cout << "StoogeSort is validated" << endl;
	}
	delete stooge_sort;

	return 0;
}