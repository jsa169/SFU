//function.c

#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int comparator(void *a, void *b){
	if ( *(int*)a == *(int*)b ) return 1;
	return 0;
}

PCB * new_PCB(int PID, int priority, int status){
	PCB * new_proc = malloc(sizeof(PCB));	
	new_proc->PID = PID;
	new_proc->priority = priority;	
	new_proc->status = status;
	return new_proc;
}

void printPCB(PCB * a){
	printf("\tProccess ID: %i\t", a->PID);
	if(a->priority == 0) printf("Priority: High\t");
	if(a->priority == 1) printf("Priority: Normal\t");
	if(a->priority == 2) printf("Priority: Low     \t");

	if(a->status == -1) printf("Status: Blocked\t");
	if(a->status == 0) printf("Status: Ready\t");
	if(a->status == 1) printf("Status: Running\t");

	if(a->msg == 1) printf("Has stored message.\n");
	if(a->msg == 0) printf("No stored message.\n");
}