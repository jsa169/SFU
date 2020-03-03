/*List.h
*
*Description: List ADT implemented using Array. All memory is statically allocated
*			  Multiple lists can be stored together. Once memory is used up, no more
* 			  items will be added, and no more space will be allocated. Every function
*			  other than ListSearch will operate at O(1). ListCreate operates at O(1)
*			  except for the first time it is called. All the free nodes are inter-
*			  connected, every rellocated node is also added back to the free node array.
*			  All the Free lits are also interconnected. This will allow big O(1).
*
*Name: Jichuan Shi
*Date: 2020-01-30
*/

#include<stdlib.h>
#include<stdio.h>
#include"List.h"


#define TotalNode 5000	//Maximum nodes available
#define TotalList 100	//Maximum lists available
node NodeArray[TotalNode]; //Holds all the nodes
LIST ListArray[TotalList]; //ListArray[0] holds all the free nodes. List[1] holds all the free listheads

int FirstTimeToggle = 1;
//----------------------------------------------------------------------------------------------------------------------
//Description: makes a new, empty list, and returns its reference on success. Returns a NULL pointer on failure.
// runtime is O(1) except for the first time this is called .
LIST * ListCreate(){

	if(FirstTimeToggle){	//This is only executed only during the first call

		node EmptyNode  = {NULL, NULL, NULL};
		NodeArray[0] = EmptyNode;
		for(int i = 1; i < TotalNode ; i++){ //Connect all the nodes.
			NodeArray[i] = EmptyNode;
			NodeArray[i-1].next = &NodeArray[i];
		}

		LIST EmptyList = {0 ,0, NULL, NULL, NULL, NULL};
		ListArray[0] = EmptyList;
		for(int i = 1; i < TotalList; i++){ //connect all the listheads
			ListArray[i] = EmptyList;
			ListArray[i-1].next = &ListArray[i];
		}

		ListArray[0].Length = TotalNode; //ListArray point to first available node
		ListArray[0].head = &NodeArray[0];
		ListArray[0].tail = &NodeArray[TotalNode-1];
		ListArray[0].current = &NodeArray[0];
		ListArray[0].next = NULL;

		ListArray[1].Length = TotalList-2;

	FirstTimeToggle = 0;
	}

	if(ListArray[1].next == NULL){ //if all listheads are used
		printf("All Listhead space is used up. New list creation failed\n");
		return NULL;
	}else{ //Create new list
		LIST *NewList = ListArray[1].next;
		ListArray[1].next = ListArray[1].next->next;
		NewList->next = NULL;
		ListArray[1].Length --;
		return NewList;
	}


}
//----------------------------------------------------------------------------------------------------------------------
//Description: returns the number of items in list. returns -999 if the list does not exist
int ListCount(LIST * list) {
	if (list == NULL) return -999; 
	return list->Length;
}
//----------------------------------------------------------------------------------------------------------------------
//Description: returns a pointer to the first item in list and makes the first item the current item.
void *ListFirst(LIST * list){
	if(list == NULL){
		printf("ListFirst failed: list does not exist\n");
		return NULL;
	}
	if (list->Length == 0){
		printf("ListFirst failed: list is empty\n");
		return NULL;
	} 

	if(list->currentRange != 0){ //if current is out of range, make current in range
		list->currentRange = 0;
	}

	if(list->Length == 1) return list->current;
	else{
		list->current = list->head;
		return list->current;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//Description: returns a pointer to the last item in list and makes the last item the current one.
void *ListLast(LIST * list){

	if(list == NULL){
		printf("ListLast failed: list does not exist\n");
		return NULL;
	}
	if (list->Length == 0){
		printf("ListLast failed: list is empty\n");
		return NULL;
	}

	if(list->currentRange != 0){
		list->currentRange = 0;
	}

	if(list->Length == 1) return list->current;
	else{
		list->current = list->tail;
		return list->current;
	}

}
//----------------------------------------------------------------------------------------------------------------------
//Description: advances list's current item by one, and returns apointer to the new current item. If this operation advances 
//the current item beyondthe end of the list, a NULL pointer is returned.
void *ListNext(LIST * list){
	if(list == NULL){
		printf("ListNext failed: list does not exist\n");
		return NULL;
	}
	if (list->Length == 0){
		printf("ListNext failed: list is empty\n");
		return NULL;
	}

	if(list->currentRange == 1)	return NULL; //if current is beyond tail, return NULL

	if(list->currentRange == -1){ //if current is before head, return head
		list->current = list->head;
		list->currentRange = 0;
		return list->current;
	}
	list->current=list->current->next; //return next node
	if(list->current == NULL) list->currentRange = 1;
	return list->current;
	
} 
//----------------------------------------------------------------------------------------------------------------------
//Description: backs up list's current item by one, and returns a pointer to the new current item. If this operation backs 
//up the current item beyond the start of the list, a NULL pointer is returned.
void *ListPrev(LIST * list){
	if(list == NULL){
		printf("ListPrev failed: list does not exist\n");
		return NULL;
	}
	else if (list->Length == 0){
		printf("ListPrev failed: list is empty\n");
		return NULL;
	}
	if(list->currentRange == -1) return NULL; //if current is beyond tail, return NULL

	if(list->currentRange == 1){ //if current is beyond tail, return tail
		list->current = list->tail;
		list->currentRange = 0;
		return list->current;
	}

	list->current = list->current->prev; //return next node
	if(list->current == NULL) list->currentRange = -1;
	return list->current;
}
//----------------------------------------------------------------------------------------------------------------------
//Description: returns a pointer to the current item in list.
void *ListCurr(LIST * list){
	if(list == NULL){
		printf("ListCurr failed: list does not exist\n");
		return NULL;
	}
	else if (list->Length == 0){
		printf("ListCurr failed: list is empty\n");
		return NULL;
	}
	else{
		return list->current;
	}	
}
//----------------------------------------------------------------------------------------------------------------------
//Description: adds the new item to list directly after the current item, and makes item the current item. If the current 
//pointer is before the start of the list, the item is added at the start. If the current pointer is beyond 
//the end of the list, the item is added at the end. Returns 0 on success, -1 on failure.
int ListAdd(LIST * list, void * item) {
	if(list == NULL){
		printf("ListAdd failed: invalid list.\n");
		return -1;
	}
	if(ListArray[0].Length == 0){
		printf("ListAdd failed: all space for nodes has been used.\n");
		return -1;
	}
	

	if(list->Length == 0 || list->current == list->tail) return ListAppend(list, item); // if current is tail, append
	else{

		ListArray[0].head->data = item; //ListArray[0].head points to list of free nodes
		list->current->next->prev = ListArray[0].head;
		ListArray[0].head->prev = list->current;
		ListArray[0].head = ListArray[0].head->next;
		list->current->next->prev->next = list->current->next;
		list->current->next = list->current->next->prev;
		list->current = list->current->next;
		ListArray[0].Length--;
		list->Length++;
		return 0;
	}
		
}
//----------------------------------------------------------------------------------------------------------------------
//Description: adds item to list directly before the current item, and makes the new item the current one. If the current 
//pointer is before the start of the list, the item is added at the start. If the current pointer is beyond 
//the end of the list, the item is added at the end. Returns 0 on success, -1 on failure.
int ListInsert(LIST * list, void * item) {
	if(list == NULL){
		printf("Node Append failed: invalid list.\n");
		return -1;
	}
	if(ListArray[0].Length == 0){
		printf("Node Append failed: all space for nodes has been used.\n");
		return -1;
	}

	if(list->Length == 0 || list->current == list->head) return ListPrepend(list, item);// if current is head, prepend
	else{
		ListArray[0].head->data = item; //ListArray[0].head points to list of free nodes
		ListArray[0].head->prev = list->current->prev;
		list->current->prev = ListArray[0].head;
		ListArray[0].head = ListArray[0].head->next;
		list->current->prev->prev->next = list->current->prev;
		list->current->prev->next = list->current;
		list->current = list->current->prev;
		ListArray[0].Length--;
		list->Length++;
		return 0;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//Description: adds item to the end of list, and makes the new item the current one. Returns 0 on success, -1 on failure.
int ListAppend(LIST * list, void * item) {
	if(list == NULL){
		printf("ListAppend failed: invalid list.\n");
		return -1;
	}
	if(ListArray[0].Length == 0){
		printf("ListAppend failed: all space for nodes has been used.\n");
		return -1;
	}

	ListArray[0].head->data = item; //ListArray[0].head points to list of free nodes

	list->current = ListArray[0].head;
	ListArray[0].head = ListArray[0].head->next;
	list->current->next = NULL;
	list->current->prev = NULL;
	ListArray[0].Length--;

	if(list->Length == 0){
		list->head = list->current;
		list->tail = list->current;
	}
	else{
		list->current->prev = list->tail;
		list->tail->next = list->current;
		list->tail = list->current;
	}
	list->Length ++;
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------
//Description: adds item to the front of list, and makes the new item the current one. Returns 0 on success, -1 on failure.
int ListPrepend(LIST * list, void * item) {
	if(list == NULL){
		printf("ListPrepend failed: invalid list.\n");
		return -1;
	}
	if(ListArray[0].Length == 0){
		printf("ListPrepend failed: all space for nodes has been used.\n");
		return -1;
	}

	ListArray[0].head->data = item; //ListArray[0].head points to list of free nodes

	list->current = ListArray[0].head;
	ListArray[0].head = ListArray[0].head->next;
	list->current->next = NULL;
	list->current->prev = NULL;
	ListArray[0].Length--;

	if(list->Length == 0){
		list->head = list->current;
		list->tail = list->current;
	}
	else{
		list->head->prev = list->current;
		list->current->next = list->head;
		list->head = list->current;
	}
	list->Length ++;
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------
//Description: Return current item and take it out of list. Make the next item the current one.
void *ListRemove(LIST * list) {
	if(list == NULL){
		printf("ListRemove failed: list does not exist\n");
		return NULL;
	}
	if (list->Length == 0){
		printf("ListRemove failed: list is empty\n");
		return NULL;
	}
	if(list->current == NULL){
		printf("ListRemove failed: current is not pointing at anything\n");
		return NULL; 
	}

	ListArray[0].tail = list->current; //ListArray[0].head points to list of free nodes
	void * toBeReturned = list->current->data;
	if(list->Length == 1){ //List length = 1, only need to remove 1 node
		ListArray[0].tail->next = ListArray[0].head;
		ListArray[0].head = ListArray[0].tail; //ListArray[0].tail is a temp pointer
		list->head = NULL;
		list->tail = NULL;
		list->current = NULL;
	}
	else if(list->current == list->head){ //List length > 0, current is head
		list->head = list->head->next;
		list->head->prev = NULL;
		ListArray[0].tail->next = ListArray[0].head;
		ListArray[0].head = ListArray[0].tail;
		list->current = list->head;
	}
	else if(list->current == list->tail){ //List length > 0, current is tail

		list->tail = list->current->prev;
		list->tail->next = NULL;

		ListArray[0].tail->next = ListArray[0].head;
		ListArray[0].head = ListArray[0].tail;
		ListArray[0].head->prev = NULL;

		list->current = NULL;
		list->currentRange = 1;
	}
	else { //List length > 0, current is any middle node other than head and tail
		list->current->prev->next = list->current->next;
		list->current->next->prev = list->current->prev;
		ListArray[0].tail->next = ListArray[0].head;
		ListArray[0].head = ListArray[0].tail;
		ListArray[0].head->prev = NULL;		
	}
	list->Length--;
	ListArray[0].Length++;

	//printf("\nFreenode: %i\n", ListArray[0].Length);
	return toBeReturned;

}
//----------------------------------------------------------------------------------------------------------------------
//Description: adds list2 to the end of list1. The current pointer is set to the current pointer of list1. List2 no longer 
//exists after the operation.
void ListConcat(LIST * list1, LIST * list2) {
	if(list1 == NULL || list2 == NULL){
		printf("ListConcat failed: one or both of the source list do(es) not exist.");
		return;
	}
	if(list1->Length == 0){ //list1 is empty
		list1->tail = list2->tail;
		list1->head = list2->head;
		list1->Length = list2->Length;
		if (list2->Length != 0) list1->currentRange = -1;
	}
	if(list1->Length != 0 && list2->Length == 0){ //list1 is not empty, list2 is empty

		list1->tail->next = list2->head;
		//list1->tail = list2->tail;
		list1->Length = list1->Length + list2->Length;
	}
	if(list1->Length != 0 && list2->Length != 0){ //list1 & list2 both empty

		list1->tail->next = list2->head;
		list1->tail = list2->tail;
		list1->Length = list1->Length + list2->Length;
	}

	list2->current = NULL;	//Rellocated list2, connect to other available lists
	list2->head	= NULL;
	list2->tail = NULL;	
	list2->Length = 0;
	list2->currentRange = 0;
	list2->next = ListArray[1].next;
	ListArray[1].next = list2;
	ListArray[1].Length++;
}
//----------------------------------------------------------------------------------------------------------------------
//Description: delete list. itemFree is a pointer to a routine that frees an item. It should be invoked (within ListFree) 
//as: (*itemFree)(itemToBeFreed);
void ListFree(LIST * list, void * itemFree) {
	if(list == NULL){
		printf("ListFree failed: list does not exist\n");
		return;
	}

	list->current = list->head;
	while (list->current != NULL){
		((void (*)(void *))itemFree)(list->current->data);
		list->current = list->current->next;
	}

	if(list->Length == 0);
	else{
		list->tail->next = ListArray[0].head;
		ListArray[0].head = list->head;
	}

	ListArray[0].Length = ListArray[0].Length+list->Length;

	list->current = NULL; //Rellocated list, connect to other available lists
	list->head	= NULL;
	list->tail = NULL;	
	list->Length = 0;
	list->currentRange = 0;
	list->next = ListArray[1].next;
	ListArray[1].next = list;
	ListArray[1].Length++;	
}
//----------------------------------------------------------------------------------------------------------------------
//Description: Return last item and take it out of list. Make the new last item the current one.
void *ListTrim(LIST * list) {
	if(list == NULL){
		printf("ListTrim failed: list does not exist\n");
		return NULL;
	}
	if (list->Length == 0){
		printf("ListTrim failed: list is empty\n");
		return NULL;
	}

	ListArray[0].tail = list->tail;
	void * toBeReturned = list->tail->data;

	list->tail->prev->next = NULL;
	list->tail = list->tail->prev;

	ListArray[0].tail->next = ListArray[0].head;
	ListArray[0].head = ListArray[0].tail;
	ListArray[0].head->prev = NULL;

	if(list->Length == 1) list->current = NULL; //if length = 1, after trim, list is empty
	else list->current = list->tail; //after trimming, current points to the new tail

	list->currentRange = 1;
	
	list->Length--;
	ListArray[0].Length++;

	//printf("\nFreenode: %i\n", ListArray[0].Length);
	return toBeReturned;
}
//----------------------------------------------------------------------------------------------------------------------
/*Description: searches list starting at the current item until the end is reached or a match is found. In this context, a match 
is determined by the comparator parameter. This parameter is a pointer to a routine that takes as  its first 
argument an item pointer, and as its second argument comparisonArg. Comparator returns 0 if the item and 
comparisonArg don't match, or 1 if they do. Exactly what constitutes a match is up to the implementor of 
comparator. If a match is found, the current pointer is left at the matched item and the pointer to that item is 
returned. If no match is found, the current pointer is left beyond the end of the list and a NULL pointer is returned.*/
void *ListSearch(LIST * list, void * comparator, void * comparisonArg){
	if(list == NULL){
		printf("ListSearchm failed: list does not exist\n");
		return NULL;
	}
	if (list->Length == 0){
		printf("ListSearch failed: list is empty\n");
		return NULL;
	}
	if(list->currentRange == -1){
		list->currentRange = 0;
		list->current = list->head;
	}

	int a;
	while (list->current != NULL){
		a = ((int (*)(void *, void *))comparator)(list->current->data, comparisonArg);
		if(a == 1) return list->current->data;
		list->current = list->current->next;
	}
	
	list->currentRange = 1;
	return NULL;
}
