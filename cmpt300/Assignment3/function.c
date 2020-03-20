/*File: function.c

Date: 2020-03-20

Auther: Jichuan

Description: Include PCB and Semaphore structure*/

#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int comparator(void *a, void *b){//comparitor for searching in the lists
	if ( *(int*)a == *(int*)b ) return 1;
	return 0;
}

PCB * new_PCB(int PID, int priority, int status){//Create new PCB
	PCB * new_proc = malloc(sizeof(PCB));	
	new_proc->PID = PID;
	new_proc->priority = priority;	
	new_proc->status = status;
	msg = 0;
	waitformessage = 0;
	waitforreply = 0
	smp = 0;
	sender = 0;
	needtoreply = 0;
	return new_proc;
}

void printPCB(PCB * a){//Print out information about current PCB
	printf("  Proccess ID: %i\t", a->PID);
	if(a->priority == 0) printf("-Priority: High   ");
	if(a->priority == 1) printf("-Priority: Norm   ");
	if(a->priority == 2) printf("-Priority: Low    ");

	if(a->status == -1) printf("-Status: Blocked   ");
	if(a->status == 0)  printf("-Status: Ready     ");
	if(a->status == 1)  printf("-Status: Running   ");

	if(a->msg == 1) printf("-Unread message.   ");

	if(a->waitformessage != 0) printf("-Waiting for message.   ");
	if(a->waitforreply != 0) printf("-Waiting for reply.   ");
	if(a->needtoreply != 0) printf("-Please reply to process %i.   ", a->sender);
	if(a->smp != 0) printf("-Blocked by semaphore %i"   , a->smp);
	printf("\n");

}

SMP * new_SMP(int SID, int val){//Create new Semaphore
	SMP * new_semaphore = malloc(sizeof(SMP));
	new_semaphore->SID = SID;
	new_semaphore->val = val;
	new_semaphore->proc = ListCreate();
	return new_semaphore;
}
