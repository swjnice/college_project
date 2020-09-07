#ifndef HW3_AVL_H
#define HW3_AVL_H

#include "HW3_BST.h"

class AVL : public BST {
public:
	AVL();
	void insert(const int&, const double&);
	void remove(const int&);
private:
	int BF(TreeNode*);
	void insert(TreeNode*&, const int&, const double&);
	void rotateSingle(TreeNode *&);
	void rotateDouble(TreeNode *&);
	void remove(TreeNode*&, const int&);
};

#endif
