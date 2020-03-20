/*File: function.h

Date: 2020-03-20

Auther: Jichuan

Description: Includes PCB and Semaphore structure*/

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef struct PCB { //PCB structure
	int PID; //Process ID
	int priority; //0 high, 1 norm, 2 low
	int status; //-1 blocked, 0 ready, 1 running
	
	int msg; //1 has message, 0 no message
	int waitformessage; // Waiting for message, 0 = not waiting
	int waitforreply; //Waiting for reply, 0 = not waiting
	int smp; //Blocked by semaphore ID, 0 = no semaphore
	int sender; //PID of sender, 0 = no sender
	int needtoreply; //Need to reply to sender, 0 = Dont need  to reply
	char message[101];
}PCB;

int comparator(void *item, void *comparisonArg); //comparitor for searching in the lists

PCB * new_PCB(int PID, int priority, int status); //Create new PCB

void printPCB(PCB * a); //Print out information about current PCB

typedef struct Semaphore { // Semaphore Structure
	int SID; //Semaphore ID
	int val;
	LIST * proc; // List of blocked process
}SMP;

SMP * new_SMP(int SID, int val); //Create new Semaphore

