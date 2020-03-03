/*
 * Patient.cpp
 * 
 * Class Description: Models a walk-in clinic patient.
 * Class Invariant: The care card number must have 10 digits.
 *                  The care card number cannot be modified.  
 *
 * Last modified on: Oct. 2019
 * Author: AL
 */

#include <iostream>
#include <string>
#include <locale>         // std::locale, std::isalpha
#include "Patient.h"

using namespace std;

// Default Constructor
// Description: Create a patient with a care card number of "0000000000".
// Postcondition: All data members set to "To be entered",
//                except the care card number which is set to "0000000000".
Patient::Patient() : name("To be entered"), address("To be entered"),
                   phone("To be entered"), email("To be entered") {

	setCareCard("0000000000");
	std::cout << "Patient::default constructor" << endl;   // For testing purposes ... and curiosity
}


// Parameterized Constructor
// Description: Create a patient with the given care card number.
// Postcondition: If aCareCard does not have SIZE_OF_CARECARD digits (10), then care card is set to "0000000000".
//                All other data members set to "To be entered".
Patient::Patient(string aCareCard) : name("To be entered"), address("To be entered"),
                                  phone("To be entered"), email("To be entered") {
  	setCareCard(aCareCard);
}

// Description: Create a patient with the given name, address, phone number, email and care card number.
// Postcondition: If aCareCard does not have 10 digits, then care card is set to "0000000000".
Patient::Patient(string aName, string anAddress, string aPhone, string anEmail, string aCareCard) : 
                 name(aName), address(anAddress), phone(aPhone), email(anEmail) {
                 	
  	setCareCard(aCareCard);
}

// Getters and setters
// Description: Returns patient's name.
string Patient::getName() const {
	return name;
}

// Description: Returns patient's address.
string Patient::getAddress() const {
	return address;
}

// Description: Returns patient's phone number.
string Patient::getPhone() const {
	return phone;
}

// Description: Returns patient's email.
string Patient::getEmail() const {
 	return email;
}

// Description: Returns patient's care card number.
string Patient::getCareCard() const {
	return careCard;
}

// Description: Sets the patient's name.
void Patient::setName(const string aName) {
	name = aName;
}

// Description: Sets the patient's address.
void Patient::setAddress(const string anAddress) {
	address = anAddress;
}

// Description: Sets the patient's phone number.
void Patient::setPhone(const string aPhone) {
	phone = aPhone;
}

// Description: Sets the patient's email.
void Patient::setEmail(const string anEmail) {
	email = anEmail;
}

// Description: Sets the patient's email - Private method
void Patient::setCareCard(const string aCareCard) {
	bool badCareCard = false;

	careCard = "0000000000";
	if (aCareCard.length() == SIZE_OF_CARECARD )
		for ( int digit = 0; !badCareCard && digit < SIZE_OF_CARECARD; digit++ )
			if ( !isdigit(aCareCard[digit]) ) badCareCard = true;

	if ( !badCareCard ) careCard = aCareCard;
  return;
}


// Overloaded Operators
// Description: Comparison operator. Compares "this" Patient object with "rhs" Patient object.
//              Returns true if both Patient objects have the same care card number.
bool Patient::operator == (const Patient & rhs) {

	return this->careCard == rhs.getCareCard();

} // end of operator ==


// Description: Greater than operator. Compares "this" Patient object with "rhs" Patient object.
//              Returns true if the care card number of "this" Patient object is > the care card
//              number of "rhs" Patient object.
bool Patient::operator > (const Patient & rhs) {

	return this->careCard > rhs.getCareCard();

} // end of operator >


// For testing purposes!
// Description: Prints the content of "this".
ostream & operator<<(ostream & os, const Patient & p) {

// Put your code here!
cout<<p.getName()<<", "<<p.getAddress()<<", "<<p.getPhone()<<", "<<p.getEmail()<<", "<<p.getCareCard()<<endl;
	     
	return os;
} // end of operator<<

// end of Patient.cpp