#include "list.h"
#include <stddef.h>
#include <stdbool.h> 
#include <stdio.h>

#define nodeListSize 20
#define headListSize 20
Node nodeList[nodeListSize];
LIST headList[headListSize];


//makes a new, empty list, and returns its reference on
//success. Returns a NULL pointer on failure.
LIST *ListCreate() {

    LIST *newList;        

    //The user will only be able to create headListSize-1 lists
    if(headList[0].headArrayLength == headListSize-1){
        printf("You cannot create any more lists.\n");
        //list of heads is full
        return NULL;   
    }

    //the first index of headList is used to keep track of free list heads and free nodes with a list of its own
    //This list is initialized only on the first time the user creates a list
    if(headList[0].headArrayLength==0){
        for(int i = 0; i < headListSize-1; i++){
            headList[i].next = &headList[i+1];
        }
        headList[0].head = &nodeList[0];
        for(int i = 0; i < nodeListSize-1; i++){
            nodeList[i].next = &nodeList[i+1];
        }
        nodeList[nodeListSize-1].next = NULL;
    }

    newList = headList[0].next;
    if(headList[0].headArrayLength >= headListSize-1){
        headList[0].next = NULL;
    } else {
        headList[0].next = headList[0].next->next;
    }
    headList[0].headArrayLength++;
    return newList;
}

//returns the number of items in list.
int ListCount(LIST *list) {
    int size = (*list).length;
    return size;
}

//returns a pointer to the first item in list and makes
//the first item the current item.
void *ListFirst(LIST *list) {
    list->current = list->head;
    list->beyondEnd = false;
    list->beyondStart = false;
    return list->head->data;
}

//returns a pointer to the last item in list and makes
//the last item the current one.
void *ListLast(LIST *list) {
    list->current = list->last;
    list->beyondEnd = false;
    list->beyondStart = false;
    return list->current->data;
}

//advances list's current item by one, and returns a
//pointer to the new current item. If this operation advances the current item beyond
//the end of the list, a NULL pointer is returned and the beyondEnd flag is set to True.
void *ListNext(LIST *list) {
    if(!list->beyondEnd){
        if(list->current != list->last){
            list->current=list->current->next;
        return list->current->data;
        }
    }
    //While the current pointer is before the first element, calling listNext will 
    //bring the pointer back into the list, pointing to the first element
    if(list->beyondStart){
        list->beyondStart = false;
        return ListFirst(list);
    }
    //current pointer points to last element
    list->beyondEnd = true;
    printf("You are beyond the last element\n");
    return NULL;
}

//backs up list's current item by one, and returns a
//pointer to the new current item. If this operation backs up the current item beyond
//the start of the list, a NULL pointer is returned and the beyondStart flag is set to True.
void *ListPrev(LIST *list) {
    if(!list->beyondStart){
        if(list->current != list->head){
            list->current=list->current->prev;
        return list->current->data;
        }
    }
    //While the current pointer is past the first element, calling ListPrevwill 
    //bring the pointer back into the list, pointing to the last element
    if(list->beyondEnd){
        list->beyondEnd = false;
        return ListLast(list);
    }
    //current pointer points to first element
    list->beyondStart = true;
    printf("You are beyond the first element\n");
    return NULL;
}

//returns a pointer to the current item in list.
void *ListCurr(LIST *list) {
        return list->current->data;
}

//adds the new item to list directly after the
//current item, and makes item the current item. If the current pointer is before the
//start of the list, the item is added at the start. If the current pointer is beyond the
//end of the list, the item is added at the end. Returns 0 on success, -1 on failure.
int ListAdd(LIST *list, void *item) {

    if(headList[0].head==NULL){
        //free nodes are used up
        printf("You cannot add any more items\n");
        return -1;
    }

    if(!list){
        printf("List does not exist\n");
        return -1;
    }

    if(list->length<=0){
        //empty list
        list->head = headList[0].head;
        headList[0].head = headList[0].head->next;
        list->head->next = NULL;
        list->head->prev = NULL;
        list->current = list->head;
        list->last = list->head;
    } else if(list->beyondStart) {
        //current pointer is before start
        Node *newNode = headList[0].head;
        headList[0].head = headList[0].head->next;
        newNode->next = list->head;
        newNode->prev = NULL;
        list->head->prev = newNode;
        list->head = newNode;
        list->current = newNode;
    } else if(list->beyondEnd || list->current == list->last) {
        //current pointer is last item, or is after last item
        Node *newNode = headList[0].head;
        headList[0].head = headList[0].head->next;
        newNode->next = NULL;
        newNode->prev = list->last;
        list->last->next = newNode;
        list->last = newNode;
        list->current = newNode;
    } else{
        Node *newNode = headList[0].head;
        headList[0].head = headList[0].head->next;        
        newNode->next = list->current->next;
        newNode->prev = list->current;
        list->current->next = newNode;
        newNode->next->prev = newNode;
        list->current = newNode;
    }
    headList[0].nodeArrayLength++;
    list->current->data = item;
    list->length++;
    return 0;
}

//adds item to list directly before the current
//item, and makes the new item the current one. If the current pointer is before the
//start of the list, the item is added at the start. If the current pointer is beyond the
//end of the list, the item is added at the end. Returns 0 on success, -1 on failure.
int ListInsert(LIST *list, void *item) {
    if(headList[0].head == NULL){
        //free nodes are used up
        printf("You cannot add any more items\n");
        return -1;
    }
    if(!list){
        printf("List does not exist\n");
        return -1;
    }
    if(list->length<=0){
        //empty list
        list->head = headList[0].head;
        headList[0].head = headList[0].head->next;
        list->head->next = NULL;
        list->head->prev = NULL;       
        list->current = list->head;
        list->last = list->head;
    } else if(list->beyondStart || list->current == list->head) {
        //current pointer is before start, or is start
        Node *newNode = headList[0].head;
        headList[0].head = headList[0].head->next;
        newNode->next = list->head;
        newNode->prev = NULL;
        list->head->prev = newNode;
        list->head = newNode;
        list->current = newNode;
    } else if(list->beyondEnd) {
        //current pointer is after last node
        Node *newNode = headList[0].head;
        headList[0].head = headList[0].head->next;
        newNode->next = NULL;
        newNode->prev = list->last;
        list->last->next = newNode;
        list->last = newNode;
        list->current = newNode;
    } else{
        Node *newNode = headList[0].head;
        headList[0].head = headList[0].head->next;
        newNode->next = list->current;
        newNode->prev = list->current->prev;
        list->current->prev = newNode;
        newNode->prev->next = newNode;
        list->current = newNode;
    }
    headList[0].nodeArrayLength++;
    list->current->data = item;
    list->length++;
    
    return 0;
}

//adds item to the end of list, and makes the
//new item the current one. Returns 0 on success, -1 on failure.
int ListAppend(LIST *list, void *item) {
    if(headList[0].head == NULL){
        //free nodes are used up
        printf("You cannot add any more items\n");
        return -1;
    }
    if(!list){
        printf("List does not exist\n");
        return -1;
    }
    if(list->length<=0){
        //empty list
        list->head = headList[0].head;
        headList[0].head = headList[0].head->next;
        list->head->next = NULL;
        list->head->prev = NULL;    
        list->current = list->head;
        list->last = list->head;
    } else{
        Node *newNode = headList[0].head->next;
        headList[0].head = newNode->next;
        newNode->next = NULL;
        newNode->prev = list->last;
        list->last->next = newNode;
        list->last = newNode;
        list->current = newNode;
    }
    headList[0].nodeArrayLength++;
    list->current->data = item;
    list->length++;
    
    return 0;
}

//adds item to the front of list, and makes
//the new item the current one. Returns 0 on success, -1 on failure.
int ListPrepend(LIST *list, void *item) {
    if(headList[0].head == NULL){
        //free nodes are used up
        printf("You cannot add any more items\n");
        return -1;
    }
    if(!list){
        printf("List does not exist\n");
        return -1;
    }
    if(list->length<=0){
        //empty list
        list->head = headList[0].head;
        headList[0].head = headList[0].head->next;
        list->head->next = NULL;
        list->head->prev = NULL;  
        list->current = list->head;
        list->last = list->head;
    } else{
        Node *newNode = headList[0].head;
        headList[0].head = newNode->next;
        newNode->next = list->head;
        newNode->prev = NULL;
        list->head->prev = newNode;
        list->head = newNode;
        list->current = list->head;
    }
    headList[0].nodeArrayLength++;
    list->current->data = item;
    list->length++;
    
    return 0;
}

//Return current item and take it out of list. Make
//the next item the current one.
void *ListRemove(LIST *list) {
    if(list->head == NULL){
        //empty list
        return list->current;
    }
    if(!list){
        printf("List does not exist\n");
        return list->current;
    }

    Node *tmp = list->current;
    list->current = list->current->next;

    if(tmp != NULL){
        if(list->length==1){
            if(headList[0].head!=NULL){
                tmp->next = headList[0].head;
                headList[0].head->prev = tmp;
            } else{
                tmp->next = NULL;
            }
            tmp->prev = NULL;
            headList[0].head = tmp;
            list->head==NULL;
            list->last==NULL;
        } else {
            if(tmp == list->head){
                //current pointer points to first item in list
                list->head = list->current;
                list->current->prev = NULL;
            }else if(tmp == list->last){
                //current pointer points to last item in list
                list->last = tmp->prev;
                list->beyondEnd = true;
            } else {
                tmp->prev = tmp->next;
                tmp->next = tmp->prev;
            }
            if(headList[0].head!=NULL){
                //free list heads are used up
                tmp->next = headList[0].head;
                tmp->prev = NULL;
                tmp->next->prev = tmp;
                headList[0].head = tmp; 
            } else {
                tmp->next = NULL;
                tmp->prev = NULL;
                headList[0].head = tmp; 
            }
        }
    }
    headList[0].nodeArrayLength--;
    list->length--;
    return tmp->data;
}

//adds list2 to the end of list1. The
//current pointer is set to the current pointer of list1. List2 no longer exists after the
//operation.
void ListConcat(LIST *list1,LIST *list2) {
    if(list1 && list2){
        //both lists exist
        list1->last->next = list2->head;
        list2->head->prev = list1->last;
        list1->length += list2->length;

        list2->head = NULL;
        list2->last = NULL;
        list2->current=NULL;

        list2->next = headList[0].next;
        headList[0].headArrayLength--;
        headList[0].next = list2;
    } else {
        printf("Error: Please ensure both lists exist\n");
    }
}

//delete list. itemFree is a pointer to a
//routine that frees an item. It should be invoked (within ListFree) as:
//(*itemFree)(itemToBeFreed);
void ListFree(LIST *list, void (*itemFree)(void *)) {
    if(list){
    //list exists
        if(list->length>0){
            //non-empty list
            list->current = list->head;
            while(list->current != NULL){
                (*itemFree)(list->current->data);
                ListRemove(list);
            }
        }
        headList[0].next = list;
        headList[0].headArrayLength++;
    }
}

//Return last item and take it out of list. Make the
//new last item the current one.
void *ListTrim(LIST *list) {
    if(list->head != NULL){
    //list not empty
        Node *tmp = list->last;
        if(list->length==1){
            tmp->next = headList[0].head;
            tmp->prev = NULL;
            headList[0].head->prev = tmp;
            headList[0].head = tmp;
            list->head==NULL;
            list->last==NULL;
        } else {
            list->last = tmp->prev;
            list->last->next = NULL;

            tmp->next = headList[0].head;
            tmp->prev = NULL;
            headList[0].head = tmp;
            if(headList[0].nodeArrayLength == nodeListSize){
                //free nodes are used up prior to trimming
                tmp->next = NULL;
            } else {
                tmp->next->prev = tmp;
            }
        }
        headList[0].nodeArrayLength--;
        list->current = list->last;
        list->length--;
        return tmp->data;
    }
}

//searches list starting at the current item until the end is reached or a match is found.
void *ListSearch(LIST *list, int (*comparator)(void *, void *), void *comparisonArg) {
    int match = 0;
    list->current = list->head;
    while(list->beyondEnd==false && match == 0){
        match = comparator(list->current->data, comparisonArg);
        if(match==0){
            ListNext(list);
        } else {
            printf("Item found!\n");
            return list->current;
        }
    }    
    printf("Item not found!\n");
    return list->current;
}