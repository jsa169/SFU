/* BST.h */

#include <iostream>

using namespace std;

// Desc: A binary tree node with a single key (int)
//       Contains pointers to left child, right child, parent
// Note: All attributes are public.
class BTnode {
    public:
        int key;
        BTnode *left, *right, *parent;
        BTnode(int key, BTnode *left, BTnode *right, BTnode *parent) : key(key), left(left), right(right), parent(parent) {};
};

// Desc: A binary search tree (root)
//  Inv: All keys in root->left <= root->key <= all keys in root->right
class BST {

/* Feel free to add to the private and the public parts of this class. */
/* However, you cannot modify the code that is already in this class. */

    private:
        // Desc: The root of the BST (NULL if empty)
        BTnode *root;

        // Desc: Helper function for insert(key)
        BTnode *insertH(BTnode *root, int key);

    public:
        // Desc: Constructors
        BST();
        BST(BTnode *root);

        // Desc: Insert key into the BST
        // Note: This is the wrapper method which is called
        //       by the client code (main.ccp) and which
        //       calls the private helper (recursive) method insertH().
        void insert(int key);

        // Desc: I/O functions
        //  Pre: The input stream contains a sequence of integers ending
        //       in eof, or the result is indeterminate
        friend istream & operator>>(istream & is, BST& rhs);
        friend ostream & operator<<(ostream & os, const BST& rhs);

        // Desc: Prints the highest 5 keys of the BST in decreasing order.
        //       Keys are presented in descending order in a space-separated
        //       list, ending with a newline.
        // Post: The BST keys and structure will remain unchanged.
        void top5() const;

};
