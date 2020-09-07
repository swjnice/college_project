#include "ext_merge_sort.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

#include "misc.h"
#include "merge.h"
#include "heap.h"
#include "read_buffer.h"
#include "output_buffer.h"

using std::stringstream;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using namespace std;

ExtMergeSort::ExtMergeSort(int data_size, int page_size, int num_pages, int* initialfilesize) :
		page_size(page_size), data_size(data_size), num_pages(num_pages), initial_buffer_size(page_size * (num_pages-2)), num_of_initial_files(0), initialfilesize(initialfilesize) {
}


void ExtMergeSort::main() {
	initial_pass();

	int nRun = 0;

	if (num_of_initial_files == 1) {
		return;
	}


	int mergerun = 0;
	for (int j = num_of_initial_files; j > 1; j = (j + num_pages - 2) / (num_pages - 1)) {
		mergerun++;
	}
	// mergerun is the number of mergerun

	int** filesize = new int*[mergerun+1];// filesize[nRun][k] = the number of data of 'temp_nRUn_k' file

	mergerun = 0; // make the array of the filesize of each run
	for (int j = num_of_initial_files; j > 1; j = (j + num_pages - 2) / (num_pages - 1)) {
		filesize[mergerun] = new int[j];
		mergerun++;
	}

	filesize[mergerun] = new int[1];

	for (int i = 0; i < num_of_initial_files; i++) { // get initial file number into filesize[0]
		filesize[0][i] = initialfilesize[i];
	}

	mergerun = 1; // calculate the filesize
	for (int j = num_of_initial_files; j > 1; j = (j + num_pages - 2) / (num_pages - 1)) {

		int suminputfile = 0;
		int rest = j%(num_pages-1);
		for (int k = 0; k < j/(num_pages-1); k++) {
			suminputfile = 0;
			for (int g = 0; g < num_pages - 1; g++) {
				suminputfile = suminputfile + filesize[mergerun - 1][g+k*(num_pages-1)];
			}
			filesize[mergerun][k] = suminputfile;
		}
		suminputfile = 0;
		if (rest != 0) {
			for (int g = 1; g <= rest; g++) {
				suminputfile = suminputfile + filesize[mergerun - 1][j - g];
			}
			filesize[mergerun][j / (num_pages - 1)] = suminputfile;
		}
		mergerun++;
	}
	
	*filesize[mergerun-1] = data_size; // the last outputfile size is same with data_size
	



	for (int i = num_of_initial_files; i > 1; i = (i+num_pages-2)/(num_pages-1) ) {
		// i: the number of input files to process
		int j = 0; // input file index
		int c = 0; // output file index
		while (j < i/(num_pages-1)) {
			mergefiles(nRun, j, c, num_pages - 1, page_size, filesize);
		}

		int restfile = i % (num_pages - 1);
		if (i != 0) {
			mergefiles(nRun, j, c, restfile, page_size, filesize);
		}
		++nRun;
	}

}

int ExtMergeSort::get_initial_buffer_size() {
	return initial_buffer_size;
}

void ExtMergeSort::initial_pass() {
	//ifstream IFS("input.bin", ios::binary); //open input file
	//if (!IFS.is_open()) {
	//	cout << "failed to open input file" << endl;
	//	mad();
	//}	
	
	vector<int> filesize_0;
	int* buf = new int[page_size*(num_pages - 2)]; //make array for heapbuffer

	int fileID = 0;
	
	bool datasmall = false; // when initial buffer size is bigger than data size

	ReadBuffer readbuf(page_size, "input.bin", data_size); //make readbuffer
	MinHeap heapbuf(buf, initial_buffer_size); //make heapbuffer
	
	if (data_size < initial_buffer_size) { // if initial buffer size > data size
		datasmall = true;
		heapbuf.setsize(data_size);
	}

	for (int i = 0; i < initial_buffer_size; ++i) { // fill heapbuffer
		readbuf.read(*(buf + i));
	}
	heapbuf.build_minheap(); //build minheap in heapbuffer


	while (1) {

		stringstream ss_filename; //define outputfile name
		ss_filename << "temp_0_" << fileID;
		stringstream ss; // output binary filename
		ss << "output_binary/" << ss_filename.str();
		stringstream ss_debug;// output debug filename
		ss_debug << "output_debug/" << ss_filename.str();

		OutputBuffer outbuf(page_size, ss.str(), ss_debug.str()); // make outbuffer

		heapbuf.build_minheap();

		outbuf.add(*buf);

		int written = *buf; // memorize the wriitten number just before

		while (readbuf.read(*buf)) { //by comparing now top of minheap with written number decide min_heapify(1) or min_heapify2()
			if (heapbuf.getheapsize() <= 2) {
				if (heapbuf.getheapsize() <= 1) {
					if (written > *buf) { // when heapsize is 1 and smaller number is read stop reading and make one output file
						outbuf.finish();
						++fileID;
						filesize_0.push_back(outbuf.getfilesize()); //memorize the size of the file
						heapbuf.heapsizereturn(); //reset heapsize to make next output
						break;
					}
				}
				else {
					if (*buf < written) {
						heapbuf.min_heapify2();
					}
					else {
						heapbuf.min_heapify(1);
					}
				}
			}
			else {
				if (*buf < written) {
					heapbuf.min_heapify2();
				}
				else {
					heapbuf.min_heapify(1);
				}
			}
			outbuf.add(*buf);
			written = *buf;
		}

		if (datasmall) {
			break;
		}

		if (readbuf.checkallread()) { // if input file is all read
			int curheapsize = heapbuf.getheapsize(); // give all rest number in the minheap to current outputfile
				for (int i = 1; i < curheapsize; i++) {
					heapbuf.min_heapify2();
					outbuf.add(*buf);
				}
				outbuf.finish();
				++fileID;
				filesize_0.push_back(outbuf.getfilesize());


				heapbuf.restheapify(curheapsize); // make last ouput for numbers outside the minheap

				stringstream ss_filename;
				ss_filename << "temp_0_" << fileID;
				stringstream ss;
				ss << "output_binary/" << ss_filename.str();
				stringstream ss_debug;
				ss_debug << "output_debug/" << ss_filename.str();

				OutputBuffer outbuf(page_size, ss.str(), ss_debug.str());

				for (int j = 0; j < initial_buffer_size - curheapsize; j++) {
					outbuf.add(*buf);
					heapbuf.min_heapify2();
				}
				outbuf.finish();
				++fileID;
				filesize_0.push_back(outbuf.getfilesize());
				break;
			
		}
	}
	
	delete[] buf;
	num_of_initial_files = fileID;
	initialfilesize = new int[num_of_initial_files];
	for (int i = 0; i < num_of_initial_files; i++) {
		initialfilesize[i] = filesize_0[i];
	}
}
