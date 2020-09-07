#pragma once

class ExtMergeSort {
public:
	ExtMergeSort(int data_size, int page_size, int num_pages,int* initialfilesize);
	int get_initial_buffer_size(); // 3 * page_size
	void main();
private:
	int data_size;
	int num_pages;
	int page_size;
	int initial_buffer_size; // 3 * page_size
	int num_of_initial_files; // the number of output files of the initial pass
	void initial_pass();
	int* initialfilesize;
};
