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

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// #Include statements

#include <iostream>
#include "List.h"
#include "Patient.h"
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

//--------------------------------------------------------------------------------------------
//Global Variables
List l = List();
Patient * Current;

//--------------------------------------------------------------------------------------------
//Description: Search for a target patient using his care card number, then set the patient
//				as current selected patient.
//				Return true of element found
//				Otherwise return false
bool Search_and_set_current(string aCareCard){

	Patient temp = Patient(aCareCard);	//Create temp Patient with the given care card 

	Current = l.search(temp);	//Search in the patient list for patient with same care card number as temp
								//and set as current selected
	
	if(Current != NULL){	//return
		return true;
	}else{
		return false;
	}

}

//--------------------------------------------------------------------------------------------
//Description: Removes currently selected patient from list l, return if nothing is selected
void l_remove(){

	if(Current == NULL)
		return;

	l.remove(* Current);
	Current = NULL;	//After removing selected patient, set Current to NULL

	
}

//--------------------------------------------------------------------------------------------
//Description: Ask for inputs, and create a nuw patient, then insert into list l
//			   Return true if successfully inserted,
//			   Return false otherwise
bool l_insert(){

	//Declaring variables
	cout << "Creating a new Patient..."<< endl<<endl;
	string name;
	string address;
	string phone;
	string email;
	string careCard;

	//Getting input
	cout << "Enter careCard (10 digits, invalid input will be set to '0000000000'): ";
	getline(cin, careCard);
	cout << "Enter name: ";
	getline(cin, name);
	cout << "Enter address: ";
	getline(cin, address);	
	cout << "Enter phone: ";
	getline(cin, phone);
	cout << "Enter email: ";
	getline(cin, email);

	//Creating new patient	
	Patient newElement = Patient(careCard, email, name, address, phone);

	//Inserting new patient		
	bool a = l.insert(newElement);

	//Search and set as selected
	Search_and_set_current(careCard);
	return a;	

}

//--------------------------------------------------------------------------------------------
//Description: Modify the currently selected patient using one of the giving options
void editPatient(){

	//Decalaring variable
	char editoption;
	string textToEdit;

	//Loop if user does NOT choose to quit
	while(editoption != 'Q' ){ //while edit option not equal to (Q)uit
		system("clear");
		cout<<"Currently selected patient: "<<endl<<*Current<<endl
		<<"Please select one of the following edit options"<<endl<<endl
		<<"  (N)ame to edit name"<<endl
		<<"  (E)mail to edit email"<<endl
		<<"  (A)ddress to edit address"<<endl
		<<"  (P)hone to edit phone"<<endl
		<<"  (Q)uit and return to main menu"<<endl<<endl
		<< "--------------------------------------------" << endl 
		<< "Enter (N, E, A, P, Q): ";
		
		cin >> editoption;
		cin.ignore();
		cout << endl;

		//Modify each info field according to the users' input
		if(editoption == 'N'){	//(N)ame edit
			system("clear");
			cout<<"Currently selected patient: "<<endl<<*Current<<endl
			    <<"Enter desired name: ";

			getline(cin,textToEdit);
			Current->setName(textToEdit);

		}else if(editoption == 'E'){	//(E)mail edit
			system("clear");
			cout<<"Currently selected patient: "<<endl<<*Current<<endl
			    <<"Enter desired email: ";

			getline(cin,textToEdit);
			Current->setEmail(textToEdit);

		}else if(editoption == 'A'){	//(A)ddress edit
			system("clear");
			cout<<"Currently selected patient: "<<endl<<*Current<<endl
			    <<"Enter desired address: ";

			getline(cin,textToEdit);
			Current->setAddress(textToEdit);

		}else if(editoption == 'P'){	//(P)hone edit
			system("clear");
			cout<<"Currently selected patient: "<<endl<<*Current<<endl
			    <<"Enter desired phone: ";

			getline(cin,textToEdit);
			Current->setPhone(textToEdit);

		}else if(editoption == 'Q'){	//(Q)uit
			return;
		}
	}
}





//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//Description: Main app of walkIn that includes UI and user options, It will ask user for different options including
//			   creating new, remove, edit, and print patient. It also keeps track of a currently selected patient.
int main(){
	system("clear");
	cout << "Welcome to the clinic patient management system!" << endl <<endl;

	char option;

	while(option != 'Q' ){ //Start of while loop, program will end if option = Q

		//  Available options for the user to use, This is the main menu of the entire app
		cout << "Please select which function you need "<<endl<<"To edit or remove a patient, search for him first"<<endl<<endl 
			 	<< "  (N)ew - patient"<< endl
				<< "  (S)earch - and select a patient"<< endl
				<< "  (P)rint - all patients"<< endl
				<< "  (R)emove - currently selected patient"<<endl
				<< "  (C)lear - all patient"<<endl
				<< "  (E)dit - currently selected patient"<< endl
				<< "  (Q)uit - application"<<endl<<endl;
		
		//Displaying the currently selected patient 
		if(Current != NULL){
			cout<<"Currently selected patient is: "<< endl <<*Current<<endl;
		}else{
			cout<<"No currently selected patient"<<endl<<endl;
		}


		cout<<"Total patient number is "<<l.getElementCount()<<endl<<endl
		    << "--------------------------------------------" << endl << "Enter (N, S, P, R, E, Q): ";
		
		//Asking users for input for the options above
		cin >> option;
		cin.ignore();
		cout <<endl;

//--------------------------------------------------------------------------------------------		
//Switch according to the options user inputed.

//If nothing is passed by the user, or an wrong option is inputed. By default the programd will 
//go back to the while statement.
		switch(option){

//--------------------------------------------------------------------------------------------
			case 'N':{	//(N)ew - patient
				system("clear");

				//Call insert function, Display Error of success depending on the return of the insert function
				if (l_insert() == false){
					cout <<endl<< "Error: Cannot insert, either patient already exist or wrong input."<<endl;
				}
				else{
					cout <<endl<<"Successfully created." << endl<<endl
					<<"Patient created:"<<endl<<*Current;
				}

				cout <<endl<<"--------------------------------------------"
				     << endl <<"Enter to continue: ";
				cin.ignore();
				system("clear");

				break;
			}

//--------------------------------------------------------------------------------------------
			case 'S':{	//(S)earch - and select a patient
				system("clear");

				//Get input for searching
				string careCard;
				cout<<"Enter the care card number to search: ";
				getline(cin, careCard);

				//Check for non integer input
				int count = 0;
				for(unsigned int i = 0; i < careCard.size(); i++){
					if(isdigit(careCard[i]) != true)
					count++;
				}

				//Check if Target of search is 10 integer long, run search funtion if true
				if(careCard.size() != 10 || count != 0)
					cout <<endl<<"Patient not found."<<endl<<endl;
				else if (Search_and_set_current(careCard) == false)
					cout <<endl<<"Patient not found."<<endl<<endl;
				else
					cout <<endl<< "Patient found!"<< endl <<endl
					     <<"Current selected patient is set to: " <<endl<< *Current<<endl;
				

				cout <<"--------------------------------------------"
				     << endl <<"Enter to continue: ";
				cin.ignore();

				system("clear");
				break;
			}

//--------------------------------------------------------------------------------------------
			case 'P':{	//(P)rint - all patients
				system("clear");

				//Print out list if element count is not 0
				if(l.getElementCount() == 0){
					cout<< "Error: Patient list is empty, nothing to display." <<endl;
				}
				else{
					cout << "Displaying all the patients as follows:" << endl<<endl;
					l.printList();
				}
				cout <<endl<<"--------------------------------------------"
				     << endl <<"Enter to continue: ";
				cin.ignore();

				system("clear");
				break;
			}

//--------------------------------------------------------------------------------------------
			case 'R':{	//(R)emove - currently selected patient
				system("clear");

				//If no patient is selected, display error and return to menu
				if(Current == NULL){
					system("clear");

					cout<<"Error: No Patient is Selected"<<endl
				        << endl <<"--------------------------------------------"
				        << endl <<"Enter to continue: ";  
					cin.ignore();

					system("clear");
					break;
				}

				//Call the remove function if a patient is selected
				l_remove();
				cout <<"Successfully Removed"<<endl
				     <<endl <<"--------------------------------------------"
				     << endl <<"Enter to continue: ";
				cin.ignore();

				system("clear");				
				break;
			}

//--------------------------------------------------------------------------------------------			
			case 'C':{	//(C)lear - all patient
				system("clear");

				//Display Error if list is empty, if list has patients, remove all
				if(l.getElementCount() == 0){
					cout<< "Error: Patient list is empty, nothing to clear"<<endl;
				}else{
					l.removeAll();
					cout<< "All patients removed."<<endl;
					Current = NULL;
				}
				cout <<endl<<"--------------------------------------------"
				     << endl <<"Enter to continue: ";
				cin.ignore();

				system("clear");
				break;
			}

//--------------------------------------------------------------------------------------------
			case 'E':{	//(E)dit - currently selected patient
				system("clear");

				//Edit patient, only if a patient is currently selected
				if(Current == NULL){
					system("clear");

					cout<<"No Patient is Selected"<<endl
				        << endl <<"--------------------------------------------"
				        << endl <<"Enter to continue: ";  
					cin.ignore();

					system("clear");
					break;
				}
				editPatient();

				system("clear");
				break;
			}

//--------------------------------------------------------------------------------------------
			case 'Q':{	//(Q)uit Application
				system("clear");
				break;

			}

//--------------------------------------------------------------------------------------------
			default:{	//Break the switch and return to the top of the loop by default
				system("clear");

				break;
			}

//--------------------------------------------------------------------------------------------
		} //End of switch
		
	} //End of while loop
	cout<<"Thanks for using the clinic patient management system!"<<endl;
	cin.ignore();
	system("clear");

} //End of walkIn.cpp

