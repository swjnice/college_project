#include "HW4_Edge.h"

// TODO : Implement constructor and all member functions of Edge class
Edge::Edge() {
	idx = 0;
	src = 0;
	dest = 0;
	dist = 0;
}
Edge::Edge(int i, int s, int d, int w) {
	idx = i;
	src = s;
	dest = d;
	dist = w;
}
int Edge::getIdx() {
	return idx;
}
int Edge::getSrc() {
	return src;
}
int Edge::getDest() {
	return dest;
}
int Edge::getDist() {
	return dist;
}
void Edge::setIdx(int i) {
	idx = i;
}
void Edge::setSrc(int s) {
	src = s;
}
void Edge::setDest(int d) {
	dest = d;
}
void Edge::setDist(int w) {
	dist = w;
}
bool Edge::operator <(const Edge& e) {
	if (this->dist < e.dist) {
		return true;
	}
	else {
		return false;
	}
}
bool Edge::operator >(const Edge& e) {
	if (this->dist > e.dist) {
		return true;
	}
	else {
		return false;
	}
}
Edge& Edge::operator=(const Edge& e) {
	this->idx = e.idx;
	this->src = e.src;
	this->dest = e.dest;
	this->dist = e.dist;
	return *this;
}
void Edge::print() {
	std::cout << "[" << idx << "] " << src << " - " << dest << " (" << dist << ")";
}