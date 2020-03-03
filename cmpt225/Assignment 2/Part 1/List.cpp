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
#include "List.h"
#include <iostream> 

using namespace std;


	// Default constructor
List::List(){
	elementCount[10] = 0;
	capacity[10] = 50;
	for (int i = 0; i < 10; i++){
		data[i] = new Patient[5];
		elementCount[i] = 0;
		capacity[i] = 5;
	}
}
	// Copy constructor
List::List(const List& lst){
	elementCount[10] = lst.elementCount[10];
	capacity[10] = lst.capacity[10];
		
	for(int i = 0; i < 10; i++){		
		elementCount[i] = lst.elementCount[i];
		capacity[i] = lst.capacity[i];
		
		data[i] = new Patient[capacity[i]];
		for(int j = 0; j < elementCount[i]; j++){
			data[i][j] = lst.data[i][j];
		}

		//copy(lstdata,lstdata+lst.getElementCount(i), data[i]);
	}
	
	
}

	// Destructor
List::~List(){
	for(int i = 0; i < 10; i++){
		delete[] data[i];
	}
}

	// Description: Returns the total element count currently stored in List.
int List::getElementCount() const{
	return elementCount[10];
}

int List::getCapacity() const{
	return capacity[10];
}

int List::getFirstNumber(const Patient& p){
	int firstNumber = p.getCareCard()[0] - '0';
	return firstNumber;
}

	// Description: Insert an element.
	// Precondition: newElement must not already be in data collection.     
	// Postcondition: newElement inserted and the appropriate elementCount has been incremented.  
bool List::insert(const Patient& newElement){

	int firstNumber = this->getFirstNumber(newElement);
	if(elementCount[firstNumber] >= capacity[firstNumber]){

		Patient * temp = new Patient[capacity[firstNumber]*2];

		copy(data[firstNumber], data[firstNumber] + elementCount[firstNumber], temp);

		delete[] data[firstNumber];

		data[firstNumber] = temp;
		capacity[10] = capacity[10]+capacity[firstNumber];
		capacity[firstNumber] = capacity[firstNumber]*2;

	}

	if (search(newElement) != NULL){

		return false;
	}else{

		Patient toBeInserted = newElement;
		int insertIndex = 0;

		for(int i = 0; i < elementCount[firstNumber]; i++){
			if(toBeInserted > data[firstNumber][i])
				break;
			else
				insertIndex ++;
		}

		for(int i = elementCount[firstNumber]; i > insertIndex; i--){
			data[firstNumber][i] = data[firstNumber][i-1];
		}

		data[firstNumber][insertIndex] = newElement;

		elementCount[firstNumber]++;
		elementCount[10]++;
		return true;
	}

}

	// Description: Remove an element. 
	// Postcondition: toBeRemoved is removed and the appropriate elementCount has been decremented.
bool List::remove( const Patient& toBeRemoved ){
	if (this->search(toBeRemoved) == NULL){
		return false;
	}else{
		int firstNumber = this->getFirstNumber(toBeRemoved);

		Patient * newdata = new Patient[capacity[firstNumber]];
		int count = 0;

		for (int i = 0; i < elementCount[firstNumber]; i++){
			if(data[firstNumber][i] == toBeRemoved)
				break;

			newdata[i] = data[firstNumber][i];
			count++;
		}

		for(int i = count; i < elementCount[firstNumber]-1; i++){
			newdata[i] = data[firstNumber][i+1];
		}

		delete[] data[firstNumber];
		data[firstNumber]=newdata;
		elementCount[firstNumber]--;
		elementCount[10]--;
		return true;
	}
}	
	// Description: Remove all elements.
void List::removeAll(){
	for (int i = 0; i < 10; i++){
		Patient * newdata = new Patient[capacity[i]];
		delete[] data[i];
		data[i] = newdata;
		elementCount[i] = 0;
	}
	elementCount[10] = 0;
}
   
	// Description: Search for target element.
	//              Returns a pointer to the element if found,
	//              otherwise, returns NULL.
Patient* List::search(const Patient& target){
	int firstNumber = this->getFirstNumber(target);

	for(int i = 0; i < elementCount[firstNumber]; i++){
		
		if(data[firstNumber][i] == target)
			return &data[firstNumber][i];
		
	}
	return NULL;
}
	
	// Description: Prints all elements stored in List.
void List::printList(){
	for(int i = 0; i < 10; i++){
		for (int j = 0; j < elementCount[i]; j++){
			cout << data[i][j];
		}
	}
}

 // end List.h  