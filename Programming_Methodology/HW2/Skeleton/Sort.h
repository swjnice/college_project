#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <ctime>

using namespace std;

class QuickSort {
public:
	void print_time() const {
		cout << "QuickSort : " << seconds << " sec" << endl;
	}



	// implement the following functions
	QuickSort() {
		// constructor
	}

	~QuickSort() {
		// destructor
	}

	void run() {
		// sorting algorithm is applied
		// elapsed time is also recorded in seconds

	}


	void set(double *arr, int size) {
		// new input array and its size are set

	}

private:
	double *arr;
	int size;
	time_t seconds;
};

class MergeSort {
public:
	void print_time() const {
		cout << "MergeSort : " << seconds << " sec" << endl;
	}

	// implement the following functions
	MergeSort() {
		// constructor
	}

	~MergeSort() {
		// destructor
	}

	void run() {
		// sorting algorithm is applied
		// elapsed time is also recorded in seconds

	}


	void set(double *arr, int size) {
		// new input array and its size are set

	}

private:
	double *arr;
	int size;
	time_t seconds;

};

class InsertionSort {
public:
	void print_time() const {
		cout << "InsertionSort : " << seconds << " sec" << endl;
	}

	// implement the following functions
	InsertionSort() {
		// constructor
	}

	~InsertionSort() {
		// destructor
	}

	void run() {
		// sorting algorithm is applied
		// elapsed time is also recorded in seconds

	}


	void set(double *arr, int size) {
		// new input array and its size are set

	}

private:
	double *arr;
	int size;
	time_t seconds;
};

class StoogeSort {
public:
	void print_time() const {
		cout << "StoogeSort : " << seconds << " sec" << endl;
	}

	// implement the following functions
	StoogeSort() {
		// constructor
	}

	~StoogeSort() {
		// destructor

	}

	void run() {
		// sorting algorithm is applied
		// elapsed time is also recorded are seconds

	}


	void set(double *arr, int size) {
		// new input array and its size are set
		
	}


private:
	double *arr;
	int size;
	time_t seconds;
};


#endif