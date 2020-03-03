/*test.h
*
*Description: test driver for List ADT
*
*			 
*
*Name: Jichuan Shi
*Date: 2020-01-30
*/

#include<stdlib.h>
#include<stdio.h>
#include "List.h"


void printList(LIST *list){
	node * current = list->head;
	if(list->Length == 0) {
		printf("Empty List\n");
		return;
	}
	for(int i = 0; i < list->Length; i++){
		printf("%i", *(int*)current->data);
		current = current->next;
	}		
	printf("\n");
}

int comparator(void * a, void * b){
	if ( *(int*)a == *(int*)b ) return 1;
	return 0;
}

void itemFree(void * a){
	free(a);
}

int main(){

printf("\n----Testing ListCreate()---------------------------------------------------\n");
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



printf("\n----Testing First, Last, Prev, Next on empty list---------------------------\n");
	printf("\nUsing ListFirst on lc...");
	ListFirst(lc);
	printf("\nUsing ListLast on lc...");
	ListLast(lc);
	printf("\nUsing ListNext on lc...");
	ListNext(lc);
	printf("\nUsing ListPrev on lc...");
	ListPrev(lc);


printf("\n----Testing Append() and Prepend()----------------------------------------\n");
	printf("\nPrepending 3 to list la... ");
	ListAppend(la, &d);
	printList(la);
	printf("\nAppending 1 to list lb... ");
	ListAppend(lb, &b);
	printList(lb);
	printf("\nAppending 1 to list lb... ");
	ListAppend(lb, &b);
	printList(lb);
	printf("\nPrepending 2 to list la... ");
	ListPrepend(la, &c);
	printList(la);
	printf("\nAppending 3 to list ld... ");
	ListAppend(ld, &d);


	printf("\nAppending 1 to list la... ");
	ListPrepend(la, &b);
	printList(la);
	printf("\nPrepending 0 to list la... ");
	ListPrepend(la, &a);
	printList(la);
	printf("\nPrepending 0 to list lc... ");
	ListPrepend(lc, &a);
	printList(lc);
	printf("\nAppending 3 to list lc... ");
	ListAppend(lc, &d);
	printList(lc);
	printf("\nCurrent in list lc is: %i", *(int*)lc->current->data);

	printf("\nAdding 2 to list lc... ");
	ListAdd(lc, &c);
	printList(lc);
	printf("\nCurrent in list lc is: %i", *(int*)lc->current->data);

	printf("\nInserting 1 to list lc... ");
	ListInsert(lc, &b);
	printList(lc);
	printf("\nCurrent in list lc is: %i", *(int*)lc->current->data);


	printf("\nAppending 2 to list la... ");
	ListAppend(lc, &a);


	
	printf("\nList lengths are: %d, %d, %d, %d.\n", ListCount(la), ListCount(lb), ListCount(lc), ListCount(ld));


printf("\n----Testing First, Last, Prev, Next on list with elements--------------------------\n");
	printf("\nUsing ListFirst on ld...");
	ListFirst(ld);
	printf("\nUsing ListLast on ld...");
	ListLast(ld);
	printf("\nUsing ListNext on ld...");
	ListNext(ld);
	printf("\nUsing ListPrev on ld...");
	ListPrev(ld);

	printf("\nCurrent of list lc is: %i", *(int*)lc->current->data);
	
	printf("\nUsing ListFirst on lc...");
	ListFirst(lc);
	printf("Current of list lc is: %i", *(int*)lc->current->data);

	printf("\nUsing ListNext on lc...");
	ListNext(lc);
	printf("Current of list lc is: %i", *(int*)lc->current->data);

	printf("\nUsing ListPrev on lc...");
	ListPrev(lc);
	printf("Current of list lc is: %i", *(int*)lc->current->data);

	printf("\nUsing ListPrev on lc...");
	if(ListPrev(lc) == NULL) printf("Current is set to NULL already at end of list\n");

	printf("\nUsing ListLast on lc...");	
	ListLast(lc);
	printf("Current of list lc is: %i", *(int*)lc->current->data);

	printf("\nUsing ListNext on lc...");
	if(ListNext(lc) == NULL) printf("Current is set to NULL already at end of list\n");




printf("\n----Testing First, Last, Prev, Next on list out of bound--------------------------\n");
	printf("\nUsing Listfirst on lc...");
	ListFirst(lc);
	printf("Current of list lc is: %i", *(int*)lc->current->data);

	printf("\nUsing ListPrev on lc...");
	ListPrev(lc);
	printf("currentRange is %i", lc->currentRange);

	printf("\nUsing ListPrev on lc...");
	ListPrev(lc);
	printf("currentRange is %i", lc->currentRange);

	printf("\nUsing ListNext on lc...");
	ListNext(lc);
	printf("currentRange is %i", lc->currentRange);

	printf("\nUsing ListPrev on lc...");
	ListPrev(lc);
	printf("currentRange is %i", lc->currentRange);

	printf("\nUsing ListFirst on lc...");
	ListFirst(lc);
	printf("currentRange is %i", lc->currentRange);

	printf("\nUsing ListPrev on lc...");
	ListPrev(lc);
	printf("currentRange is %i", lc->currentRange);

	printf("\nUsing ListLast on lc...");
	ListLast(lc);
	printf("currentRange is %i", lc->currentRange);

	printf("\nUsing ListNext on lc...");
	ListNext(lc);
	printf("currentRange is %i", lc->currentRange);

	printf("\nUsing ListNext on lc...");
	ListNext(lc);
	printf("currentRange is %i", lc->currentRange);

	printf("\nUsing ListPrev on lc...");
	ListPrev(lc);
	printf("currentRange is %i", lc->currentRange);

	printf("\nUsing ListNext on lc...");
	ListNext(lc);
	printf("currentRange is %i", lc->currentRange);

	printf("\nUsing ListLast on lc...");
	ListLast(lc);
	printf("currentRange is %i", lc->currentRange);

printf("\n----Testing ListRemove()-----------------------------------------\n");

	printf("lc: ");
	printList(lc);
		printf("Length is %d, head is %d, tail is %d, current is %d, currentRange is %d\n", lc->Length, *(int*)lc->head->data,*(int*)lc->tail->data,*(int*)lc->current->data,lc->currentRange);


	printf("\nUsing ListRemove on lc...");

	if (ListRemove(lc) == NULL) printf("currentRange is %i\n", lc->currentRange);
	printf("lc: ");
	printList(lc);

	printf("\nUsing ListRemove on lc...");
	if (ListRemove(lc) == NULL) printf("currentRange is %i", lc->currentRange);

	printf("\nUsing ListFirst on lc...");
	ListFirst(lc);

	printf("\nLength is %d, head is %d, tail is %d, current is %d, currentRange is %d\n", lc->Length, *(int*)lc->head->data,*(int*)lc->tail->data,*(int*)lc->current->data,lc->currentRange);

	printf("\nUsing ListRemove on lc...");
	if (ListRemove(lc) == NULL) printf("currentRange is %i\n", lc->currentRange);		
	printf("lc: ");
	printList(lc);
	printf("Length is %d, head is %d, tail is %d, current is %d, currentRange is %d\n", lc->Length, *(int*)lc->head->data,*(int*)lc->tail->data,*(int*)lc->current->data,lc->currentRange);


	printf("\nUsing ListRemove on lc...");
	if (ListRemove(lc) == NULL) printf("currentRange is %i\n", lc->currentRange);		
	printf("lc: ");
	printList(lc);
	printf("Length is %d, head is %d, tail is %d, current is %d, currentRange is %d\n", lc->Length, *(int*)lc->head->data,*(int*)lc->tail->data,*(int*)lc->current->data,lc->currentRange);


	printf("\nUsing ListRemove on lc...");
	if (ListRemove(lc) == NULL) printf("currentRange is %i\n", lc->currentRange);		
	printf("lc: ");
	printList(lc);
	printf("\n");
	printf("Length is %d, head is %d, tail is %d, current is %d, currentRange is %d\n", lc->Length, *(int*)lc->head->data,*(int*)lc->tail->data,*(int*)lc->current->data,lc->currentRange);


	printf("\nPrepending 1 to list la... ");
	ListPrepend(la, &b);
	printList(la);
	printf("\nPrepending 1 to list la... ");
	ListPrepend(la, &b);
	printList(la);

	printf("Current of list la is: %i", *(int*)la->current->data);
	printf("\nUsing ListRemove on la...");
	if (ListRemove(la) == NULL) printf("currentRange is %i\n", la->currentRange);
	printf("la: ");
	printList(la);

	printf("Current of list la is: %i", *(int*)la->current->data);
	printf("\nUsing ListRemove on la...");
	if (ListRemove(la) == NULL) printf("currentRange is %i\n", la->currentRange);
	printf("la: ");
	printList(la);
///!!!!!!!!!!!!!
	printf("\nlc: ");
	printList(lc);
	printf("Length is %d, head is %d, tail is %d, current is %d, currentRange is %d\n", lc->Length, *(int*)lc->head->data,*(int*)lc->tail->data,*(int*)lc->current->data,lc->currentRange);



	printf("\nPrepending 0 to list lc... ");
	ListPrepend(lc, &a);
	printList(lc);
	printf("Length is %d, head is %d, tail is %d, current is %d, currentRange is %d\n", lc->Length, *(int*)lc->head->data,*(int*)lc->tail->data,*(int*)lc->current->data,lc->currentRange);


	printf("\nAppending 3 to list lc... ");
	ListAppend(lc, &d);
	printList(lc);
	printf("Length is %d, head is %d, tail is %d, current is %d, currentRange is %d\n", lc->Length, *(int*)lc->head->data,*(int*)lc->tail->data,*(int*)lc->current->data,lc->currentRange);

	printf("\nAdding 2 to list lc... ");
	ListAdd(lc, &c);
	printList(lc);
	printf("Length is %d, head is %d, tail is %d, current is %d, currentRange is %d\n", lc->Length, *(int*)lc->head->data,*(int*)lc->tail->data,*(int*)lc->current->data,lc->currentRange);


	printf("\nInserting 1 to list lc... \n");
	ListInsert(lc, &b);
	printList(lc);


	printf("\nUsing ListFirst on lb...");
	ListFirst(lb);
	printf("currentRange is %i", lb->currentRange);
	printf("\nUsing ListRemove on lb...");
	if (ListRemove(lb) == NULL) printf("currentRange is %i\n", lb->currentRange);		
	printf("lb: ");
	printList(lb);
	printf("\nUsing ListRemove on lb...");
	if (ListRemove(lb) == NULL) printf("currentRange is %i\n", lb->currentRange);		
	printf("lb: ");
	printList(lb);

printf("\n----Testing ListConcat()-----------------------------------------\n");
	printf("lc: ");
	printList(lc);
	printf("lc head is: %i, lc tail is: %i.\n", *(int*)lc->head->data, *(int*)lc->tail->data);		


	printf("Using Listconcat(lc,lb)\n");
	ListConcat(lc,lb);
	printf("lc: ");
	printList(lc);
	printf("Trying lb...");
	ListFirst(lb);

	printf("lc: ");
	printList(lc);
	printf("la: ");
	printList(la);

	printf("la head is: %i, la tail is: %i.\n", *(int*)la->head->data, *(int*)la->tail->data);
	printf("lc head is: %i, lc tail is: %i.\n", *(int*)lc->head->data, *(int*)lc->tail->data);		
		

	printf("Using Listconcat(lc,la)\n");
	ListConcat(lc,la);
	printf("lc: ");
	printList(lc);
	printf("Trying la...");
	ListFirst(la);



	printf("\nCreating list d... ");
	ld = ListCreate();
printf("\n----Testing ListTrim()-----------------------------------------\n");
	printf("Using ListTrim on ld\n");
	ListTrim(ld);

	printf("lc: ");
	printList(lc);
	printf("Using ListTrim1 on lc ... ");
	ListTrim(lc);
	printList(lc);	
	printf("Using ListTrim2 on lc ... ");
	ListTrim(lc);
	printList(lc);	
	printf("Using ListTrim3 on lc ... ");
	ListTrim(lc);
	printList(lc);	

printf("\n----Testing ListSearch()-----------------------------------------\n");
	printf("lc: ");
	printList(lc);	
	printf("\nUsing ListFirst on lc...");
	ListFirst(lc);

	printf("\nSearching for %i in lc ... found: %i", d, *(int*)ListSearch(lc, &comparator, &d));
	printf("\nSearching for %i in lc ... found: %i", d, *(int*)ListSearch(lc, &comparator, &d));
	printf("\nUsing ListNext on lc...");
	ListNext(lc);
	*(int*)ListSearch(lc, &comparator, &d);
	if(lc->current==NULL)	printf("\nSearching for %i in lc ... Not found!", d);
	*(int*)ListSearch(lc, &comparator, &d);
	if(lc->current==NULL)	printf("\nSearching for %i in lc ... Not found!", d);

printf("\n----Testing ListFree()-----------------------------------------\n");
	
	printf("creating temp varaible -1 in heap\n");
	int * temp = malloc(sizeof(int));

	printf("Appending temp tp ld\n");
	*temp = -1;
	ListAppend(ld, temp);

	printf("ld: ");
	printList(ld);

	printf("Running ListFree on ld\n");
	ListFree(ld, &itemFree);

	printf("Trying to print temp!");

	if(*temp == NULL) printf("\nNULLNULLNULL\nend of test\n");

	printf("\n");
	return 0;

}
