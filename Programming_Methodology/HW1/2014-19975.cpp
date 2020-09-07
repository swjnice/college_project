#include <iostream>
#include <ctime> // time
#include <cstdlib> // srand, rand
#include <climits> // INT_MAX

using std::cout;
using std::endl;

void gen_data(int n_data, int size, int **data);
void print_elpased_time(clock_t start_time);

void run_insertion_sort(int size, int *arr);
void run_merge_sort(int size, int *arr);
void merge_sort(int* A, int p, int r);
void merge(int*A, int p, int q, int r);
void run_quick_sort(int size, int *arr);
void quick_sort(int* A, int p, int r);
int partition(int*A, int p, int r);
void run_stooge_sort(int size, int *arr);
void stooge_sort(int* A, int q, int r);
void compare_results(int size, int *arr1, int *arr2);

int main() {
	const int n_sort = 4; // insertion sort, merge sort, quicksort, stooge sort

	int size = 20;

	// Allocate memory for the 2-D array with a size of (n_sort, size)
	int **data = new int*[n_sort];
	for (int i = 0; i < n_sort; i++)
		data[i] = new int[size];

	// Generate random numbers
	// Each 1-D array with a size of "size" should be same

	gen_data(n_sort, size, data);

	run_quick_sort(size, data[0]);


	run_merge_sort(size, data[1]);
	compare_results(size, data[1], data[0]); // compare the two sorted results

	run_insertion_sort(size, data[2]);
	compare_results(size, data[2], data[0]);

	run_stooge_sort(size, data[3]);
	compare_results(size, data[3], data[0]);


	// release the memory
	for (int i = 0; i < n_sort; i++) {
	delete[] data[i];
	delete[] data;
}

	return 0;
}

void gen_data(int n_data, int size, int **data) {
	// Implement here
	srand(time(0));

	for (int k = 0; k < size; k++) {
		data[0][k] = rand();
		data[1][k] = data[2][k] = data[3][k] = data[0][k];
	}
	

	cout << "A part of the initial data:" << endl << "  ";
	for (int i = 0; i < size && i < 10; i++)
		cout << data[0][i] << " ";
	cout << endl;
}

void compare_results(int size, int *arr1, int *arr2) {
	bool is_same = true;
	for (int i = 0; i < size; i++)
		if (arr1[i] != arr2[i]) {
			cout << "not same" << endl;
			is_same = false;
			break;
		}
	if (is_same == true)
		cout << "same" << endl;
}

void print_elpased_time(clock_t start_time) {
	clock_t end_time = clock();
	cout << "Time : " << (float)(end_time - start_time) / CLOCKS_PER_SEC << "sec" << endl;
}

void run_insertion_sort(int size, int *arr) {
	cout << endl << "insertion sort" << endl;
	clock_t start_time = clock();

	// Implement here
	for (int i = 1; i < size; i++) {
		int key = arr[i];
		while (i > 0 && arr[i - 1] > key) {
			arr[i] = arr[i - 1];
			i = i - 1;
		}
		arr[i] = key;
	}

	print_elpased_time(start_time);
}

void run_merge_sort(int size, int *arr) {
	cout << endl << "merge sort" << endl;
	clock_t start_time = clock();

	// Implement here
	merge_sort(arr, 0, size - 1);

	print_elpased_time(start_time);
}

void merge(int*A, int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	int* L = new int[n1 + 1];
	int* R = new int[n2 + 1];
	for (int i = 0; i < n1; i++) {
		L[i] = A[p + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = A[q + j + 1];
	}
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;

	int i  = 0;
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

void merge_sort(int* A, int p, int r) {
	if (p < r) {
		int q = floor((p + r) / 2);
		merge_sort(A, p, q);
		merge_sort(A, q+1, r);
		merge(A, p, q, r);
	}
}

void run_quick_sort(int size, int *arr) {
	cout << endl << "quick sort" << endl;
	clock_t start_time = clock();

	// Implement here
	quick_sort(arr, 0, size - 1);

	print_elpased_time(start_time);
}

void quick_sort(int* A, int p, int r) {
	if (p < r) {
		int q = partition(A, p, r);
		quick_sort(A, p, q - 1);
		quick_sort(A, q + 1, r);
	}
}

int partition(int* A, int p, int r) {
	int x = A[r];
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (A[j] <= x) {
			i = i + 1;
			int temp = A[j];
			A[j] = A[i];
			A[i] = temp;
		}
	}
	int temp2 = A[r];
	A[r] = A[i+1];
	A[i + 1] = temp2;
	return i + 1;
}

void run_stooge_sort(int size, int *arr) {
	cout << endl << "stooge sort" << endl;
	clock_t start_time = clock();

	// Implement here
	stooge_sort(arr, 0, size - 1);

	print_elpased_time(start_time);
}

void stooge_sort(int* A, int s, int e) {
	if (s >= e) {
		return;
	}
	else if (e - s == 1) {
		if (A[s] > A[e]) {
			int temp = A[e];
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

