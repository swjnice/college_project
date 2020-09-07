#include "read_buffer.h"

#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::ios;



ReadBuffer::ReadBuffer(int capacity, string filename) {
	buffer = new int[capacity]; // allocate the buffer array
	this->capacity = capacity;
	curr_pos = 0;
	IFS.open(filename, ios::binary); //Open input file
	IFS.read((char*)buffer, sizeof(int)* capacity); // buffer get input data
};
	
ReadBuffer::~ReadBuffer() {
	delete[] buffer; //release the buffer
	IFS.close();	//close input file
};


bool ReadBuffer::read(int &x) { //read one integer from the buffer
	if (curr_pos == capacity) { //if buffer is all read open new input file
		if (!IFS.read((char*)buffer, sizeof(int)*capacity)) { //if all input files are read return false
			return false;
		}
		curr_pos = 0; // set current position to 0 to read new input file
	}
	x = buffer[curr_pos];
	curr_pos++;
	return true;
}; 
