/* 
 * Queue.cpp
 *
 * Description: Array-based implementation of data collection Queue ADT.
 * 
 * Class invariants: FIFO or LILO
 * 
 * Inspired from the code in our textbook (Frank M. Carrano and Tim Henry)
 *
 * Date: June 2017
 */

#include <iostream>
#include "Queue.h"  // Header file


// Constructor
Queue::Queue() : front(0), back(CAPACITY - 1), elementCount(0)
{
} // end default constructor


// Copy constructor and destructor supplied by compiler


// Description: Returns "true" is this queue is empty, otherwise "false".
// Time Efficiency: O(1)
bool Queue::isEmpty() const
{
   return elementCount == 0;
} // end isEmpty

// Description: Adds newElement to the "back" of this queue and 
//              returns "true" if successful, otherwise "false".
// Time Efficiency: O(1)
bool Queue::enqueue(const Patient& newElement)
{
   bool queuedOK = false;
   if (elementCount < CAPACITY)
   {
      // Queue has room for another item
      back = (back + 1) % CAPACITY;
      elements[back] = newElement;
      elementCount++;
      queuedOK = true;
   } // end if
   
   return queuedOK;
} // end enqueue


// Description: Removes the element at the "front" of this queue and 
//              returns "true" if successful, otherwise "false".
// Precondition: This queue is not empty.
// Time Efficiency: O(1)
bool Queue::dequeue()
{
   // Some code
   
   return true;
} // end dequeue


// Description: Retrieves (but does not remove) the element at the  
//              "front" of this queue and returns it.
// Precondition: This queue is not empty.
// Postcondition: This queue is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this queue is empty.
// Time Efficiency: O(1)
Patient Queue::peek() const throw(EmptyDataCollectionException)
{
   // Enforce precondition
   if (isEmpty())
      throw EmptyDataCollectionException("peek() called with empty queue.");

   // Queue is not empty; return front
   return elements[front];
} // end peek

// For Testing Purposes
// Description: Prints the content of "this". 
void Queue::printQueue() const { 
   cout << "Printing the queue from front = " << front << " to back = " << back << endl;
   for ( int i = front; i <= back; i++)
      cout << elements[i];
   cout << endl;
} // end of printQueue

// End of implementation file.