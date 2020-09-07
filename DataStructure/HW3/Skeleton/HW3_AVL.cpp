#include "HW3_AVL.h"

AVL::AVL() {
	// TODO : Implement a constructor of AVL
}


void AVL::insert(const int& key, const double& data) {
	// TODO : Implement an insert function of AVL Tree using private insert function
}

void AVL::remove(const int& key) {
	// TODO : Implement a remove function of AVL Tree using private remove function
}

int AVL::BF(TreeNode* curr_node) {
	// TODO : Return the balance factor of curr_node
	// BF = The height of left child node of curr_node - The height of right child node of curr_node
}

void AVL::insert(TreeNode*& curr_node, const int& key, const double& data) {
	// TODO : Insert new node in AVL tree
	if (curr_node == nullptr) {
		// TODO : Create a new node
	}
	else if (key < curr_node->key) {
		// TODO : Insert the node in left sub-tree with rotation process
	}
	else if (key > curr_node->key) {
		// TODO : Insert the node in right sub-tree with rotation process
	}
	else if (key == curr_node->key) {
		// TODO : Update when a node which has same key exists
	}
	return;
}

void AVL::rotateSingle(TreeNode*& curr_node) {
	// TODO : Implement a rotateSingle function
}

void AVL::rotateDouble(TreeNode*& curr_node) {
	// TODO : Implement a rotateDouble function
}

void AVL::remove(TreeNode*& curr_node, const int& key) {
	// TODO : Implement a remove function with propagated rotation process
}