#include "HW4_Node.h"

// TODO : Implement constructor and all member functions of Node class
Node::Node() {
	idx = 0;
	dist = 0;
}
Node::Node(int i, int d) {
	idx = i;
	dist = d;
}
int Node::getIdx() {
	return idx;
}
int Node::getDist() {
	return dist;
}
void Node::setIdx(int i) {
	idx = i;
}
void Node::setDist(int d) {
	dist = d;
}
bool Node::operator <(const Node& n) {
	if (this->dist < n.dist) {
		return true;
	}
	else {
		return false;
	}
}
bool Node::operator >(const Node& n) {
	if (this->dist > n.dist) {
		return true;
	}
	else {
		return false;
	}
}
Node& Node::operator=(const Node& n) {
	this->idx = n.idx;
	this->dist = n.dist;
	return *this;
}
void Node::print() {
	std::cout << "[" << idx << "] (" << dist << ")";
}