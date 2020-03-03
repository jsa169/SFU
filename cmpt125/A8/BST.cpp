
#include "BST.h"
#include "BT-visualize.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <string>


// Implement the following five methods
// inserts val into BST rooted at x and returns the tree's new root
BTnode * insert(BTnode * x, int val) {
	if (x == NULL){
		struct BTnode * a = (struct BTnode *)malloc(sizeof(BTnode));
		a->val = val;
		x=a;
		return x;
	}

	if (val <= x->val){
		x->left = insert(x->left, val);
	}

	if (val >= x->val){
		x->right = insert(x->right, val);
	}

	return x;
}

// returns true iff target in tree rooted at x
bool search(BTnode * x, int target) {
	if (x == NULL){
		return false;
	}

	if (x->val == target){
		return true;
	}

	if (target < x->val){
		return search(x->left, target);
	}

	else {
		return search(x->right, target);
	}
}

// Find the maximum value of a tree rooted at x
int findmax(BTnode * x) {
	if (x->right == NULL && x->left == NULL){
		return x->val;
	}
	if (x->right == NULL && x->left != NULL){
		return x->val;
	}

	if (x->right != NULL && x->left == NULL){
		return findmax(x->right);
	}

	if (x->right->val >= x->left->val){
		return findmax(x->right);
	}
	else {
		return findmax(x->left);
	}
}

// Find the manimum value of a tree rooted at x
int findmin(BTnode * x) {
	if (x->right == NULL && x->left == NULL){
		return x->val;
	}
	if (x->right == NULL && x->left != NULL){
		return findmin(x->left);
	}

	if (x->right != NULL && x->left == NULL){
		return x->val;
	}

	if (x->right->val >= x->left->val){
		return findmin(x->left);
	}
	else {
		return findmin(x->right);
	}
}

// Given a binary tree, print its nodes in in-order
void pAO(BTnode * x){
	if (x == NULL){
		return;
	}
	pAO(x->left);
	printf("%d ", x->val);
	pAO(x->right);
}

void printAscendOrder(BTnode * x){
	pAO(x);
	printf("\n");
}

// You don't need to worry about these methods below
BTascii print_helper(BTnode * x);

void print(BTnode * x) {
    BTascii ret = print_helper(x);
    ret.display();
}

BTascii print_helper(BTnode * x) {
    if (x == NULL) return BTascii();
    BTascii left = print_helper(x->left);
    BTascii right = print_helper(x->right);
    char buf[25];
    sprintf(buf, "%d", x->val); return join(left, right, std::string(buf)); 

}
void postfree(BTnode * x) {
    if (x == NULL) return;
    postfree(x->left);
    postfree(x->right);
    delete x;
}