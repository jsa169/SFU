/*
 * BSTNode.h
 * 
 * Description: Node Class for BST
 *
 * 
 * Author: Jichuan Shi, Martin Suryadi
 * Date: 2019-11-28
 */

//----------------------------------------------------------------------------------------------
//include statements
#include <string>
#include <iostream>

using namespace std;
//----------------------------------------------------------------------------------------------
//class BSTNode
template <class ElementType>
class BSTNode{
//Public members and methods
public:
	ElementType data;				//data
	BSTNode<ElementType> * right;	//Pointer to right
	BSTNode<ElementType> * left;	//Point to left

	BSTNode(ElementType newElement);	//Default Constructor
	void printNode();					//method to Print the data
	ElementType getWord();				//Method to get the first half of data
};

//----------------------------------------------------------------------------------------------
//Default Constructor
template<class ElementType>
BSTNode<ElementType>::BSTNode(ElementType newElement){
	this->data = newElement;
	right = NULL;
	left = NULL;
}

//----------------------------------------------------------------------------------------------
//Description:	print out the data
template<class ElementType>
void BSTNode<ElementType>::printNode(){
	cout<<data<<endl;		
}

//----------------------------------------------------------------------------------------------
//Description: return the first half of data before the ':'
template<class ElementType>
ElementType BSTNode<ElementType>::getWord(){
	int index = 0;
	while (data[index] != ':'){
		index++;
	}
	ElementType word = data.substr(0, index);

	return word;	
}