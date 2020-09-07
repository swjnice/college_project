#pragma once
#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <ctime>

using namespace std;

class QuickSort {
public:
	friend bool check_quick(QuickSort* quick_sort);
	clock_t checktime1;
	clock_t checktime2;
	int timelimit;



	void print_time() const {
		cout << "QuickSort : " << seconds << " sec" << endl;
	}




	/*
	constructor
	size = 10
	array = {1,2,3,4,5,6,7,8,9,10}
	*/
	QuickSort() {

		this->size = 10;
		arr = new double[10];
		for (int i = 0; i < 10; i++) {
			*(arr + i) = i + 1;
		}
		seconds = 0;
	}

	//destructor
	~QuickSort() {
		delete[] arr;
	}

	void run() {
		/*
		Function Description : quick_sorting and elapsed time is also recorded in seconds
		*/
		clock_t start_time = (double)clock();
		checktime1 = start_time;
		quick_sort(arr, 0, size - 1);
		if (timelimit==1) {
			cout << "Teminated due to the time limit" << endl;
		}
		clock_t end_time = (double)clock();
		this->seconds = (end_time - start_time) / (double)CLOCKS_PER_SEC;

	}

	/*
	Input : double_type array, int p, int r
	Output : quick_sorted array in range p to r
	Function Description : sorting like --->>>> numbergroup1(<pivot), pivot, numbergroup2(>pivots)
	and quicksort numbergroup1, numbergroup2 recursively, In every recursion check time and if it goes over 10 seconds stop sorting.
	*/
	void quick_sort(double* A, int p, int r) {
		if (timelimit==1) {
			return;
		}
		
		checktime2 = clock();
		if (((double)(checktime2 - checktime1) / (double)CLOCKS_PER_SEC) >= 10) {
			timelimit = 1;
			return;
		}

		if (p < r) {
			int q = partition(A, p, r);
			quick_sort(A, p, q - 1);
			quick_sort(A, q + 1, r);
		}
	}

	/*
	Input : double_type array, int p, int r
	Output : int_type = position of pivot
	Function Description : comparing with pivot, move smaller numbers forward and larger numbers backward, insert pivot in the right place and return position
	*/
	int partition(double* A, int p, int r) {
		if (timelimit == 1) {
			return 0;
		}

		double x = A[r];
		int i = p - 1;
		for (int j = p; j < r; j++) {
			if (A[j] <= x) {
				i = i + 1;
				double temp = A[j];
				A[j] = A[i];
				A[i] = temp;
			}
		}
		double temp2 = A[r];
		A[r] = A[i + 1];
		A[i + 1] = temp2;
		return i + 1;
	}


	//get input_array and size , deep_copy input_array
	void set(double *arr, int size) {
		delete[] this->arr;
		this->size = size;
		this->arr = new double[size];
		for (int k = 0; k < size; k++) {
			this->arr[k] = arr[k];
		}
	}

private:
	double *arr;
	int size;
	double seconds;
};

class MergeSort {
public:
	friend bool check_merge(MergeSort* merge_sort);
	clock_t checktime1;
	clock_t checktime2;
	int timelimit;

	void print_time() const {
		cout << "MergeSort : " << seconds << " sec" << endl;
	}

	/*
	constructor
	size = 10
	array = {1,2,3,4,5,6,7,8,9,10}
	*/
	MergeSort() {
		this->size = 10;
		arr = new double[10];
		for (int i = 0; i < 10; i++) {
			*(arr + i) = i + 1;
		}
		seconds = 0;
	}

	// destructor
	~MergeSort() {
		delete[] arr;
	}


	/*
	Function Description : merge_sorting and elapsed time is also recorded in seconds
	*/
	void run() {
		clock_t start_time = clock();
		checktime1 = start_time;
		merge_sort(arr, 0, size - 1);
		if (timelimit == 1) {
				cout << "Teminated due to the time limit" << endl;
		}
		clock_t end_time = clock();
		this->seconds = (float)(end_time - start_time) / CLOCKS_PER_SEC;
	}

	/*
	Input : double_typed_array, int p,q,r
	Output : merged_double_typed_array
	Function Description : numbers p to q are sorted, q+1 to r are sorted make these numbers two group
							and comparing from forward, make one sorted array and delete used memory
	*/
	void merge(double*A, int p, int q, int r) {
		if (timelimit == 1) {
			return;
		}

		int n1 = q - p + 1;
		int n2 = r - q;
		double* L = new double[n1 + 1];
		double* R = new double[n2 + 1];
		for (int i = 0; i < n1; i++) {
			L[i] = A[p + i];
		}
		for (int j = 0; j < n2; j++) {
			R[j] = A[q + j + 1];
		}
		L[n1] = INT_MAX;
		R[n2] = INT_MAX;

		int i = 0;
		int j = 0;

		int k = p;
		for (k; k <= r; k++) {
			if (L[i] <= R[j]) {
				A[k] = L[i];
				i++;
			}
			else {
				A[k] = R[j];
				j++;
			}
		}
		delete[] L;
		delete[] R;
	}

	/*
	Input : double_typed_array, int p,r
	Output : merge_sorted array
	Function Description : divide array into two array by center.
							do merge_sort each group recursively and merge two array. In every recursion check time and if it goes over 10 seconds stop sorting.
	*/
	void merge_sort(double* A, int p, int r) {
		if (timelimit == 1) {
			return;
		}
		checktime2 = clock();
		if (((double)(checktime2 - checktime1) / (double)CLOCKS_PER_SEC) >= 10) {
			timelimit = 1;
			return;
		}
		if (p < r) {
			int q = floor((p + r) / 2);
			merge_sort(A, p, q);
			merge_sort(A, q + 1, r);
			merge(A, p, q, r);
		}
	}

	//get input_array and size , deep_copy input_array
	void set(double *arr, int size) {
		delete[] this->arr;
		this->size = size;
		this->arr = new double[size];
		for (int k = 0; k < size; k++) {
			this->arr[k] = arr[k];
		}
	}

private:
	double *arr;
	int size;
	double seconds;

};

class InsertionSort {
public:
	friend bool check_insertion(InsertionSort* insertion_sort);
	clock_t checktime1;
	clock_t checktime2;
	int timelimit;

	void print_time() const {
		cout << "InsertionSort : " << seconds << " sec" << endl;
	}

	/*
	constructor
	size = 10
	array = {1,2,3,4,5,6,7,8,9,10}
	*/
	InsertionSort() {
		this->size = 10;
		arr = new double[10];
		for (int i = 0; i < 10; i++) {
			*(arr + i) = i + 1;
		}
		seconds = 0;
	}

	//destructor
	~InsertionSort() {
		delete[] arr;
	}

	/*
	Function Description :insertion_sorting and elapsed time is also recorded in seconds
	insertion sorting : (Sorting this class' array) From first number. find the right place of every number by comparing number while going left side and insert it.
						During 'for' loop, if checktime go over 10 sec stop sorting. 
	*/
	void run() {
		clock_t start_time = clock();
		checktime1 = start_time;

		for (int i = 1; i < size; i++) {
			checktime2 = clock();
			if (((double)(checktime2 - checktime1) / (double)CLOCKS_PER_SEC) >= 10) {
				timelimit = 1;
				cout << "Teminated due to the time limit" << endl;
				return;
			}
			double key = arr[i];
			while (i > 0 && arr[i - 1] > key) {
				arr[i] = arr[i - 1];
				i = i - 1;
			}
			arr[i] = key;
		}
		clock_t end_time = clock();
		this->seconds = (float)(end_time - start_time) / CLOCKS_PER_SEC;

	}

	//get input_array and size , deep_copy input_array
	void set(double *arr, int size) {
		delete[] this->arr;
		this->size = size;
		this->arr = new double[size];
		for (int k = 0; k < size; k++) {
			this->arr[k] = arr[k];
		}
	}

private:
	double *arr;
	int size;
	double seconds;
};

class StoogeSort {
public:
	friend bool check_stooge(StoogeSort* stooge_sort);
	clock_t checktime1;
	clock_t checktime2;
	int timelimit;

	void print_time() const {
		cout << "StoogeSort : " << seconds << " sec" << endl;
	}

	/*
	constructor
	size = 10
	array = {1,2,3,4,5,6,7,8,9,10}
	*/
	StoogeSort() {
		this->size = 10;
		arr = new double[10];
		for (int i = 0; i < 10; i++) {
			*(arr + i) = i + 1;
		}
		seconds = 0;
	}

	//destructor
	~StoogeSort() {
		delete[] arr;
	}

	/*
	Function Description : stooge_sorting and elapsed time is also recorded in seconds (if elapsed time is over 10 seconds, show that it is terminated.)
	*/
	void run() {
		clock_t start_time = (double)clock();
		checktime1 = start_time;
		stooge_sort(arr, 0, size - 1);
		clock_t end_time = (double)clock();
		this->seconds = (double)(end_time - start_time) / (double)CLOCKS_PER_SEC;
		if (timelimit > 0) {
			cout << "Terminated due to the time limit" << endl;
		}
	}

	/*
	Input : double_typed_array , int s,e
	Output : stooge_sorted array, or terminated(timeover)
	Function Description : get array divided in three parts. then stooge_sort (1th,2nd)->(2nd,3rd)->(1st,2nd) recursively
							doing timecheck in every recursion and if time is over 10 second, get timelimit = 1 (meaning timeover) and stop recursion and return
	*/
	void stooge_sort(double* A, int s, int e) {
		if (timelimit > 0) {
			return;
		}

		checktime2 = clock();
		if (((double)(checktime2 - checktime1) / (double)CLOCKS_PER_SEC) >= 10 ){
			timelimit = 1;
				return;
		}
		if (s >= e) {
			return;
		}
		else if (e - s == 1) {
			if (A[s] > A[e]) {
				double temp = A[e];
					A[e] = A[s];
					A[s] = temp;
			}
		}
		else {
			int d = (e - s + 1) / 3;
			stooge_sort(A, s, e - d);
			stooge_sort(A, s + d, e);
			stooge_sort(A, s, e - d);
		}
	}

	//get input_array and size , deep_copy input_array
	void set(double *arr, int size) {
		delete[] this->arr;
		this->size = size;
		this->arr = new double[size];
		for (int k = 0; k < size; k++) {
			this->arr[k] = arr[k];
		}
	}


private:
	double *arr;
	int size;
	double seconds;
};


#endif