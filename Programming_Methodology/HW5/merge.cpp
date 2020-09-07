#include "merge.h"
#include "read_buffer.h"
#include "output_buffer.h"
#include <climits>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

using std::stringstream;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using namespace std;

using std::string;

bool check_intMax(int* number, int numbersize) { // check if all number array element is INT_MAX
	for (int i = 0; i < numbersize; i++) {
		if (number[i] != INT_MAX) {
			return false;
		}
	}
	return true;
}

int Minnumpos(int* number, int numbersize) { // find the smallest number position between number array
	int min = *number;
	int position = 0;
	for (int i = 0; i < numbersize; i++) {
		if (min > number[i]) {
			min = number[i];
			position = i;
		}
	}
	return position;
}

void merge(int page_size, int nRun, int numbermerge, int** filesize, string* in_file_path,
	string out_file_path, string debug_out_file_path) {
	
	int* number = new int[numbermerge]; // number that readbuf of number of buffer
	bool* read = new bool[numbermerge];// check whether number are read of each buffer


	ReadBuffer* readbuf = new ReadBuffer[numbermerge]; // make new readbuffers
	for (int i = 0; i < numbermerge; i++) {
		readbuf[i].set(page_size, in_file_path[i], filesize[nRun][i]);
		read[i] = readbuf[i].read(number[i]);
	}
	OutputBuffer outputbuf(page_size, out_file_path, debug_out_file_path); // make outputfile


	// from now merge input files by comparing numbers
	// if read all numbers of file, make number INT_MAX to check
	while (!check_intMax(number, numbermerge)) {
		int mnp = Minnumpos(number, numbermerge);
		outputbuf.add(number[mnp]);
		read[mnp] = readbuf[mnp].read(number[mnp]);
		if (!read[mnp]) {
			number[mnp] = INT_MAX;
		}
	}
	outputbuf.finish();
};

void mergefiles(int nRun, int& j, int& c, int numbermerge, int page_size, int** filesize) { // function to merge files 
	if (numbermerge == 0) {
		return;
	}
	
	stringstream ss_out, ss_out_debug; // make output file path
	ss_out << "output_binary/temp_" << (nRun + 1) << "_" << (c);
	ss_out_debug << "output_debug/temp_" << (nRun + 1) << "_" << (c++);

	string* in_file_path = new string[numbermerge]; // input file path
	for (int k = 0; k < numbermerge; k++) {
		stringstream ss_read;
		ss_read << "output_binary/temp_" << nRun << "_" << (j++);
		in_file_path[k] = ss_read.str();
	}

	string out_file_path = ss_out.str();
	string debug_out_file_path = ss_out_debug.str();


	merge(page_size, nRun, numbermerge, filesize, in_file_path , //merge function
		out_file_path, debug_out_file_path);

};
