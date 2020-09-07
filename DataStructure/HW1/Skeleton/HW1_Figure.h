#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>

using namespace std;

class Figure {
protected:
	float area;

public:
	// TODO: Declare and define member functions following the instruction
	// You can add other member functions if you need

};

class Rectangle : public Figure {
private:
	int width;
	int height;
	int* point;

public:
	// TODO: Define member functions declared as below
	// You can add other member functions if you need
	Rectangle();
	Rectangle(int, int, int, int);
	~Rectangle();
	void shift(int, int);
	ostream& print(ostream&) const;
};

class Circle : public Figure {
private:
	int radius;
	int* center;

public:
	// TODO: Define member functions declared as below
	// You can add other member functions if you need
	Circle();
	Circle(int, int, int);
	~Circle();
	void shift(int, int);
	ostream& print(ostream&) const;
};

#endif