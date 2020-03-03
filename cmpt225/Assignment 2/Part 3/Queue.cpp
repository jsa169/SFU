/* 
 * Queue.cpp
 *
 * Description: Queue data collection ADT class.
 *              Implementation of an int sequence with enqueue/dequeue ...
 * Class Invariant: ... in FIFO order
 *
 * Author:
 * Date:
 */
 
#include <iostream>
#include "Queue.h"
#include <assert.h>
using namespace std;


// Description: Constructor
Queue::Queue() : elementCount(0), capacity(INITIAL_SIZE), frontindex(0), backindex(0) {
	elements = new int[INITIAL_SIZE];
} 


// Description: Inserts newElement at the back (O(1))
void Queue::enqueue(int newElement) {

	if(backindex+1 >= capacity){
		int * newElements = new int[capacity*2];
        copy(elements,elements+backindex, newElements);
        delete[] elements;
        elements = newElements;
        capacity = capacity*2;
	}

    elementCount++;
    elements[backindex] = newElement;
    backindex = (backindex + 1)%capacity;
    for(int i = frontindex; i<backindex; i++){
        cout<<elements[i]<<" ";
    }
    cout<<endl;
} 


// Description: Removes the frontmost element (O(1))
// Precondition: Queue not empty
void Queue::dequeue() {
    if(elementCount == 0)
        return;
    elementCount--;
    frontindex = (frontindex + 1)%capacity;
    for(int i = frontindex; i<backindex; i++){
        cout<<elements[i]<<" ";
    }
    cout<<endl;


    if(elementCount*4 < capacity && capacity > INITIAL_SIZE){
        int * newElements = new int[capacity/2];
        for(unsigned i = 0; i < elementCount; i++){
            newElements[i] = elements[i+frontindex];
        }
        delete[] elements;
        elements = newElements;
        capacity = capacity/2;
        frontindex = 0;
        backindex = frontindex+elementCount;
    }

}


// Description: Returns a copy of the frontmost element (O(1))
// Precondition: Queue not empty
int Queue::peek() const {
    if(elementCount == 0){
        return;
    }
    return elements[frontindex];
} 


// Description: Returns true if and only if queue empty (O(1))
bool Queue::isEmpty() const {
    return elementCount == 0;
} 




