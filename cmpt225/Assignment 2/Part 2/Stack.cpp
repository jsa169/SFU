/* 
 * Stack.cpp
 *
 * Description: Stack data collection ADT class.
 *              Implementation of an int sequence with push/pop ...
 * Class Invariant: ... in a LIFO order
 *
 * Author:
 * Date:
 */
 #include "Stack.h"
 #include <iostream>

 using namespace std; 

        // Description: Constructor
        // Postcondition: Stack is empty
Stack::Stack(){

    head = NULL;
    tail = NULL;
}


        // Description: Destructor 
        // Postcondition: All memory released
Stack::~Stack(){

    if(head != NULL){

        StackNode * current = head;
        StackNode * next;

        while(current != NULL){
            next = current->next;
            delete current;
            current = next;
        }
    }
}


        // Description: Insert newElement to the top of the stack. 
void Stack::push(int newElement){
    StackNode * newNode = new StackNode();
    newNode->data = newElement;
    newNode->next = NULL;

    if(head == NULL){
        head = newNode;
        tail = newNode; 
    }else{
        tail->next = newNode;
        tail = newNode;
    }

}


        // Description: Remove and return element at the top of the stack.
        // Precondition: Stack is not empty   
int Stack::pop(){

    if(head == NULL){
        return -99999;
    }
    if(head->next == NULL){
        int data = tail->data;
        delete head;
        head = NULL;
        tail = NULL;
        return data;
    }

    int data = tail->data; 

    StackNode * current = head;
    while(current->next->next != NULL){
        current = current -> next;
    }
    current->next = NULL;

    delete tail;

    tail = current;

    return data;
}


        // Description: Return the topmost element of the stack.
        // Precondition: Stack is not empty   
int Stack::peek() const{
    if(head == NULL){
        return -99999;
    }

    return tail->data;


}


        // Description: Is stack empty? 
bool Stack::isEmpty() const{
    if(head == NULL)
        return true;
    return false;

}


