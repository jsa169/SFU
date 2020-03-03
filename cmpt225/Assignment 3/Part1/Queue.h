/* 
 * Queue.h
 *
 * Description: Queue data collection ADT class.
 *              Implementation of an int sequence with enqueue/dequeue ...
*               Throw exceptions if user use invalid inputs such as peeking when the Queue
 *              is empty
 * Class Invariant:  FIFO or LILO order
 *
 * Author: Jichuan Shi, Martin Suryadi
 * Date:10/27/2019
 */

//----------------------------------------------------------------------------------------------
//include statements

#include <iostream>
#include "EmptyDataCollectionException.h"
using namespace std;


//----------------------------------------------------------------------------------------------
//Class: Queue
template<class ElementType>
class Queue {
    private:
        static unsigned const INITIAL_SIZE = 6;
        ElementType * elements;  

        unsigned elementCount;  // number of elements in the queue
        unsigned capacity;      // number of cells in the array
        unsigned frontindex;    // index the topmost element
        unsigned backindex;     // index where the next element will be placed

    public:

//----------------------------------------------------------------------------------------------
        // Description: Constructor
        Queue();

//----------------------------------------------------------------------------------------------
        //Description:Destructor
        //Post condition: Free all used memmory
        ~Queue();

//----------------------------------------------------------------------------------------------
        // Description: Returns "true" is this Queue is empty, otherwise "false".
        // Postcondition:  The Queue is unchanged by this operation.
        // Time Efficiency: O(1)
        bool isEmpty() const;

//----------------------------------------------------------------------------------------------
        // Description: Inserts newElement at the "back" of this Queue 
        //              (not necessarily the "back" of its data structure) and 
        //              returns "true" if successful, otherwise "false".
        // Time Efficiency: O(1)
        bool enqueue(ElementType& newElement);

//---------------------------------------------------------------------------------------------- 
       // Description: Removes (but does not return) the element at the "front" of this Queue 
       //              (not necessarily the "front" of its data structure).
       // Precondition: This Queue is not empty.
       // Exception: Throws EmptyDataCollectionException if this Queue is empty.   
       // Time Efficiency: O(1)
       void dequeue() throw(EmptyDataCollectionException);

//----------------------------------------------------------------------------------------------
       // Description: Returns (but does not remove) the element at the "front" of this Queue
       //              (not necessarily the "front" of its data structure).
       // Precondition: This Queue is not empty.
       // Exception: Throws EmptyDataCollectionException if this Queue is empty.
       // Time Efficiency: O(1)
       ElementType& peek() throw(EmptyDataCollectionException);  

//----------------------------------------------------------------------------------------------        
};



//----------------------------------------------------------------------------------------------

	// Description: Constructor
template<class ElementType>
Queue<ElementType>::Queue() : elementCount(0), capacity(INITIAL_SIZE), frontindex(0), backindex(0) {
    elements = new ElementType[INITIAL_SIZE];

} 

//----------------------------------------------------------------------------------------------
    //Description:Destructor
    //Post condition: Free all used memory
template<class ElementType>
Queue<ElementType>::~Queue(){
    delete[] elements;
}

//----------------------------------------------------------------------------------------------
   // Description: Returns "true" is this Queue is empty, otherwise "false".
   // Postcondition:  The Queue is unchanged by this operation.
   // Time Efficiency: O(1)
template<class ElementType>
bool Queue<ElementType>::isEmpty()  const{
    return elementCount == 0;
} 

//----------------------------------------------------------------------------------------------
   // Description: Inserts newElement at the "back" of this Queue 
   //              (not necessarily the "back" of its data structure) and 
   //              returns "true" if successful, otherwise "false".
   // Time Efficiency: O(1)
template<class ElementType>
bool Queue<ElementType>::enqueue(ElementType& newElement) {
	if (elements == NULL) return false;

//Expande Array if element count >= array capacity; capacity *= 2
    if(elementCount >= capacity){
        ElementType * newElements = new ElementType[capacity*2];
        for(unsigned i = 0; i<elementCount; i++){
            newElements[i] = elements[(frontindex+i)%capacity];
        }
        delete[] elements;
        elements = newElements;
        capacity = capacity*2;
        frontindex = 0; 
        backindex = elementCount;
    }
    
    //enqueue the new element
    elementCount++;

    elements[backindex] = newElement;

    backindex = (backindex + 1)%capacity;

    return true;
} 

//----------------------------------------------------------------------------------------------
   // Description: Removes (but does not return) the element at the "front" of this Queue 
   //              (not necessarily the "front" of its data structure).
   // Precondition: This Queue is not empty.
   // Exception: Throws EmptyDataCollectionException if this Queue is empty.   
   // Time Efficiency: O(1)
template<class ElementType>
void Queue<ElementType>::dequeue() throw(EmptyDataCollectionException)
{

    //return if queue is empty
    if(isEmpty())
        throw EmptyDataCollectionException("dequeue() called with empty queue.");

    //Dequeue(), remove the the element at frontindex
    elementCount--;
    frontindex = (frontindex + 1)%capacity;

    //Shrink capacity to if element count is 1/4 of capacity
    //New array is arranged so that frontindex is at position 0, and the corresponding backindex is set to 0 + elementcount.
    if(elementCount*4 < capacity && capacity > INITIAL_SIZE){
        ElementType * newElements = new ElementType[capacity/2];
        for(unsigned i = 0; i < elementCount; i++){
            newElements[i] = elements[(frontindex + i)%capacity];
        }
        delete[] elements;
        elements = newElements;
        capacity = capacity/2;
        frontindex = 0;
        backindex = elementCount;
    }

}

//----------------------------------------------------------------------------------------------
    // Description: Returns (but does not remove) the element at the "front" of this Queue
    //              (not necessarily the "front" of its data structure).
    // Precondition: Queue not empty
    // Exception: Throws EmptyDataCollectionException if this Queue is empty.
    // Time efficiency: (O(1))
template<class ElementType>
ElementType& Queue<ElementType>::peek() throw(EmptyDataCollectionException)
{
    if(isEmpty()){
        throw EmptyDataCollectionException("peek() called with empty queue.");
    }
    return elements[frontindex];
} 


//end of Queue.h


