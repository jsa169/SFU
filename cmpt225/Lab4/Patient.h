/*
 * Patient.h
 * 
 * Class Description: Models a walk-in clinic patient.
 * Class Invariant: The care card number must have 10 digits.
 *                  The care card number cannot be modified. 
 *
 * Author: AL
 * Date: Last modified: Sept. 2019
 */

#pragma once

#include <string>

using namespace std;


class Patient {
	
private:

	static const int SIZE_OF_CARECARD = 10;

	string name;                
	string address;          
	string phone;
	string email;
	string careCard;

	// Description: Sets the patient's email - Private method
	void setCareCard(const string aCareCard);

public:

	// Default Constructor
	// Description: Create a patient with a care card number of "0000000000". 
	// Postcondition: All data members set to "To be entered", 
	//                except the care card number which is set to "0000000000".       
	Patient();

	// Parameterized Constructors
	// Description: Create a patient with the given care card number.
	// Postcondition: If aCareCard does not have 10 digits, then care card is set to "0000000000".
	//                All other data members set to "To be entered".
	Patient(string aCareCard);

	// Description: Create a patient with the given name, address, phone number, email and care card number.
	// Postcondition: If aCareCard does not have 10 digits, then care card is set to "0000000000".
	Patient(string aName, string anAddress, string aPhone, string anEmail, string aCareCard);

	// Getters and setters
	// Description: Returns patient's name.
	string getName() const;

	// Description: Returns patient's address.
	string getAddress() const;

	// Description: Returns patient's phone.
	string getPhone() const;

	// Description: Returns patient's email.
	string getEmail() const;
	
	// Description: Returns patient's care card.
	string getCareCard() const;

	// Description: Sets the patient's name.
	void setName(const string aName);

	// Description: Sets the patient's address.
	void setAddress(const string anAddress);

	// Description: Sets the patient's phone.
	void setPhone(const string aPhone);

	// Description: Sets the patient's email.
	void setEmail(const string anEmail);

	// Overloaded Operators
	// Description: Comparison operator. Compares "this" Patient object with "rhs" Patient object.
	//              Returns true if both Patient objects have the same care card number.
	bool operator == (const Patient & rhs);

	// Description: Greater than operator. Compares "this" Patient object with "rhs" Patient object.
	//              Returns true if the care card number of "this" Patient object is > the care card 
	//              number of "rhs" Patient object.
	bool operator > (const Patient & rhs);

	// For testing purposes!
	// Description: Prints the content of "this".
	friend ostream & operator<<(ostream & os, const Patient & p);

}; // end of Patient.h