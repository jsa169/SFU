/*
 * Patient_Test_Driver.cpp - Lab 4
 * 
 * Class Description: Test Driver for Patient class
 *
 * Modified on: Oct. 2019
 * Author: AL
 */

#include <iostream>
#include "Patient.h"

using namespace std;

int main() {

	// Variables declaration
	Patient p1234567890("Marie Poppins", "Somewhere over the hills", "234.987.9256", "mp@gemate.com", "1234567890");
	Patient p3456789012("R2D2", "Somewhere over the sea", "925.236.9876", "r2d2@gemate.com", "3456789012");
	Patient p4567890123("Odo", "Somewhere in space", "*^%-#^$-1234", "odo@gemate.com", "4567890123");

	cout << "Here is Patient 1234567890 : " << endl;
	cout << p1234567890 << endl;
    
	cout << "Here is Patient 3456789012 : " << endl;
	cout << p3456789012 << endl;

	cout << "Here is Patient 4567890123 : " << endl;
	cout << p4567890123 << endl;

	return 0;
}