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

	Patient three = Patient("4111111111");
	Patient four = Patient("4222222222");
	Patient five1 = Patient("4333333333");
	Patient five2 = Patient("4555555555");
	Patient five3 = Patient("4666666666");
	Patient five4 = Patient("4777777777");
	Patient five5 = Patient("5888888888");
	Patient five6 = Patient("5999999999");
	Patient five7 = Patient("5444444444");
	Patient five8 = Patient("5000000000");

	Patient five9 = Patient("5234336814");
	Patient five10 = Patient("5234336829");
	Patient five11 = Patient("22343368");
	 a.insert(five2);
	cout << "capacity is: " << a.getCapacity() << endl;
	cout << "Total patient is: " << a.getElementCount() << endl;	 

	a.insert(five3);
	cout << "capacity is: " << a.getCapacity() << endl;
	cout << "Total patient is: " << a.getElementCount() << endl;

	 a.insert(five4);
	cout << "capacity is: " << a.getCapacity() << endl;
	cout << "Total patient is: " << a.getElementCount() << endl;
	 a.insert(five5);
	cout << "capacity is: " << a.getCapacity() << endl;
	cout << "Total patient is: " << a.getElementCount() << endl;
	 a.insert(five6);
	cout << "capacity is: " << a.getCapacity() << endl;
	cout << "Total patient is: " << a.getElementCount() << endl;
	 a.insert(five7);
	cout << "capacity is: " << a.getCapacity() << endl;
	cout << "Total patient is: " << a.getElementCount() << endl;
	 a.insert(five8);

	a.insert(five9);

	 a.insert(three);	

	 a.insert(four);

	 a.insert(five1);
	


	a.insert(five10);
	 cout<<"working"<<endl;
	 a.printList();
	cout << "capacity is: " << a.getCapacity() << endl;
	cout << "Total patient is: " << a.getElementCount() << endl;	a.remove(five8);
	 cout<<"working"<<endl;

	a.remove(five11);

	cout << "capacity is: " << a.getCapacity() << endl;
	cout << "Total patient is: " << a.getElementCount() << endl;

		cout<<"works"<<endl;

	List b = List(a);

	a.printList();
	a.removeAll();

	cout << "capacity is: " << a.getCapacity() << endl;
	cout << "Total patient is: " << a.getElementCount() << endl;

	cout<<"end"<<endl;
	b.printList();
	cout << "capacity is: " << b.getCapacity() << endl;
	cout << "Total patient is: " << b.getElementCount() << endl;
}

