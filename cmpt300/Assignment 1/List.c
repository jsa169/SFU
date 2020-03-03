#include<stdlib.h>
#include<stdio.h>

typedef struct node {
	int * data;
	struct node * next;
	struct node * prev;
}node;

typedef struct LIST {
	int Length;
	node * head;
	node * tail;
	node * current;
	struct LIST * next;
}LIST;

#define TotalNode 10
#define TotalList 5
node NodeArray[TotalNode];
LIST ListArray[TotalList];

int FirstTimeToggle = 1;



// makes a new, empty list, and returns its reference on success. Returns a NULL pointer on failure.
LIST * ListCreate(){

	if(FirstTimeToggle){	

		node EmptyNode  = {NULL, NULL, NULL};
		NodeArray[0] = EmptyNode;
		for(int i = 1; i < TotalNode ; i++){ //Connect all the nodes.
			NodeArray[i] = EmptyNode;
			NodeArray[i-1].next = &NodeArray[i];
		}

		LIST EmptyList = {0 ,NULL, NULL, NULL, NULL};
		ListArray[0] = EmptyList;
		for(int i = 1; i < TotalList; i++){ //connect all the arrays
			ListArray[i] = EmptyList;
			ListArray[i-1].next = &ListArray[i];
		}

		ListArray[0].Length = TotalNode;
		ListArray[0].head = &NodeArray[0];
		ListArray[0].tail = &NodeArray[TotalNode-1];
		ListArray[0].current = &NodeArray[0];
		ListArray[0].next = NULL;

		ListArray[1].Length = TotalList-2;

	FirstTimeToggle = 0;
	}

	if(ListArray[1].next == NULL){
		printf("All Listhead space is used up. New list creation failed\n");
		return NULL;
	}else{
		LIST *NewList = ListArray[1].next;
		ListArray[1].next = ListArray[1].next->next;
		NewList->next = NULL;
		ListArray[1].Length --;
		return NewList;
	}


}

// returns the number of items in list. returns -999 if the list does not exist
int ListCount(LIST * list) {
	if (list == NULL) return -999; 
	return list->Length;
}

//returns a pointer to the first item in list and makes the first item the current item.
void *ListFirst(LIST * list){}

//returns a pointer to the last item in list and makes the last item the current one.
void *ListLast(LIST * list){}

//advances list's current item by one, and returns apointer to the new current item. If this operation advances 
//the current item beyondthe end of the list, a NULL pointer is returned.
void *ListNext(LIST * list){} 

//backs up list's current item by one, and returns a pointer to the new current item. If this operation backs 
//up the current item beyond the start of the list, a NULL pointer is returned.
void *ListPrev(LIST * list){}

//returns a pointer to the current item in list.
void *ListCurr(LIST * list){}

//adds the new item to list directly after the current item, and makes item the current item. If the current 
//pointer is before the start of the list, the item is added at the start. If the current pointer is beyond 
//the end of the list, the item is added at the end. Returns 0 on success, -1 on failure.
int ListAdd(LIST * list, int * item) {}

//adds item to list directly before the current item, and makes the new item the current one. If the current 
//pointer is before the start of the list, the item is added at the start. If the current pointer is beyond 
//the end of the list, the item is added at the end. Returns 0 on success, -1 on failure.
int ListInsert(LIST * list, int * item) {}

//adds item to the end of list, and makes the new item the current one. Returns 0 on success, -1 on failure.
int ListAppend(LIST * list, int * item) {
	if(list == NULL){
		printf("Node Append failed: invalid list.\n");
		return -1;
	}
	if(ListArray[0].Length == 0){
		printf("Node Append failed: all space for nodes has been used.\n");
		return -1;
	}

	ListArray[0].head->data = item;

	list->current = ListArray[0].head;
	ListArray[0].head = ListArray[0].head->next;
	list->current->next = NULL;
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
}

//adds item to the front of list, and makes the new item the current one. Returns 0 on success, -1 on failure.
int ListPrepend(LIST * list, int * item) {
	if(list == NULL){
		printf("Node Append failed: invalid list.\n");
		return -1;
	}
	if(ListArray[0].Length == 0){
		printf("Node Append failed: all space for nodes has been used.\n");
		return -1;
	}

	ListArray[0].head->data = item;

	list->current = ListArray[0].head;
	ListArray[0].head = ListArray[0].head->next;
	list->current->next = NULL;
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

}

//Return current item and take it out of list. Make the next item the current one.
void *ListRemove(LIST * list) {}

//adds list2 to the end of list1. The current pointer is set to the current pointer of list1. List2 no longer 
//exists after the operation.
void ListConcat(LIST * list1, LIST * list2) {}

//delete list. itemFree is a pointer to a routine that frees an item. It should be invoked (within ListFree) 
//as: (*itemFree)(itemToBeFreed);
void ListFree(LIST * list, void * itemFree) {}

//Return last item and take it out of list. Make the new last item the current one.
void *ListTrim(LIST * list) {}

/*searches list starting at the current item until the end is reached or a match is found. In this context, a match 
is determined by the comparator parameter. This parameter is a pointer to a routine that takes as  its first 
argument an item pointer, and as its second argument comparisonArg. Comparator returns 0 if the item and 
comparisonArg don't match, or 1 if they do. Exactly what constitutes a match is up to the implementor of 
comparator. If a match is found, the current pointer is left at the matched item and the pointer to that item is 
returned. If no match is found, the current pointer is left beyond the end of the list and a NULL pointer is returned.*/
void *ListSearch(LIST * list, void * comparator, void * comparisonArg){}


int main(){
	printf("\nCreating list a... ");

	LIST * la = ListCreate();
	printf("\nCreating list b... ");
	LIST * lb = ListCreate();
	printf("\nCreating list c... ");
	LIST * lc = ListCreate();
	printf("\nCreating list d... ");
	LIST * ld = ListCreate();

	int a = 0;
	int b = 1;	
	int c = 2;
	int d = 3;

	printf("\nPrepending 3 to list la... ");
	ListAppend(la, &d);
	printf("\nAppending 1 to list lb... ");
	ListAppend(lb, &b);
	printf("\nAppending 1 to list lb... ");
	ListAppend(lb, &b);
	printf("\nPrepending 2 to list la... ");
	ListPrepend(la, &c);
	printf("\nAppending 3 to list ld... ");
	ListAppend(ld, &d);
	printf("\nAppending 2 to list lc... ");
	ListAppend(lc, &c);
	printf("\nAppending 1 to list la... ");
	ListPrepend(la, &b);
	printf("\nPrepending 0 to list la... ");
	ListPrepend(la, &a);
	printf("\nAppending 2 to list lc... ");
	ListAppend(lc, &c);
	printf("\nPrepending 1 to list lc... ");
	ListPrepend(lc, &b);
	printf("\nAppending 3 to list lc... ");
	ListAppend(lc, &d);
	printf("\nAppending 2 to list la... ");
	ListAppend(lc, &a);

	
	printf("\nList lengths are: %d, %d, %d, %d.\n", ListCount(la), ListCount(lb), ListCount(lc), ListCount(ld));

	char p;
	for(int i = 0; i < TotalNode; i++){
		printf("%i", *NodeArray[i].data);
	}
	printf("\n");

	node * current = la->head;
	printf("\nPrinting la: ");
	for(int i = 0; i < la->Length; i++){
		printf("%i", *current->data);
		current = current->next;
	}
	printf("\n");

	printf("\nPrinting lc: ");
	current = lc->head;
	for(int i = 0; i < lc->Length; i++){
		printf("%i", *current->data);
		current = current->next;
	}
	printf("\n");


	return 0;
}