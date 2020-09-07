#include "run_ext_sort.h"

#include "ext_merge_sort.h"
#include "misc.h"

void run_ext_sort(int data_size, int page_size, int num_pages) {
	int* initialfile = new int[1];
	ExtMergeSort ext_merge_sort(data_size, page_size, num_pages, initialfile);
	ext_merge_sort.main();
}


