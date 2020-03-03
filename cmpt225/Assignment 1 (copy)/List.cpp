/*
 * List.cpp
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

#include "List.h"
#include <string.h>
#include <iostream>
#include "Patient.h"
#include<stdlib.h>

using namespace std;

//--------------------------------------------------------------------------------------------
// Default constructor
List::List(){
	this->max_ele = 5;
	this->data = new Patient[max_ele];
	this->elementCount = 0;
	this->capacity = 5;
}

//--------------------------------------------------------------------------------------------
//Getters
	// Description: Returns the total element count currently stored in List.
int List::getElementCount() const{
	return elementCount;
}

	// Description: Returns the total element count currently stored in List.
int List::getCapacity() const{
	return capacity;
}

//--------------------------------------------------------------------------------------------

	// Description: Insert an element. 
	//				Return true if new element is inserted, 
	//              otherwise return false.
	// Precondition: newElement must not already be in data collection.  
	// Postcondition: newElement inserted and elementCount has been incremented.  
	//				  List is sorted 
bool List::insert(const Patient& newElement){
	if(elementCount >= capacity){
		Patient * temp = new Patient[capacity*2];
		std::copy(data, data + elementCount, temp);
		delete[] data;
		data = temp;
		capacity = capacity*2;
		max_ele = max_ele*2;
	}	//Expanding the array

		//check if the element already exist Return false, if element is found
	if (search(newElement) != NULL){
		return false;
	}		
	else{
		Patient toBeInserted = newElement;
		int insertIndex = 0;

		//Locate the index of insertion
		for(int i = 0; i <= elementCount; i++){	
			if (toBeInserted > data[i])
				break;
			else
				insertIndex ++ ;
		}

		//Shift every patient after the insertion point 1 index to the back,
		//ie, insertion point 3, shift index 5->6, 4->5, 3->4
		for(int i = elementCount; i > insertIndex; i--){
			data[i]=data[i-1];
		}

		//Insert the patient at the correct location, the list is sorted after insertion
		data[insertIndex] = newElement;

		this->elementCount++;
		return true;

	}	//end of else statement

}	//end of insert method

//--------------------------------------------------------------------------------------------

	// Description: Remove an element. 
	//              Return true if an elment is removed, 
	//              otherwise return false.
	// Postcondition: toBeRemoved is removed and elementCount has been decremented.	
bool List::remove( const Patient& toBeRemoved ){
	
	//Return false if element to be removed is not found
	if (this->search(toBeRemoved) == NULL){
		return false;
	}
	else{
		//Create new array
		Patient * newdata = new Patient[capacity];
		int count = 0;

		//Copy every patient to the new array until patient to be removed
		for (int i = 0; i < elementCount; i ++){

			if(data[i] == toBeRemoved){

				break;
			}
			newdata[i] = data[i];
			count++;
		}

		//Skip patient to be remove, and copy every patient after to the new array
		for (int i = count; i< elementCount-1; i++){
			newdata[i] = data[i+1];
		}

		//Deallocate old array and set pointer to new array
		delete[] data;

		this->data = newdata;
		elementCount--;
		return true;
	}

}

//--------------------------------------------------------------------------------------------	

	// Description: Remove all elements.
void List::removeAll(){
	Patient * newdata = new Patient[capacity];
	delete[] data;
	this->data = newdata;
	this->elementCount = 0;

}

//--------------------------------------------------------------------------------------------
   
	// Description: Search for target element.
	//              Returns a pointer to the element if found,
	//              otherwise, returns NULL.
Patient* List::search(const Patient& target){
	for (int i = 0; i < this->elementCount; i++){
		if (this->data[i] == target)
			return &data[i];
	}
	return NULL;
}

//--------------------------------------------------------------------------------------------
	
// Description: Prints all elements stored in List by descending order of care card numbers.
void List::printList(){

	for (int i = 0; i < this->elementCount; i++){
		cout << this->data[i];
	}

}






















//--------------------------------------------------------------------------------------------
//Sort the list ***Saved for future use
/*void List::sort(){
	Patient * temp = new Patient[capacity];
	int max;
	for(int i = 0; i < elementCount; i++){
		max = i;
		for (int j = i+1; j < elementCount; j++){

			if(data[j] > data[max]){
				max = j;
			}
		}

		temp[0] = data[i];
		data[i] = data[max];
		data[max]=temp[0];
	}
	delete[]temp;
}*/