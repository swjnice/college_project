#include "HW3_AVL.h"

AVL::AVL() : BST(){
	
}


void AVL::insert(const int& key, const double& data) {
	this->insert(root, key, data);
}

void AVL::remove(const int& key) {
	this->remove(root, key);
}

int AVL::BF(TreeNode* curr_node) {
	// BF = The height of left child node of curr_node - The height of right child node of curr_node
	if (curr_node == nullptr) {
		return 0;
	}
	return (getLevelFromLeaf(curr_node->left) - getLevelFromLeaf(curr_node->right));
}

void AVL::insert(TreeNode*& curr_node, const int& key, const double& data) {
	// TODO : Insert new node in AVL tree
	if (curr_node == nullptr) {
		// TODO : Create a new node
		curr_node = new TreeNode(key, data);
	}
	else if (key < curr_node->key) {
		// TODO : Insert the node in left sub-tree with rotation process
		insert(curr_node->left, key, data);
		if (BF(curr_node) >= 2) {
			getBalance(curr_node);
		}
	}
	else if (key > curr_node->key) {
		// TODO : Insert the node in right sub-tree with rotation process
		insert(curr_node->right, key, data);
		if (BF(curr_node) <= -2) {
			getBalance(curr_node);
		}
	}
	else if (key == curr_node->key) {
		// TODO : Update when a node which has same key exists
		curr_node->data = data;
	}
	return;
}

void AVL::rotateSingle(TreeNode*& curr_node) {
	// TODO : Implement a rotateSingle function
	// Right-Single-Rotate
	if (this->BF(curr_node) > 0) {
		Rightrotate(curr_node);
	}
	//Left-Single-Rotate
	else {
		Leftrotate(curr_node);
	}
}

void AVL::rotateDouble(TreeNode*& curr_node) {
	// TODO : Implement a rotateDouble function
	if (this->BF(curr_node) > 0) {
		Leftrotate(curr_node->left);
		Rightrotate(curr_node);
	}
	else {
		Rightrotate(curr_node->right);
		Leftrotate(curr_node);
	}
}

void AVL::remove(TreeNode*& curr_node, const int& key) {
	// TODO : Implement a remove function with propagated rotation process
	BST::remove(curr_node, key);
	getBalance(curr_node);
	getBalance(curr_node);
}

void AVL::Leftrotate(TreeNode* curr_node) {
	if (curr_node == this->root) {
		this->root = curr_node->right;
		curr_node->right = root->left;
		root->left = curr_node;
		return;
	}
	TreeNode* parent = find_parent(this->root, curr_node);
	if (parent->left == curr_node) {
		parent->left = curr_node->right;
		curr_node->right = parent->left->left;
		parent->left->left = curr_node;
	}
	else {
		parent->right = curr_node->right;
		curr_node->right = parent->right->left;
		parent->right->left = curr_node;
	}
}

void AVL::Rightrotate(TreeNode* curr_node) {
	if (curr_node == this->root) {
		this->root = curr_node->left;
		curr_node->left = root->right;
		root->right = curr_node;
		return;
	}
	TreeNode* parent = find_parent(this->root, curr_node);
	if (parent->left == curr_node) {
		parent->left = curr_node->left;
		curr_node->left = parent->left->right;
		parent->left->right = curr_node;
	}
	else {
		parent->right = curr_node->left;
		curr_node->left = parent->right->right;
		parent->right->right = curr_node;
	}
}

// find inbalance node
TreeNode* AVL::find_inbalance(TreeNode*& curr_node) {
	if (curr_node == nullptr) {
		return nullptr;
	}
	int balance = BF(curr_node);
	TreeNode* goLeft = find_inbalance(curr_node->left);
	TreeNode* goRight = find_inbalance(curr_node->right);
	if (balance == 2 || balance == -2) {
		if (goLeft == nullptr && goRight == nullptr) {
			return curr_node;
		}
		else if (goLeft == nullptr) {
			return goRight;
		}
		else {
			return goLeft;
		}
	}
	else {
		if (goLeft != nullptr) {
			return goLeft;
		}
		else {
			return goRight;
		}
	}
}

//get balance
void AVL::getBalance(TreeNode*& curr_node) {
	TreeNode* rotate_need = find_inbalance(curr_node);
	if (rotate_need == nullptr) { // don't need to rotate
		return;
	}
	// get balance
	int inbalance = BF(rotate_need);
	if (inbalance >= 2) {
		if (BF(rotate_need->left) == -1) {
			rotateDouble(rotate_need);
		}
		else {
			rotateSingle(rotate_need);
		}
	}
	else {
		if (BF(rotate_need->right) == 1) {
			rotateDouble(rotate_need);
		}
		else {
			rotateSingle(rotate_need);
		}
	}
}

// find curr_node's parent
TreeNode* AVL::find_parent(TreeNode* from, TreeNode* curr_node) {
	if (curr_node == nullptr || curr_node == this->root || from == nullptr) {
		return nullptr;
	}
	if (from->left == curr_node || from->right == curr_node) {
		return from;
	}
	TreeNode* parent = find_parent(from->left, curr_node);
	if (parent == nullptr) {
		parent = find_parent(from->right, curr_node);
	}
	return parent;
}