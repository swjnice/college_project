#include "merge.h"
#include "read_buffer.h"
#include "output_buffer.h"
#include <climits>

#include <string>

using std::string;

void merge(int page_size, string in_file_path1, string in_file_path2,
	string out_file_path, string debug_out_file_path) {
	
	int number1, number2; // number that readbuf 1, 2 read
	bool read1, read2;		  // check whether number are read

	ReadBuffer readbuf1(page_size, in_file_path1); //read file_path1
	ReadBuffer readbuf2(page_size, in_file_path2); //read file_path2
	OutputBuffer outputbuf(page_size, out_file_path, debug_out_file_path); // make outputfile

	read1 = readbuf1.read(number1); 
	read2 = readbuf2.read(number2);

	// from now merge two input files by comparing numbers
	// if read all numbers of file, make number INT_MAX to check
	while (number1 != INT_MAX || number2 != INT_MAX) {
		if (number1 <= number2) {
			outputbuf.add(number1);
			read1 = readbuf1.read(number1);
		}
		else {
			outputbuf.add(number2);
			read2 = readbuf2.read(number2);
		}
		if (!read1) {
			number1 = INT_MAX;
		}
		if (!read2) {
			number2 = INT_MAX;
		}
	}
};
