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
void run_quick_sort(int size, int *arr);
void run_stooge_sort(int size, int *arr);

void compare_results(int size, int *arr1, int *arr2);

int main() {
	const int n_sort = 4; // insertion sort, merge sort, quicksort, stooge sort

	int size = 10;

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
	for (int i = 0; i < n_sort; i++)
		delete[] data[i];
	delete[] data;

	return 0;
}

void gen_data(int n_data, int size, int **data) {
	// Implement here

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

	print_elpased_time(start_time);
}

void run_merge_sort(int size, int *arr) {
	cout << endl << "merge sort" << endl;
	clock_t start_time = clock();

	// Implement here

	print_elpased_time(start_time);
}

void run_quick_sort(int size, int *arr) {
	cout << endl << "quick sort" << endl;
	clock_t start_time = clock();

	// Implement here

	print_elpased_time(start_time);
}

void run_stooge_sort(int size, int *arr) {
	cout << endl << "stooge sort" << endl;
	clock_t start_time = clock();

	// Implement here

	print_elpased_time(start_time);
}

