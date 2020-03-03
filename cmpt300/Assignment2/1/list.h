#include <stdbool.h> 

typedef struct _node {
    void *data;
    struct _node * next;
    struct _node * prev;
} Node;

typedef struct _list {
    Node *head;
    Node *last;

    Node *current;

    bool beyondStart;
    bool beyondEnd;
    
    //length of user-created list
    int length;

    //Arrays represent nodes/heads that are in use
    int nodeArrayLength;
    int headArrayLength;

    //points to next free list head
    struct _list * next;
} LIST;

LIST *ListCreate();

//returns the number of items in list.
int ListCount(LIST *list);

//returns a pointer to the first item in list and makes
//the first item the current item.
void *ListFirst(LIST *list);

//returns a pointer to the last item in list and makes
//the last item the current one.
void *ListLast(LIST *list);

//the end of the list, a NULL pointer is returned.
void *ListNext(LIST *list);

//backs up list's current item by one, and returns a
//pointer to the new current item. If this operation backs up the current item beyond
//the start of the list, a NULL pointer is returned.
void *ListPrev(LIST *list);

//returns a pointer to the current item in list.
void *ListCurr(LIST *list);

//adds the new item to list directly after the
//current item, and makes item the current item. If the current pointer is before the
//start of the list, the item is added at the start. If the current pointer is beyond the
//end of the list, the item is added at the end. Returns 0 on success, -1 on failure.
int ListAdd(LIST *list, void *item);

//adds item to list directly before the current
//item, and makes the new item the current one. If the current pointer is before the
//start of the list, the item is added at the start. If the current pointer is beyond the
//end of the list, the item is added at the end. Returns 0 on success, -1 on failure.
int ListInsert(LIST *list,void *item);

//adds item to the end of list, and makes the
//new item the current one. Returns 0 on success, -1 on failure.
int ListAppend(LIST *list, void *item);

//adds item to the front of list, and makes
//the new item the current one. Returns 0 on success, -1 on failure.
int ListPrepend(LIST *list, void *item);

//Return current item and take it out of list. Make
//the next item the current one.
void *ListRemove(LIST *list);

//adds list2 to the end of list1. The
//current pointer is set to the current pointer of list1. List2 no longer exists after the
//operation.
void ListConcat(LIST *list1,LIST *list2);

//delete list. itemFree is a pointer to a
//routine that frees an item. It should be invoked (within ListFree) as:
//(*itemFree)(itemToBeFreed);
void ListFree(LIST *list, void (*itemFree)(void *));
//Return last item and take it out of list. Make the
//w last item the current one.
void *ListTrim(LIST *list);

//searches list starting at the current item until the end is reached or a match is found.
void *ListSearch(LIST *list, int (*comparator)(void *, void *), void *comparisonArg);