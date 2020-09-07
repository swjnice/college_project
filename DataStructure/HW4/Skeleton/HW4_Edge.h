#ifndef HW4_EDGE_H
#define HW4_EDGE_H

#include <iostream>
using namespace std;

class Edge {
private:
	int idx;
	int src;
	int dest;
	int dist;
public:
	Edge();
	Edge(int, int, int, int);
	int getIdx();
	int getSrc();
	int getDest();
	int getDist();
	void setIdx(int);
	void setSrc(int);
	void setDest(int);
	void setDist(int);
	bool operator <(const Edge&);
	bool operator >(const Edge&);
	Edge& operator=(const Edge&);
	void print();
};
#endif