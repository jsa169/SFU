/* 
 * PriorityQueue.h
 *
 * Description: BinaryHeap data collection ADT class.
 *              Implementation of an int sequence with insert and remove ...
 *              Throw exceptions if user use invalid inputs such as retrieving when the BinaryHeap
 *              is empty
 * Class Invariant: Mininum Binary Heap. A parent must be greater or equal to its children. 
 *
 * Author: Jichuan Shi, Martin Suryadi
 * Date:10/27/2019
 */

//----------------------------------------------------------------------------------------------

#include"BinaryHeap.h"
#include"EmptyDataCollectionException.h"
#include<iostream>

using namespace std;
//----------------------------------------------------------------------------------------------
template<class ElementType>
class PriorityQueue {
    private:
        BinaryHeap<ElementType>* elements;  

        unsigned frontIndex;	//Alwasy 0, the root
        unsigned elementCount;  // number of elements in the queue
//----------------------------------------------------------------------------------------------

    public:
       // Description: constructor	
	   PriorityQueue();

       // Description: Destructor	
	   // Post condition: All memory freed
	   ~PriorityQueue();

	   // Description: Returns "true" is this Priority Queue is empty, otherwise "false".
	   // Postcondition:  The Priority Queue is unchanged by this operation.
	   // Time Efficiency: O(1)
	   bool isEmpty() const;

	   // Description: Inserts newElement in the Priority Queue.
	   //              It returns "true" if successful, otherwise "false".
	   // Time Efficiency: O(log2 n)
	   bool enqueue(ElementType& newElement);

	   // Description: Removes (but does not return) the element with the "highest" priority.
	   // Precondition: This Priority Queue is not empty.
	   // Exception: Throws EmptyDataCollectionException if this Priority Queue is empty.
	   // Time Efficiency: O(log2 n)
	   void dequeue() throw(EmptyDataCollectionException);
	   
	   // Description: Returns (but does not remove) the element with the "highest" priority.
	   // Precondition: This Priority Queue is not empty.
	   // Exception: Throws EmptyDataCollectionException if this Priority Queue is empty.
	   // Time Efficiency: O(1)
	   ElementType& peek() throw(EmptyDataCollectionException);

	   void printQueue();
};

//----------------------------------------------------------------------------------------------
//Description:Constructor
template<class ElementType>
PriorityQueue<ElementType>::PriorityQueue(){
	elementCount = 0;
	frontIndex = 0;
	elements = new BinaryHeap<ElementType>;
}


//----------------------------------------------------------------------------------------------
//Description:Destructor
//Post condition: Free all used memmory
template<class ElementType>
	PriorityQueue<ElementType>::~PriorityQueue(){
	delete elements;
}


//----------------------------------------------------------------------------------------------
// Description: Returns "true" is this Priority Queue is empty, otherwise "false".
// Postcondition:  The Priority Queue is unchanged by this operation.
// Time Efficiency: O(1)
template<class ElementType>
bool PriorityQueue<ElementType>::isEmpty() const{
	return (elementCount == 0);
}

//----------------------------------------------------------------------------------------------
// Description: Inserts newElement in the Priority Queue.
//              It returns "true" if successful, otherwise "false".
// Time Efficiency: O(log2 n)
template<class ElementType>
bool PriorityQueue<ElementType>::enqueue(ElementType& newElement){
	if(elements->insert(newElement)){
		elementCount++;
		return true; 	
	}
	return false;

}

//----------------------------------------------------------------------------------------------
// Description: Removes (but does not return) the element with the "highest" priority.
// Precondition: This Priority Queue is not empty.
// Exception: Throws EmptyDataCollectionException if this Priority Queue is empty.
// Time Efficiency: O(log2 n)
template<class ElementType>
void PriorityQueue<ElementType>::dequeue() throw(EmptyDataCollectionException){
	if(isEmpty()) throw EmptyDataCollectionException("dequeue() called with empty queue.");
	elements->remove();
	elementCount--;
}

//----------------------------------------------------------------------------------------------
// Description: Returns (but does not remove) the element with the "highest" priority.
// Precondition: This Priority Queue is not empty.
// Exception: Throws EmptyDataCollectionException if this Priority Queue is empty.
// Time Efficiency: O(1)
template<class ElementType>
ElementType& PriorityQueue<ElementType>::peek() throw(EmptyDataCollectionException){
	if(isEmpty()) throw EmptyDataCollectionException("dequeue() called with empty queue.");
	return elements->retrieve();
}

//----------------------------------------------------------------------------------------------
// Description: Printout the Priority Queque as a binary heap
// Time Efficiency: O(n)
template<class ElementType>
void PriorityQueue<ElementType>::printQueue(){
	elements->printBinaryHeap();

} //end of PriorityQueue.h
