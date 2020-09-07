#pragma once

#include <string>

using std::string;

bool check_intMax(int* number, int numbersize);
int Minnumpos(int* number, int numbersize);

void merge(int page_size, int nRun, int num_pages, int** filesize, string* in_file_path,
		string out_file_path, string debug_out_file_path);

void mergefiles(int nRun, int &j, int &c, int numbermerge, int page_size, int** filesize);
