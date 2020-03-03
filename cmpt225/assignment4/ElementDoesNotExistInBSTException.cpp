/*
 * ElementDoesNotExistInBSTException.cpp
 *
 * Class Description: Defines the exception that is thrown when the 
 *                    Element Does Not Exist In BST.
 *
 * Author:
 */
 

#include "ElementDoesNotExistInBSTException.h"  

ElementDoesNotExistInBSTException::ElementDoesNotExistInBSTException(const string& message): 
logic_error("Element Does Not Exist In BST Exception: " + message)
{
}  // end constructor

// End of implementation file.