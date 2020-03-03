/*
 * Patient.cpp
 * 
 * Class Description: Models a walk-in clinic patient.
 * Class Invariant: Each patient has a unique care card number.
 *                  This care card number must have 10 digits.
 *                  This care card number cannot be modified. 
 *
 * Author: Jichuan Shi	
 * Date: 06/16/2019
 */

//--------------------------------------------------------------------------------------------
// #Include statements
#include <iostream>
#include <string.h>
#include "Patient.h"

using namespace	std;

//--------------------------------------------------------------------------------------------
// Default Constructor
// Description: Create a patient with a care card number of "0000000000". 
// Postcondition: All data members set to "To be entered", 
//                except the care card number which is set to "0000000000".       
Patient::Patient() {
	careCard = "0000000000";
	name = "To be entered";
	address = "To be entered";
	phone = "To be entered";
	email = "To be entered";
}

//--------------------------------------------------------------------------------------------
// Parameterized Constructor
// Description: Create a patient with the given care card number.
// Postcondition: If aCareCard does not have 10 digits, then care card is set to "0000000000".
//                All other data members set to "To be entered".
Patient::Patient(string aCareCard) {
	int length = aCareCard.size();

	//Count the number of non int in aCareCard
	int count = 0;
	for(int i = 0; i < length; i++){
		if(isdigit(aCareCard[i]) != true)
			count++;
	}


	if ((length != 10) || (count != 0))
		careCard = "0000000000";
	else
		careCard = aCareCard;
		
	name = "To be entered";
	address = "To be entered";
	phone = "To be entered";
	email = "To be entered";
}

//--------------------------------------------------------------------------------------------
	// Parameterized Constructor
	// Description: Create a patient with the given care card number, name, address, phone and email .
	// Postcondition: If aCareCard does not have 10 digits, then care card is set to "0000000000".
	//                All other data members set to "To be entered".
Patient::Patient(string aCareCard, string anEmail, string aName, string anAddress, string aPhone){
	int length = aCareCard.size();

	//Count the number of non int in aCareCard
	int count = 0;
	for(int i = 0; i < length; i++){
		if(isdigit(aCareCard[i]) != true)
			count++;
	}

	if ((length != 10) || (count != 0))		
		careCard = "0000000000";
	else
		careCard = aCareCard;

//Set the email, phone, name and address according to the user input, use "to be entered"
//if the user input nothing	
	if (anEmail == "")
		email = "To be entered";
	else
		email = anEmail;

	if (aName == "")
		name = "To be entered";
	else
		name = aName;

	if(aPhone == "")
		phone = "To be entered";
	else
		phone = aPhone;
	
	if(anAddress == "")
		address = "To be entered";		
	else
		address = anAddress;

}

// All other parameterized constructors -> You need to implement these methods.

//--------------------------------------------------------------------------------------------
//Getters
string Patient::getName()const{	// Description: Returns patient's name.
	return name;
}

string Patient::getAddress()const{	// Description: Returns patient's address.
	return address;
}

string Patient::getPhone()const{	// Description: Returns patient's phone.
	return phone;
}

string Patient::getEmail()const{	// Description: Returns patient's email.
	return email;
}

string Patient::getCareCard()const{	// Description: Returns patient's care card.
	return careCard;
}

//--------------------------------------------------------------------------------------------

//Setter
void Patient::setName(const string aName){	// Description: Sets the patient's name.
	name = aName;
}

void Patient::setAddress(const string anAddress){	// Description: Sets the patient's address.
	address = anAddress;
}

void Patient::setPhone(const string aPhone){	// Description: Sets the patient's phone.
	phone = aPhone;
}

void Patient::setEmail(const string anEmail){	// Description: Sets the patient's email.
	email = anEmail;
}

//--------------------------------------------------------------------------------------------
// Overloaded Operators

// Description: Comparison operator. Compares "this" Patient object with "rhs" Patient object.
//              Returns true if both Patient objects have the same care card number.
bool Patient::operator == (const Patient & rhs) {
	
	// Compare both Patient objects
	return this->careCard == rhs.getCareCard();	
} 

//--------------------------------------------------------------------------------------------
// Description: Greater than operator. Compares "this" Patient object with "rhs" Patient object.
//              Returns true if the care card number of "this" Patient object is > the care card 
//              number of "rhs" Patient object
bool Patient::operator > (const Patient & rhs) {
	
	// Compare both Patient objects
	return this->careCard > rhs.getCareCard();	
}

//---------------------------------------------------------
// Description: Prints the content of "this".
ostream & operator<<(ostream & os, const Patient & p) {
	
	os << p.careCard << " - Patient: " << p.name << ", "
	   << p.address << ", " << p.phone << ", " << p.email << endl;  
	     
	return os;

} // end of operator<<

// end of Patient.cpp