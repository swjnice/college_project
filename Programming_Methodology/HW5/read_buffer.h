#pragma once
#include <string>
#include <fstream>

using std::string;

class ReadBuffer {
public:
	ReadBuffer(int capacity, string filename, int filesize);
	ReadBuffer();
	void set(int capcity, string filename, int filesize);
	//	Allocate the array 'buffer'. Open IFS.
	~ReadBuffer();
	//	Release the array 'buffer'. Close IFS.
	bool read(int &x); // Means to read one integer from the buffer
	/*
	 * 	Returns true if reading is successful.
	 * 		The read value is stored in x.
	 * 	Returns false if reading is failure.
	 *
		If the buffer is empty,
			Read the integers of the size of capacity.
			If reading is failed, return false.
			If reading is successful, curr_pos = 0
		Set 'x' with the current position in the buffer.
	*/
	int getreadsize();
	bool checkallread();
private:
	int *buffer;
	int capacity;
	int readsize;
	int filesize;
	int curr_pos;
	std::ifstream IFS;
	bool allread;
};
