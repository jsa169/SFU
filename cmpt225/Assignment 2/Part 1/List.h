/*
 * List.h
 * 
 * Class Description: List data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - Elements are kept in descending sorted order of element's search key.
 *
 * Author: (For you to fill)
 * Date: (For you to fill)
 */

#pragma once

// You can add #include statements if you wish.
#include <string>
#include "Patient.h"

using namespace std;


class List  {

private:

Patient * data[10];
int elementCount[11];                 // Current element count in element array
int capacity[11];  

public:

/* 
 * You can add more methods to this interface, 
 * but you cannot remove the methods below 
 * nor can you change their prototype.
 * 
 */

	// Default constructor
	List();

	// Copy constructor
	List(const List& lst);

	// Destructor
	~List();

	// Description: Returns the total element count currently stored in List.
	int getElementCount() const;

	int getCapacity() const;

	int getFirstNumber(const Patient& Patient);

	// Description: Insert an element.
	// Precondition: newElement must not already be in data collection.     
	// Postcondition: newElement inserted and the appropriate elementCount has been incremented.  
	bool insert(const Patient& newElement);

	// Description: Remove an element. 
	// Postcondition: toBeRemoved is removed and the appropriate elementCount has been decremented.
	bool remove( const Patient& toBeRemoved );
	
	// Description: Remove all elements.
	void removeAll();
   
	// Description: Search for target element.
	//              Returns a pointer to the element if found,
	//              otherwise, returns NULL.
	Patient* search(const Patient& target);
	
	// Description: Prints all elements stored in List.
	void printList();

}; // end List.h  