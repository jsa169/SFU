#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BST.h"
#include "BT-node.h"

// Test your methods in the main function
int main () {

    BTnode * tree = NULL;

    for (int i = 0; i < 10; i++) {
        int newnum = rand() % 900 + 100;
        printf("Inserting . . . %d\n", newnum);
        // Test your insert function
        tree = insert(tree, newnum);
        print(tree);
        putchar('\n');
		
		// This is just to pause until you press enter after every insert
        getchar();
    }
    // Test your search function
	printf("303: %d\n", search(tree, 303));
	printf("209: %d\n", search(tree, 209));

    // Print out the maximum value in the tree
    int max = findmax(tree);
    printf("maximum value: %d\n", max);

    // Print out the minimum value in the tree
    int min = findmin(tree);
    printf("minimum value: %d\n", min);

    // Test your printAscendOrder function
    printf("Elements in ascending order:");
    printAscendOrder(tree);
    postfree(tree);
    return 0;

}
