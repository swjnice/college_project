#ifndef HW4_NODE_H
#define HW4_NODE_H

#include <iostream>
using namespace std;

class Node {
private:
	int idx;
	int dist;
public:
	Node();
	Node(int, int);
	int getIdx();
	int getDist();
	void setIdx(int);
	void setDist(int);
	bool operator <(const Node&);
	bool operator >(const Node&);
	Node& operator=(const Node&);
	void print();
};
#endif