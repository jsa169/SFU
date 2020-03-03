#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node definition for doubly linked list
typedef struct _dllnode  {
    int data;
    struct _dllnode * next;
    struct _dllnode * prev;
} DLLnode_t;

// Definition of doubly linked list
typedef struct {
    DLLnode_t * head;
} DLL_t;

// Creates a doubly linked list
DLL_t * DLLCreate() {
    DLL_t * ret = malloc(sizeof(DLL_t));
    ret->head = NULL;
    return ret;
}

// Appends a DLLnode_t containing the value x into a DLL_t
void DLLAppend(DLL_t * intlist, int x) {
    // Create a DLLnode_t
    DLLnode_t * newNode = malloc(sizeof(DLLnode_t));
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;
    
    // Point head to new node if list is empty
    if(intlist->head == NULL) {
        intlist->head = newNode;
        return;
    }
    
    DLLnode_t * temp =intlist->head;
    while(temp->next != NULL) {
        temp = temp->next; // Go To last Node
    }
    
    temp->next = newNode;
    newNode->prev = temp;
}

// Prints the elements of a doubly linked list
void DLLPrint(DLL_t * intlist) {
    DLLnode_t * temp = intlist->head;
    while(temp != NULL) {
        printf("%d ",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void DLLReverse(DLL_t * intlist){
	//Keep track of current, and defind temp
	DLLnode_t * current = intlist->head;
	DLLnode_t * temp;
	
	//Go through the LL
	while(current != NULL){
		//Rever prev amd next pointers
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}

	//If LL is empty, ie. NULL, return
	if(intlist->head == NULL){return;}
	//Change head to point the last eletment in LL
	intlist->head = temp->prev;	
}

void DLLRemove(DLL_t * intlist, int ind){
	//Remove and change head to point to next if index first node
	if(ind == 0){
		intlist->head = intlist->head->next;
		intlist->head->prev = NULL;
		return;
	}

	int n = 0;
	//Keep track of current node
	DLLnode_t * current = intlist->head; 
	//Go to the node at target index
	while (n != ind){
		current = current->next;
		n++;
	}
	//If node is last in LL, previous nodes be comre last in LL
	if(current->next == NULL){
		current->prev->next = NULL;
		free(current);
		return;
	}
	//Delete nodes in the middle of LL
	else{
	current->prev->next = current->next;
	current->next->prev = current->prev;
	free(current);
	}
}

int main (){
	DLL_t * intlist = DLLCreate();
	if (intlist == NULL){
		return 1;
	}
	
	DLLAppend(intlist, 4);
	DLLAppend(intlist, 5);
	DLLAppend(intlist, 7);
	DLLAppend(intlist, 7);
	DLLAppend(intlist, 9);
	
	DLLPrint(intlist);
	DLLReverse(intlist);
	
	DLLRemove(intlist, 4);

	DLLPrint(intlist);

}
