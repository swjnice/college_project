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
	preorder(root);
}

void BST::preorder(TreeNode* curr_node) {
	if (curr_node == nullptr) {
		return;
	}
	cout << "[" << curr_node->key << ", " << curr_node->data << "] ";
	preorder(curr_node->left);
	preorder(curr_node->right);
}

void BST::postorder() {
	postorder(root);
}

void BST::postorder(TreeNode* curr_node) {
	if (curr_node == nullptr) {
		return;
	}
	postorder(curr_node->left);
	postorder(curr_node->right);
	cout << "[" << curr_node->key << ", " << curr_node->data << "] ";
}

void BST::levelorder() {
	levelorder(root);
}

void BST::levelorder(TreeNode* curr_node) {
	Queue<TreeNode*> Nodelist(10); // make Queue sized 10
	for (int i = 0; i <= getLevelFromLeaf(curr_node); i++) { // push all Node on Queue in levelorder
		level_push(curr_node, Nodelist, i);
	}
	while (!Nodelist.isEmpty()) { // Print out All Queue
		TreeNode* Nodeout = Nodelist.pop();
		cout << "[" << Nodeout->key << ", " << Nodeout->data << "] ";
	}
}

void BST::level_push(TreeNode* curr_node, Queue<TreeNode*>& bst_node, int level) { // push all Node at certain level from given Node on Queue
	if (curr_node == nullptr) {
		return;
	}
	if (level == 0) {
		bst_node.push(curr_node);
	}
	else {
		level_push(curr_node->left, bst_node, level - 1);
		level_push(curr_node->right, bst_node, level - 1);
	}
}

void BST::merge(const BST& bst) {
	merge(root, bst.root);
}

void BST::merge(TreeNode*& curr_node, TreeNode* merge_node) {
	if (merge_node == nullptr) { 
		return;
	}
	TreeNode* search = find(curr_node, merge_node->key); 
	if (search == nullptr) { // new key
		this->insert(merge_node->key, merge_node->data);
	}
	else { // if have common key
		search->data = merge_node->data;
	}
	merge(curr_node, merge_node->left); // merge children
	merge(curr_node, merge_node->right);
}
