/*
 * TransApp.cpp
 * 
 * Description: Main file of Translator App
 *
 * 
 * Author: Jichuan Shi, Martin Suryadi
 * Date: 2019-11-28
 */

//----------------------------------------------------------------------------------------------
//include statements
#include "BST.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

//----------------------------------------------------------------------------------------------
//Main function
int main(int argc, char **argv){

	//Initiate new BST
	BST<string> *b = new BST<string>;
	
	string a;
//----------------------------------------------------------------------------------------------
	//Open file 'datafile.txt' insert everyline in to BST
	ifstream file;	
	file.open("dataFile.txt");

	while(getline(file, a))
	{
		try {
			if(a == "\0") continue;
			b->insert(a);
		} catch (ElementAlreadyExistsInBSTException &anException) {
			cout << "insert() unsuccessful because " << anException.what() << endl;
			cout << "Duplicates ignored, continuing..." << endl;
			continue;
		}
	}

	file.close();
//----------------------------------------------------------------------------------------------
//traverse through BST if input is 'display'
//			Terminate program after displaying

	if (argc == 2 && string(argv[1]) == "display"){
		b->traverseInOrder();
		delete b;
		return 0;
	}

//----------------------------------------------------------------------------------------------
//Display translation according to user input, traverse through BST if input is 'display'. 
//			Terminate program after displaying
	system("clear");
	cout << "Enter word to translate: ";
	while(cin >> a) {
		if(a == "display") {
			b->traverseInOrder();
			break;
		}
		else {
			try {
				cout << "->" << b->retrieve(a) << endl;
				cout << "Enter word to translate: ";
			} catch(ElementDoesNotExistInBSTException &anException) {
				cout << "***Not Found!***\n";
				cout << "Enter word to translate: ";
				continue;
			}
		}

	}

	delete b;
	return 0;
}