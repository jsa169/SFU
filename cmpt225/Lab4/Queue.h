/* 
 * Queue.h
 *
 * Description: Array-based implementation of data collection Queue ADT.
 * 
 * Class invariants: FIFO or LILO
 * 
 * Inspired from the code in our textbook (Frank M. Carrano and Tim Henry)
 *
 * Date: June 2017
 */

#pragma once

#include "Patient.h"
#include "EmptyDataCollectionException.h"


class Queue {

private:
   static const int CAPACITY = 100; 
   
   Patient elements[CAPACITY]; // Array of queue items
   int front;                 // Index to front of queue
   int back;                  // Index to back of queue
   int elementCount;          // Number of elements currently in the queue
   
public:
   // Constructor
   Queue();
   // Copy constructor and destructor supplied by compiler
        
   // Description: Returns "true" is this queue is empty, otherwise "false".
   // Time Efficiency: O(1)
   bool isEmpty() const;
   
   // Description: Adds newElement to the "back" of this queue and 
   //              returns "true" if successful, otherwise "false".
   // Time Efficiency: O(1)
   bool enqueue(const Patient& newElement);
   
   // Description: Removes the element at the "front" of this queue and 
   //              returns "true" if successful, otherwise "false".
   // Precondition: This queue is not empty.
   // Time Efficiency: O(1)
   bool dequeue();

   // Description: Retrieves (but does not remove) the element at the  
   //              "front" of this queue and returns it.
   // Precondition: This queue is not empty.
   // Postcondition: This queue is unchanged.
   // Exceptions: Throws EmptyDataCollectionException if this queue is empty.
   // Time Efficiency: O(1)
   Patient peek() const throw(EmptyDataCollectionException);  
  
   // For Testing Purposes
   // Description: Prints the content of "this". 
   void printQueue() const;
      
}; // end Queue