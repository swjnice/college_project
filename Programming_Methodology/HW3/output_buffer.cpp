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
	if(current_size == capacity){
		OFS.write((char*)buffer, sizeof(int)*capacity); //Write the contents of the buffer to the files.
		for (int i = 0; i < capacity; i++) {
			OFS_debug << buffer[i] << endl;
		}
		current_size = 0; //clear the buffer
	};
};
