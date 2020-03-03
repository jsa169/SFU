/*
 * ElementAlreadyExistsInBSTException.h
 *
 * Class Description: Defines the exception that is thrown when the 
 *                    Element Does Not Exist In BST
 *
 * Author: 
 */
 
#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class ElementAlreadyExistsInBSTException : public logic_error
{
public:
   ElementAlreadyExistsInBSTException(const string& message = "");
   
}; // end ElementAlreadyExistsInBSTException 