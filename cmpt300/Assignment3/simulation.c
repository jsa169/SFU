//simulation.c
#include <stdio.h>
#include <stdlib.h>
#include "function.h"


LIST * ReadyQ_High;
LIST * ReadyQ_Norm;
LIST * ReadyQ_Low;
LIST * SendQ;
LIST * RecvQ;
int proc_count;
PCB * current_proc;
int parameter;


void create(int priority, int status){

	PCB * new_proc = new_PCB(proc_count+1, priority, status);
	if(new_proc == NULL) {
		printf("Process Creation failed.\n");
		return;
	}
	proc_count++;

	if(priority == 2) ListPrepend(ReadyQ_Low, new_proc);
	if(priority == 1) ListPrepend(ReadyQ_Norm, new_proc);
	if(priority == 0) ListPrepend(ReadyQ_High, new_proc);

	if (proc_count != 1) printf("Proccess Created: \n");
	printPCB(new_proc);

}

void Fork(){

}

void Kill(int PID){

}

void Exit(){

}

void Quantum(){
	int a;
	if (current_proc->status == -1) ListPrepend(ReadyQ_High, current_proc);//if blocked -> High
	if (current_proc->PID == 1) {//if ini P -> Low
		current_proc->status = 0;
		ListPrepend(ReadyQ_Low, current_proc);
	}
	else {//if not blocked -> Norm
		ListPrepend(ReadyQ_Norm, current_proc);
		current_proc->status = 0;

	}

	a = ListCount(ReadyQ_High); //Get High priority process
	while(a != 0){
		current_proc = ListTrim(ReadyQ_High);
		if (current_proc->status == 0) break;
		ListPrepend(ReadyQ_High, current_proc);
		a--;
	}

	if(a == 0){ //Get Normal priority process
		a = ListCount(ReadyQ_Norm);

		while(a != 0){
			current_proc = ListTrim(ReadyQ_Norm);
			if (current_proc->status == 0) break;
			ListPrepend(ReadyQ_High, current_proc);
			a--;
		}

		if(a == 0){
			current_proc = ListTrim(ReadyQ_Low);
		}
	}
	current_proc->status = 1;
	printf("Current running process:\n");
	printPCB(current_proc);

}

void Send(int PID, char * msg){

}

void Receive(){

}

void Reply(int PID, char * msg){

}

void NewSemaphore(int SID, int val){

}

void SemaphoreP(int SID){

}

void SemaphoreV(int SID){

}

void Proinfo(int PID){
	printf("----------------------------------------------------------------------\n");
	
	PCB * Pinfo;

	if(PID == current_proc->PID) {
		Pinfo = current_proc;
	}else {
		ListFirst(ReadyQ_High);
		Pinfo = ListSearch(ReadyQ_High, comparator, &PID);
		if (Pinfo == NULL) {
			printf("here\n");
			ListFirst(ReadyQ_Norm);
			Pinfo = ListSearch(ReadyQ_Norm, comparator, &PID);
			if(Pinfo == NULL){
				ListFirst(ReadyQ_Low);
				Pinfo = ListSearch(ReadyQ_Low, comparator, &PID);
			}
		}
	}
	if (Pinfo == NULL){
		printf("Process not found\n.");
		return;
	}
	printPCB(Pinfo);
}

void TotalInfo(){
	printf("----------------------------------------------------------------------");
	printf("\nCurrent running process:\n");
	printPCB(current_proc);

	printf("\nHigh priority processes:\n");
	PCB * current;
	current = ListLast(ReadyQ_High);
	while(current != NULL){
		printPCB(current);
		current = ListPrev(ReadyQ_High);	}

	printf("\nNormal priority processes:\n");
	current = ListLast(ReadyQ_Norm);
	while(current != NULL){
		printPCB(current);
		current = ListPrev(ReadyQ_Norm);	}

	printf("\nLow priority processes:\n");
	current = ListLast(ReadyQ_Low);
	while(current != NULL){
		printPCB(current);
		current = ListNext(ReadyQ_Low);
	}
	printf("\n");

}


int main(){
	char command;
	proc_count = 0;

	ReadyQ_High = ListCreate();
	ReadyQ_Norm = ListCreate();
	ReadyQ_Low = ListCreate();

	SendQ = ListCreate();
	RecvQ = ListCreate();

	printf("Creating initial process...\n");
	create(2,1); //create(low priority, ready)

	current_proc = ListTrim(ReadyQ_Low);
	
	while(1){
		printf("Please input choice!!!:");
		
		command = getchar();
		if(command != '\n'){
			while(getchar() != '\n');			
		}
		switch(command){

			case 'C':
				create(1,0);//create(priority, status)
				break;
			case 'F':
				break;

			case 'K':
				break;

			case 'E':
				break;

			case 'Q':
				Quantum();
				break;

			case 'S':
				break;

			case 'R':
				break;

			case 'Y':
				break;

			case 'N':
				break;

			case 'P':
				break;

			case 'V':
				break;

			case 'I':
				printf("Please enter the PID to show info: ");
				scanf("%d", &parameter);
				getchar();
				Proinfo(parameter);
				break;

			case 'T':
				TotalInfo();
				break;

			default:
				break;
		}
	   //fflush(stdin);

	}




	return 0;
}