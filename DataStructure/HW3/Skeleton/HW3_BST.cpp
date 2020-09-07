#include "HW3_BST.h"

// Implemented in the lab class

BST::BST() {
	root = nullptr;
}

BST::~BST() {
	removeFromLeaf(root);
}

void BST::removeFromLeaf(TreeNode*& curr_node) {
	if (curr_node != nullptr) {
		removeFromLeaf(curr_node->left);
		removeFromLeaf(curr_node->right);
		delete curr_node;
	}
}

bool BST::isEmpty() {
	return root == nullptr;
}

int BST::getHeight() {
	return (root == nullptr) ? -1 : getLevelFromLeaf(root);
}

int BST::getLevelFromLeaf(TreeNode* curr_node) {
	return (curr_node == nullptr) ? -1 : __max(getLevelFromLeaf(curr_node->left), getLevelFromLeaf(curr_node->right)) + 1;
}


void BST::insert(const int& key, const double& data) {
	insert(root, key, data);
}

void BST::insert(TreeNode*& curr_node, const int& key, const double& data) {
	if (curr_node == nullptr) curr_node = new TreeNode(key, data);
	else if (curr_node->key == key) curr_node->data = data;
	else if (key < curr_node->key) insert(curr_node->left, key, data);
	else insert(curr_node->right, key, data);
}

double BST::find(const int& key) {
	return (find(root, key) != nullptr) ? find(root, key)->data : -1;
}

TreeNode* BST::find(TreeNode*& curr_node, const int& key) {
	if (curr_node == nullptr) return nullptr;
	else if (curr_node->key == key) return curr_node;
	else if (key < curr_node->key) return find(curr_node->left, key);
	else return find(curr_node->right, key);
}

TreeNode*& BST::rightMostChild(TreeNode*& curr_node) {
	return (curr_node->right != nullptr) ? rightMostChild(curr_node->right) : curr_node;
}

void BST::remove(const int& key) {
	remove(root, key);
}

void BST::remove(TreeNode*& curr_node, const int& key) {
	if (curr_node != nullptr) {
		if (key == curr_node->key) doRemoval(curr_node);
		else if (key < curr_node->key) remove(curr_node->left, key);
		else remove(curr_node->right, key);
	}
}

void BST::doRemoval(TreeNode*& curr_node) {
	if (curr_node->left == nullptr && curr_node->right == nullptr) {
		noChildRemove(curr_node);
	}
	else if (curr_node->left != nullptr && curr_node->right != nullptr) {
		twoChildRemove(curr_node);
	}
	else oneChildRemove(curr_node);
}

void BST::noChildRemove(TreeNode*& curr_node) {
	TreeNode* tmp = curr_node;
	curr_node = nullptr;
	delete tmp;
}

void BST::oneChildRemove(TreeNode*& curr_node) {
	TreeNode* tmp = curr_node;
	curr_node = (curr_node->left != nullptr) ? curr_node->left : curr_node->right;
	delete tmp;
}

void BST::twoChildRemove(TreeNode*& curr_node) {
	TreeNode*& new_node = rightMostChild(curr_node->left);
	curr_node->key = new_node->key;
	curr_node->data = new_node->data;

	doRemoval(new_node);
}

// TODO list

void BST::preorder() {
	// TODO : Implement an preorder function of BST using protected preorder function
}

void BST::preorder(TreeNode* curr_node) {
	// TODO : Print the nodes in order of the preorder traversal, starting at curr_node
}

void BST::postorder() {
	// TODO : Implement an postorder function of BST using protected postorder function
}

void BST::postorder(TreeNode* curr_node) {
	// TODO : Print the nodes in order of the postorder traversal, starting at curr_node
}

void BST::levelorder() {
	// TODO : Implement an levelorder function of BST using protected levelorder function
}

void BST::levelorder(TreeNode* curr_node) {
	// TODO : Print the nodes in order of the levelorder traversal, starting at curr_node
	// You can use given Queue class
}

void BST::merge(const BST& bst) {
	// TODO : Merge bst into this BST using protected merge function
}

void BST::merge(TreeNode*& curr_node, TreeNode* merge_node) {
	// TODO : Merge the sub-tree whose root is merge_node into the sub-tree whose root is curr_node
	// Do not delete merge_node
}