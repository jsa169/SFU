/*
 * Node.h
 *
 * Class Definition: Node of a singly linked list 
 *                   in which the data is of "int" data type.
 *                   Designed and implemented as a non-ADT.
 *
 * Created on: 
 * Author: 
 */
 

class Node
{
public:

	// Public data members - Why are the data members public?
	int data;     // The data in the node
	Node* next;   // Pointer to next node
	
	// Constructors
	Node();
	Node(int theData);
	Node(int theData, Node* theNextNode);

}; // end Node