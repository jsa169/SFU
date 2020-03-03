/*
 * walkIn.cpp
 * 
 * Class Description: Models a walk-in clinic patient.
 * Class Invariant: Each patient has a unique care card number.
 *                  This care card number must have 10 digits.
 *                  This care card number cannot be modified. 
 *
 * Author: (For you to fill)
 * Date: (For you to fill)
 */

#include <iostream>
#include "List.h"
#include "Patient.h"
#include <string.h>

using namespace std;

int main(){
	List a = List();

	Patient three = Patient("1111111111");
	Patient four = Patient("2222222222");
	Patient five1 = Patient("3333333333");
	Patient five2 = Patient("5555555555");
	Patient five3 = Patient("6666666666");
	Patient five4 = Patient("7777777777");
	Patient five5 = Patient("8888888888");
	Patient five6 = Patient("9999999999");
	Patient five7 = Patient("4444444444");
	Patient five8 = Patient("0000000000");

	//Patient five9 = Patient("1234336814");
	//Patient five10 = Patient("1234336829");
	//Patient five11 = Patient("22343368");

	 a.insert(five2);
	
	 a.insert(five3);

	 a.insert(five4);
 
	 a.insert(five5);

	 a.insert(five6);

	 a.insert(five7);

	 a.insert(five8);

	//a.insert(five9);
	
	 a.insert(three);	

	 a.insert(four);

	 a.insert(five1);
	


	//a.insert(five10);
	 cout<<"working"<<endl;
	 a.printList();
	 cout<<a.getElementCount()<<a.getCapacity()<<endl;
	a.remove(five8);
	 cout<<"working"<<endl;

	//a.remove(five11);

	cout << "capacity is: " << a.getCapacity() << endl;
	cout << "Total patient is: " << a.getElementCount() << endl;

	a.printList();
	a.removeAll();

	cout << "capacity is: " << a.getCapacity() << endl;
	cout << "Total patient is: " << a.getElementCount() << endl;

}

