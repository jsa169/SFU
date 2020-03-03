#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node * next;
} node_t;

typedef struct {
    node_t * head;
    node_t * tail;
} LL_t;

LL_t * LLcreate() {
    LL_t * ret = malloc(sizeof(LL_t));
    ret->head = NULL;
    ret->tail = NULL;
    return ret;
}

void LLappend(LL_t * intlist, int value) {
    node_t * newNode = malloc(sizeof(node_t));

    newNode->data = value;
    newNode->next = NULL;

    if (intlist->head == NULL) {
        intlist->head = newNode;
        intlist->tail = newNode;
    } else {
        intlist->tail->next = newNode;
        intlist->tail = newNode;
    }
}

void LLprint(LL_t * intlist){
	node_t * current = intlist->head;
	while (current != NULL){
		printf(" %d", current->data);
		current = current->next;
	}
	putchar('\n');
}

int LLMax(LL_t * intlist){
	//Set first note to be max
	int max = intlist->head->data;
	//Keep track of current
	node_t * current = intlist->head->next;
	//Go through LL
	while (current != NULL){
		//If current > max, replace
		if(current->data > max){
			max = current->data;
		}
		current = current->next;
	}
	return max;
}

void LLDelete(LL_t * intlist, int target){
	int n = 0;
	//Keep track of both current and previous nodes
	node_t * current = intlist->head;
	node_t * previous;

	while(current != NULL){
		//Deleting a node if its the first node of LL, Change Head to next node
		if(intlist->head == current){
			if(current->data == target){
				intlist->head = current->next;
				current = current->next;
				previous = current;
				n++;
				continue;
			}
		}
		//Deleting nodes inside the LL without touching head
		if(current->data == target){
			previous->next = current->next;
			free(current);
			n++;
		}
		
		previous = current;
		current = current->next;
	}
	//Signals target not found
	if(n == 0){
		printf("Value not Found\n");
	}

}

int main (){
	LL_t * intlist = LLcreate();
	if (intlist == NULL){
		return 1;
	}
	
	LLappend(intlist, 100);
	LLappend(intlist, 100);
	LLappend(intlist, 5);
	LLappend(intlist, 100);
	LLappend(intlist, -100);
	LLappend(intlist, 2019);
	LLappend(intlist, 100);
	
	LLprint(intlist);
	LLDelete(intlist,100);
	
	int max = LLMax(intlist);
	

	printf("max is %d\n", max);
	LLprint(intlist);

}