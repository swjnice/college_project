/*
 * 3 buffer pages
 */

#include <iostream>
using namespace std;

#include "run_ext_sort.h"
#include "misc.h"

int main() {
	int data_size;
	int page_size;
	int num_pages;

	cout << "data_size : ";
	cin >> data_size;
	cout << "page_size : ";
	cin >> page_size;
	cout << "num_pages : ";
	cin >> num_pages;
	
	gen_data("input.bin", data_size);
	run_ext_sort(data_size, page_size, num_pages); // implement this
	std::cout << "Finished" << std::endl;
	return 0;
}

