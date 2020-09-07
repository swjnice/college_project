#include "output_buffer.h"

#include <string>
#include <fstream>

#include "misc.h"

using std::string;
using std::ofstream;
using std::ios;
using std::endl;




OutputBuffer::OutputBuffer(int capacity, string file_path, string debug_file_path) {
	this->capacity = capacity;
	current_size = 0;
	filesize = 0;
	buffer = new int[capacity];				//allocate the buffer
	OFS.open(file_path, ios::binary);	//open OFS
	OFS_debug.open(debug_file_path);	//open OFS_debug
	};


OutputBuffer::~OutputBuffer() {
	OFS.close(); //close OFS
	OFS_debug.close();	//close OFS_debug
	delete[] buffer;	//release the buffer
};


void OutputBuffer::add(int x) {
	buffer[current_size] = x;
	current_size++;
	filesize++;
	if(current_size == capacity){
		OFS.write((char*)buffer, sizeof(int)*capacity); //Write the contents of the buffer to the files.
		for (int i = 0; i < capacity; i++) {
			OFS_debug << buffer[i] << endl;
		}
		current_size = 0; //clear the buffer
	};
};

void OutputBuffer::finish() { // add the rest number of the buffer
	OFS.write((char*)buffer, sizeof(int)*current_size);
	for (int i = 0; i < current_size; i++) {
		OFS_debug << buffer[i] << endl;
	}
	current_size = 0;
}

int OutputBuffer::getfilesize() { // return filesize
	return filesize;
}

