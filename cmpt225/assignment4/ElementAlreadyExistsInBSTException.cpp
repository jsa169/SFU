/*
 * ElementAlreadyExistsInBSTException.cpp
 *
 * Class Description: Defines the exception that is thrown when the 
 *                    Element Does Not Exist In BST.
 *
 * Author:
 */
 

#include "ElementAlreadyExistsInBSTException.h"  

ElementAlreadyExistsInBSTException::ElementAlreadyExistsInBSTException(const string& message): 
logic_error("Element Does Not Exist In BST Exception: " + message)
{
}  // end constructor

// End of implementation file.