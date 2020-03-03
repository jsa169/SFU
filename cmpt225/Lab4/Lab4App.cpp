/*
 * test.cpp - Lab 4
 * 
 * Class Description: Test Driver for Patient class
 *
 * Modified on: Oct. 2019
 * Author: AL
 */

#include <iostream>
#include <sstream>
#include "Queue.h"
#include "Patient.h"
#include "EmptyDataCollectionException.h"

using namespace std;


int main () { 

  // Create an empty queue bankQueue
  Queue* aQueue = new Queue();
  string aLine = "";
  string carecard = "";
  string name = "";
  string address = "";
  string phone = "";  
  string email = "";
  Patient* newPatient = NULL;

  cout << "\nTest Driver - Start" << endl << endl;
  // Create and add arrival events to aEventQueue

  Patient peekedPatient;
  try {
    cout << "Peeking before enqueuing:" << endl;
    peekedPatient = aQueue->peek();
    cout << "Now, let's have a look at the peeked Patient:" << endl;  
    cout << peekedPatient << endl;
  }catch ( EmptyDataCollectionException & anException ) {
    cout << "peeking() unsuccessful because " << anException.what() << endl;
    // Place recovery code here!
  }

  while(getline(cin >> ws, aLine)) {   // while (there is data)
      stringstream ss(aLine);
      ss >> carecard >> name >> address >> phone >> email;      
      cout << "Read: " << carecard << ", " << name << ", " << address << ", " << phone << ", " <<  email << endl;  
      newPatient = new Patient(name, address, phone, email, carecard); 
      if ( !aQueue->enqueue(*newPatient) )  return 1;
      cout << *newPatient << endl;
  }

  try {
  cout << "Peeking after enqueuing:" << endl;
  peekedPatient = aQueue->peek();
  cout << "Now, let's have a look at the peeked Patient:" << endl;  
  cout << peekedPatient << endl;
}
catch ( EmptyDataCollectionException&anException ) {
  cout << "peeking() unsuccessful because " << anException.what() << endl;
  // Place recovery code here!
}

 
  aQueue->printQueue();

  cout << "Test Driver - End" << endl << endl;
  return 0;
}