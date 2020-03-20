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

	//if(a->wait == 0) printf("Not Waiting for message or reply.");

	if(a->needtoreply != 0) printf("-Please reply to process %i.   ", a->sender);
	//if(a->sender == 0) printf("Don't need to reply.");

	//if(a->smp == 0) printf("Not Blocked by semaphore.\n");
	if(a->smp != 0) printf("-Blocked by semaphore %i"   , a->smp);
	printf("\n");

}

SMP * new_SMP(int SID, int val){
	SMP * new_semaphore = malloc(sizeof(SMP));
	new_semaphore->SID = SID;
	new_semaphore->val = val;
	new_semaphore->proc = ListCreate();
	return new_semaphore;
}
