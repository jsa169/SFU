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