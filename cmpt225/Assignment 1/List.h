/*
 * List.h
 * 
 * Class Description: List data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - This list is sorted after every insertion and removing
 *
 * Author: Jichuan Shi	
 * Date: 09/16/2019
 */

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// #Include statements

#pragma once

#include <string>
#include "Patient.h"

using namespace std;

//--------------------------------------------------------------------------------------------
//Defining class List
class List  {

private:

	int max_ele;					   // MAX_ELEMENTS
	Patient * data;      		       // Data structure of element with capacity of MAX_ELEMENTS
	int elementCount;                  // Current element count in element array
	int capacity;                      // Actual maximum capacity of element array   
//	void sort(); ***Saved for future use

//--------------------------------------------------------------------------------------------
public:
	
//--------------------------------------------------------------------------------------------
	// Default constructor
	List();

//--------------------------------------------------------------------------------------------
//Getters
	// Description: Returns the total element count currently stored in List.
	int  getElementCount() const;

	// Description: Returns the capacity of the List.
	int getCapacity()const;

//--------------------------------------------------------------------------------------------

	// Description: Insert an element. 
	//				Return true if new element is inserted, 
	//              otherwise return false.
	// Precondition: newElement must not already be in data collection.  
	// Postcondition: newElement inserted and elementCount has been incremented.  
	//				  List is sorted
	bool insert(const Patient& newElement);

//--------------------------------------------------------------------------------------------
	
	// Description: Remove an element. 
	//              Return true if an elment is removed, 
	//              otherwise return false.
	// Postcondition: toBeRemoved is removed and elementCount has been decremented.	
	bool remove( const Patient& toBeRemoved );

//--------------------------------------------------------------------------------------------	
	
	// Description: Remove all elements from List.
	void removeAll();

 //--------------------------------------------------------------------------------------------  
	
	// Description: Search for target element.
	//              Returns a pointer to the element if found,
	//              otherwise, returns NULL.
	Patient* search(const Patient& target);

//--------------------------------------------------------------------------------------------	
	
	// Description: Prints all elements stored in List by descending order of care card numbers.
	void printList();

}; // end List.h