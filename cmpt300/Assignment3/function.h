//function.h
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef struct PCB {
	int PID; //Process ID
	int priority; //0 high, 1 norm, 2 low
	int status; //-1 blocked, 0 ready, 1 running
	
	int msg; //1 has message, 0 no message
	int sender; //PID of sender
	char message[100];
}PCB;

int comparator(void *item, void *comparisonArg);

PCB * new_PCB(int PID, int priority, int status);

void printPCB(PCB * a);

typedef struct Semaphore {
	int SID; //Semaphore ID
	int val;
	LIST * proc; // List of blocked process
}SMP;
