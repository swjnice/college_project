#include "read_buffer.h"

#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::ios;



ReadBuffer::ReadBuffer(int capacity, string filename, int filesize) {
	buffer = new int[capacity]; // allocate the buffer array
	this->capacity = capacity;
	curr_pos = 0;
	readsize = 0;
	this->filesize = filesize;
	IFS.open(filename, ios::binary); //Open input file
	if (filesize >= capacity) {
		IFS.read((char*)buffer, sizeof(int)* capacity); // buffer get input data
	}
	else {
		this->capacity = filesize;
		IFS.read((char*)buffer, sizeof(int)* capacity);
	}
	allread = false; // if all input number is read
};

ReadBuffer::ReadBuffer() {
	curr_pos = 0;
	readsize = 0;
	allread = false;
};

void ReadBuffer::set(int capacity, string filename, int filesize) {
	buffer = new int[capacity];
	this->capacity = capacity;
	this->filesize = filesize;
	IFS.open(filename, ios::binary);
	IFS.read((char*)buffer, sizeof(int)* capacity);
}
	
ReadBuffer::~ReadBuffer() {
	delete[] buffer; //release the buffer
	IFS.close();	//close input file
};


bool ReadBuffer::read(int &x) { //read one integer from the buffer
	if (readsize == filesize) {
		allread = true;
		return false;
	}
	if (curr_pos == capacity) { //if buffer is all read open new input file
		if (filesize - readsize <= capacity) { //if rest of input is less than buffer size
			IFS.read((char*)buffer, sizeof(int)*(filesize - readsize));
			capacity = filesize - readsize;
		}
		else {
			IFS.read((char*)buffer, sizeof(int)*capacity);
		}
		curr_pos = 0; // set current position to 0 to read new input file
	}
	x = buffer[curr_pos];
	curr_pos++;
	readsize++;
	return true;
};

int ReadBuffer::getreadsize() {
	return this->readsize;
}

bool ReadBuffer::checkallread() {
	return this->allread;
}