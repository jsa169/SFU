/*
 * test.cpp
 *
 * Description: Driver program for testing our List ADT class.
 *              More specifically, for testing linked list copy and destructor.
 *
 * Creation Date:
 * Author:
 */
#include <iostream>
#include "List.h"


using namespace std;

int main () {
List ls1;
    
	/* Test Case */
	cout << "Adding 1,2,3 to the first List object." << endl;
	ls1.add(1);
	ls1.add(2);
	ls1.add(3);
	cout << endl << "Printing the first List object." << endl;
	ls1.printList();
	cout << endl << "Does it contain {1,2,3}?" << endl;
	cout << endl << "Make a copy of the List object." << endl;
	List ls2(ls1);
	cout << endl << "Print second List object." << endl;
	ls2.printList();
	cout << endl << "Does it contain {1,2,3}?" << endl;
	cout << endl << "Add 4,5,6 to the first List object." << endl;
	ls1.add(4);
	ls1.add(5);
	ls1.add(6);
	cout << endl << "Print first List object." << endl;
	ls1.printList();
	cout << endl << "Does it contain {1,2,3,4,5,6}?" << endl;
	cout << endl << "Print second List object: (what does it contain?)." << endl;
	ls2.printList();
	cout << endl << "If it was shallow copied, it should contain: {1,2,3,4,5,6}.";
	cout << endl << "If it was deep copied, it should contain: {1,2,3}." << endl;	
	cout << endl;

  return 0;
}
