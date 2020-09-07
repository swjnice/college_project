#ifndef NARYBIGNUM_H
#define NARYBIGNUM_H

#include <iostream>
#include <string>

using namespace std;

class NaryBigNum {
private:
	char *number;
	int size;
	int base;
public:
	NaryBigNum();
	NaryBigNum(int, string);
	NaryBigNum(const NaryBigNum&);
	~NaryBigNum();
	NaryBigNum operator+(const NaryBigNum&);
	NaryBigNum& operator=(const NaryBigNum&);
	NaryBigNum operator*(const NaryBigNum&);
	friend ostream& operator<< (ostream&, const NaryBigNum&);
};
#endif NARYBIGNUM_H