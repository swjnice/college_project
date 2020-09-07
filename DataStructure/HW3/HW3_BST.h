#ifndef HW3_BST_H
#define HW3_BST_H

#include "HW2_Queue.h"
#include <iostream>
using namespace std;

class TreeNode {
public:
	int key;
	double data;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int k, double d) {
		key = k;
		data = d;
		left = nullptr;
		right = nullptr;
	}
};

class BST {
public:
	BST();
	~BST();
	bool isEmpty();
	int getHeight();
	void preorder();
	void postorder();
	void levelorder();
	virtual void insert(const int&, const double&);
	virtual void remove(const int&);
	double find(const int&);
	void merge(const BST& bst);
protected:
	void removeFromLeaf(TreeNode*&);
	TreeNode *root;
	int getLevelFromLeaf(TreeNode *);
	void preorder(TreeNode *);
	void postorder(TreeNode *);
	void levelorder(TreeNode *);
	void level_push(TreeNode*, Queue<TreeNode*>&, int level);
	TreeNode* find(TreeNode *&, const int&);
	virtual void insert(TreeNode *&, const int&, const double&);
	TreeNode*& rightMostChild(TreeNode *&);
	void remove(TreeNode *&, const int&);
	void doRemoval(TreeNode *&);
	void noChildRemove(TreeNode *&);
	void oneChildRemove(TreeNode *&);
	void twoChildRemove(TreeNode *&);
	void merge(TreeNode*& curr_node, TreeNode* merge_node);
};

#endif
