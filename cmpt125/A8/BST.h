#ifndef _BST_H_
#define _BST_H_
#include <iostream>
#include "BT-node.h"

// Implement the following five methods in BST.cpp file.

// Insert val into BST rooted at x and returns the tree's new root
BTnode * insert(BTnode * x, int val);

// Return true iff target in tree rooted at x
bool search(BTnode * x, int target);

// Return maxmium value of the tree rooted at x. Return 0 if tree is empty.
int findmax(BTnode * root);

// Return maxmium value of the tree rooted at x. Return 0 if tree is empty.
int findmin(BTnode * root);

// Given a binary tree, print its nodes in in-order
void printAscendOrder(BTnode * root);

// You don't need to implement these below in BST.cpp file
void print(BTnode * root);
void postfree(BTnode * root);

#endif // _BT_H_