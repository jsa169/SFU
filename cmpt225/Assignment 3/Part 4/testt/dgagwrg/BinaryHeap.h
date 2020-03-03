/* 
 * BinaryHeap.h
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
//include statements

#include <iostream>
#include <math.h>
#include "EmptyDataCollectionException.h"
using namespace std;


//----------------------------------------------------------------------------------------------
template<class ElementType>
class BinaryHeap {
    private:
        static unsigned const INITIAL_SIZE = 7;
        ElementType * elements;  

        unsigned elementCount;  // number of elements in the BinaryHeap
        unsigned capacity;      // number of cells in the array

    public:

//----------------------------------------------------------------------------------------------
        // Description: Constructor
        BinaryHeap();

//----------------------------------------------------------------------------------------------
        //Description:Destructor
        //Post condition: Free all used memmory
        ~BinaryHeap();

//----------------------------------------------------------------------------------------------
        // Description: Returns "true" is this Binary Heap is empty, otherwise "false".
        // Postcondition:  The Binary Heap is unchanged by this operation.
        // Time Efficiency: O(1)
        bool isEmpty() const;

//----------------------------------------------------------------------------------------------
        // Description: Inserts newElement in this Binary Heap and 
        //              returns "true" if successful, otherwise "false".
        // Time Efficiency: O(log2 n)
        bool insert(ElementType& newElement);

//---------------------------------------------------------------------------------------------- 


        // Description: Removes (but does not return) the element located at the root.
        // Precondition: This Binary Heap is not empty.
        // Exception: Throws EmptyDataCollectionException if Binary Heap is empty.
        // Time Efficiency: O(log2 n)
        void remove() throw(EmptyDataCollectionException);
//----------------------------------------------------------------------------------------------
        // Description: Returns (but does not remove) the element located at the root.
        // Precondition: This Binary Heap is not empty.   
        // Exception: Throws EmptyDataCollectionException if Binary Heap is empty.
        // Time Efficiency: O(1)
        ElementType& retrieve() throw(EmptyDataCollectionException);
//----------------------------------------------------------------------------------------------
        void printBinaryHeap();
//----------------------------------------------------------------------------------------------
        void reHeapUp(unsigned toBeReheaped);
//----------------------------------------------------------------------------------------------   
        void reHeapDown(unsigned toBeReheaped);     
};

//----------------------------------------------------------------------------------------------
template<class ElementType>
BinaryHeap<ElementType>::BinaryHeap() : elementCount(0), capacity(INITIAL_SIZE) {
    elements = new ElementType[INITIAL_SIZE];

} 

//----------------------------------------------------------------------------------------------
    //Description:Destructor
    //Post condition: Free all used memmory
template<class ElementType>
BinaryHeap<ElementType>::~BinaryHeap(){
    delete[] elements;
}

//----------------------------------------------------------------------------------------------

   // Description: Returns "true" is this Binary Heap is empty, otherwise "false".
   // Postcondition:  The Binary Heap is unchanged by this operation.
   // Time Efficiency: O(1)
template<class ElementType>
bool BinaryHeap<ElementType>::isEmpty() const {
    return elementCount == 0;
} 

//----------------------------------------------------------------------------------------------
   // Description: Inserts newElement in this Binary Heap and 
   //              returns "true" if successful, otherwise "false".
   // Time Efficiency: O(log2 n)
template<class ElementType>
bool BinaryHeap<ElementType>::insert(ElementType& newElement) {

    if(elementCount >= capacity){
        ElementType * newElements = new ElementType[capacity*2];
        for(unsigned i = 0; i<elementCount; i++){
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = capacity*2;
    }  
    //enBinaryHeap the new element

    elementCount++;
    elements[elementCount-1] = newElement;
    reHeapUp(elementCount-1);
    
    return true;
}


//----------------------------------------------------------------------------------------------

   // Description: Removes (but does not return) the element located at the root.
   // Precondition: This Binary Heap is not empty.
   // Exception: Throws EmptyDataCollectionException if Binary Heap is empty.
   // Time Efficiency: O(log2 n)
template<class ElementType>
void BinaryHeap<ElementType>::remove() throw(EmptyDataCollectionException)
{

    //return if BinaryHeap is empty
    if(isEmpty())
        throw EmptyDataCollectionException("remove() called with empty BinaryHeap.");

    if(elementCount == 1){
        ElementType * newElements = new ElementType[capacity];
        delete[] elements;
        elements = newElements;
        elementCount = 0;
        return;
    }

    elements[0] = elements[elementCount-1];
    elementCount--;

    if(elementCount*4 < capacity && capacity > INITIAL_SIZE){
        ElementType * newElements = new ElementType[capacity/2];
        for(unsigned i = 0; i < elementCount; i++){
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = capacity/2;
    }

    reHeapDown(0);

}

//----------------------------------------------------------------------------------------------
   // Description: Returns (but does not remove) the element located at the root.
   // Precondition: This Binary Heap is not empty.   
   // Exception: Throws EmptyDataCollectionException if Binary Heap is empty.
   // Time Efficiency: O(1)
template<class ElementType>
ElementType& BinaryHeap<ElementType>::retrieve() throw(EmptyDataCollectionException)
{
    if(isEmpty()){
        throw EmptyDataCollectionException("retrieve() called with empty BinaryHeap.");
    }
    return elements[0];
} 

//----------------------------------------------------------------------------------------------
   // Description: Prints out the binary heap.   
   // Time Efficiency: O(n)

template<class ElementType>
void BinaryHeap<ElementType>::printBinaryHeap(){
    int count = 0;

    for(int i = 1; i <= elementCount; i = i*2){
      for (int j = 0; j< i; j++){
        cout << elements[count] <<" ";
        count++;
        if (count >= elementCount) break;
      }
      cout<<endl;
    }
    cout<<"element count is: " << elementCount<<endl<<"------------------"<<endl;


}

//----------------------------------------------------------------------------------------------
   // Description: Re-sorts binary heap into minimum binary heap recursively.
   // Time Efficiency: O(log2 n)
template<class ElementType>
void BinaryHeap<ElementType>::reHeapUp(unsigned toBeReheaped){
        ElementType temp;
        if(toBeReheaped > 0){
            unsigned indexOfParent = floor((toBeReheaped-1) / 2);
            if(elements[toBeReheaped] <= elements[indexOfParent]){
                temp = elements[indexOfParent];
                elements[indexOfParent] = elements[toBeReheaped];
                elements[toBeReheaped] = temp;
                reHeapUp(indexOfParent);
            }
        }

    }

//----------------------------------------------------------------------------------------------
   // Description: Re-sorts binary heap into minimum binary heap recursively.
   // Time Efficiency: O(log2 n)
template<class ElementType>
void BinaryHeap<ElementType>::reHeapDown(unsigned toBeReheaped) {
    unsigned left = 2*toBeReheaped + 1;
    unsigned right = 2*toBeReheaped + 2;
    unsigned minChild;
    unsigned temp;
    if(left < elementCount){
        if((left) == elementCount - 1) minChild = left;
        else{

            if(elements[left] <= elements[right]) minChild = left;
            else minChild = right;
        }

        if((elements[toBeReheaped] > elements[minChild])){

            temp = elements[toBeReheaped];
            elements[toBeReheaped] = elements[minChild];
            elements[minChild] = temp;
            reHeapDown(minChild);
        }
    }
}


//end of BinaryHeap.h