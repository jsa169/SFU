/*
 * BST.h
 * 
 * Description: Data collection Binary Search Tree ADT class.
 *              Link-based implementation.
 *
 * Class invariant: It is always a BST.
 * 
 * Author: Jichuan Shi, Martin Suryadi
 * Date: 2019-11-28
 */

//----------------------------------------------------------------------------------------------
//include statements

#include "BSTNode.h"
#include "ElementDoesNotExistInBSTException.h"
#include "ElementAlreadyExistsInBSTException.h"

using namespace std;

//----------------------------------------------------------------------------------------------
template <class ElementType>
class BST {
//Private members and methods	
private:

	BSTNode<ElementType> * root;	//Root pointer
	int elementCount;				//element Count
    
    // Utility methods

    //Recursively insert an element
    bool insertR(const ElementType& element, BSTNode<ElementType>* current) throw(ElementAlreadyExistsInBSTException);

    //Recursively search for an element
    ElementType& retrieveR(const ElementType& targetElement, BSTNode<ElementType>* current) const throw(ElementDoesNotExistInBSTException);

    //Recursively traverse throught the BST
	void traverseInOrderR(BSTNode<ElementType> *current) const;

	//Recursively copy from another try
	BSTNode<ElementType> * copyBST(const BSTNode<ElementType> *currentFrom);

	//Recursively remove a BST
	BSTNode<ElementType> * remove(BSTNode<ElementType> *toBeRemoved);

         
//----------------------------------------------------------------------------------------------
public:
    // Constructors and destructor:
	BST();                               // Default constructor
    BST(ElementType& element);           // Parameterized constructor 
	BST(const BST<ElementType>& aBST);   // Copy constructor 
    ~BST();                              // Destructor 
    // BST operations:

    // Time efficiency: O(1)
	int getElementCount() const;

	// Time efficiency: O(log2 n)
	void insert(const ElementType& newElement) throw(ElementAlreadyExistsInBSTException);	

	// Time efficiency: O(log2 n)
	ElementType& retrieve(const ElementType& targetElement) throw(ElementDoesNotExistInBSTException);

	// Time efficiency: O(n)
	void traverseInOrder() const;
	
};
//----------------------------------------------------------------------------------------------
	//Description:		Recursively insert an element
	//Post Condition:	Element inserted, still a BST
	//Return:			True if successfully insert, false if insertion fails
	//Exeption:			throws an exeption if target already exist
	//Time efficiency: 	O(log2 n)

	template <class ElementType>
	bool BST<ElementType>::insertR(const ElementType& element, BSTNode<ElementType>* current) throw(ElementAlreadyExistsInBSTException){
		
		if(root == NULL){
			root = new BSTNode<ElementType> (element);
			return true;
		}
		if(element == current->data) {
			throw ElementAlreadyExistsInBSTException("insertR() called with element that already exists");
		}
		if(element < current->data){
			if(current->left == NULL){
				BSTNode<ElementType> *newNode = new BSTNode<ElementType> (element);
				if(newNode == NULL) return false;
				current->left = newNode;
			}else insertR(element, current->left);

		}else{
			if(current->right == NULL){
				BSTNode<ElementType> *newNode = new BSTNode<ElementType> (element);
				if(newNode == NULL) return false;
				current->right = newNode;
			}else insertR(element, current->right);
		}
	}
//----------------------------------------------------------------------------------------------
	//Description:		Recursively search for an element
	//Precondition:		a BST
	//Return:			target element if found
	//Exeption:			throws an exeption if target is not found
	//Time efficiency: 	O(log2 n)	

	template <class ElementType>
    ElementType& BST<ElementType>::retrieveR(const ElementType& targetElement, BSTNode<ElementType>* current) const throw(ElementDoesNotExistInBSTException){
    	if(current->getWord() == targetElement) {
    		return current->data;
    	}
    	if(targetElement < current->getWord()) {
    		if(current->left == NULL) {
    			throw ElementDoesNotExistInBSTException("retrieveR() called with element that does not exist in left");
    		}
    		else {
    			retrieveR(targetElement, current->left);
    		}
    	}
    	else {
    		if(current->right == NULL) {
    			throw ElementDoesNotExistInBSTException("retrieveR() called with element that does not exist in right");
    		}
    		else {
    			retrieveR(targetElement, current->right);
    		}
    	}
    }
//----------------------------------------------------------------------------------------------
 	//Description:		Recursively traverse through the BST
	//Precondition:		a BST
	//Time efficiency: 	O(n)   
 	template <class ElementType>
	void BST<ElementType>::traverseInOrderR(BSTNode<ElementType> *current) const{
		if(current == NULL) return;
		else{
			traverseInOrderR(current->left);
			current->printNode();
			traverseInOrderR(current->right);
		}
	}
//----------------------------------------------------------------------------------------------
 	//Description:		Recursively copy another BST
	//Return:			Pointer to the newly created copy
	//Time efficiency: 	O(n)  
	template <class ElementType>
	BSTNode<ElementType> * BST<ElementType>::copyBST(const BSTNode<ElementType> *copyFrom){
		if (copyFrom == NULL) return NULL;
		else{
			string s = copyFrom->data;
			BSTNode<ElementType> * node = new BSTNode<ElementType>(s);	
			node->left = copyBST(copyFrom->left);
			node->right = copyBST(copyFrom->right);
			return node;
		}
	}
//----------------------------------------------------------------------------------------------
 	//Description:		Recursively delete the BST
 	//Post confition:	All memory freed
	//Time efficiency: 	O(n)   
	template <class ElementType>
	BSTNode<ElementType> * BST<ElementType>::remove(BSTNode<ElementType> *toBeRemoved){
		if(toBeRemoved->left != NULL) remove(toBeRemoved->left);
		if(toBeRemoved->right != NULL) remove(toBeRemoved->right);
		delete toBeRemoved;
	}
         
//----------------------------------------------------------------------------------------------
	//Constructors

	// Default constructor
	template <class ElementType>
	BST<ElementType>::BST(){
		root = NULL;
		elementCount = 0;
	}

	// Parameterized constructor 
	template <class ElementType>
    BST<ElementType>::BST(ElementType& element){
    	root = element;
    	elementCount = 1;
    }

	// Copy constructor 
	template <class ElementType>
	BST<ElementType>::BST(const BST<ElementType>& aBST){
		if (aBST.root == NULL) {
			elementCount = 0;
			root = NULL;
		}
		else {
			root = copyBST(aBST.root);
			elementCount = aBST.elementCount;
		}
	}

//----------------------------------------------------------------------------------------------
	// Destructor 	
	template <class ElementType>
    BST<ElementType>::~BST(){
    	if(root == NULL);
    	else remove(root);
    } 

//----------------------------------------------------------------------------------------------
    // Desctiption:	Gets the elment count of the BST then return it.
    // Time efficiency: O(1)
	template <class ElementType>
	int BST<ElementType>::getElementCount() const{
		return elementCount;
	}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
	//Description:		Recursively insert an element
	//Post Condition:	Element inserted, still a BST
	//Return:			True if successfully insert, false if insertion fails
	//Exeption:			throws an exeption if target already exist
	//Time efficiency: 	O(log2 n)	template <class ElementType>
	template <class ElementType>
	void BST<ElementType>::insert(const ElementType& newElement) throw(ElementAlreadyExistsInBSTException){
		try {
			insertR(newElement, root);
			elementCount++;
		} catch (ElementAlreadyExistsInBSTException &anException) {
			throw anException;
		}

	}
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
	//Description:		Recursively search for an element
	//Precondition:		a BST
	//Return:			target element if found
	//Exeption:			throws an exeption if target is not found
	//Time efficiency: 	O(log2 n)	
	template <class ElementType>
	ElementType& BST<ElementType>::retrieve(const ElementType& targetElement) throw(ElementDoesNotExistInBSTException){
		try {
			return retrieveR(targetElement, root);
		} catch (ElementDoesNotExistInBSTException &anException) {
			throw anException;
		}
	}
//----------------------------------------------------------------------------------------------
 	//Description:		Recursively traverse through the BST
	//Precondition:		a BST
	//Time efficiency: 	O(n) 
	template <class ElementType>
	void BST<ElementType>::traverseInOrder() const{
		traverseInOrderR(root);
	}

