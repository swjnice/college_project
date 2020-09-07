#ifndef HW4_ADJ_H
#define HW4_ADJ_H

#include "HW4_Edge.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void tokenize(const string&, vector<string>&, const string&);
void adjReader(string, int&, int**&);
void matrixToList(int, int**, int*, Edge**);

#endif
