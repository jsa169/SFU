#include <stdio.h>
#include <stdlib.h>

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