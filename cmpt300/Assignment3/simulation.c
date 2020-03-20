//simulation.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"



LIST * ReadyQ_High;
LIST * ReadyQ_Norm;
LIST * ReadyQ_Low;
SMP * Semaphore_List[6] = {NULL};
//LIST * RecvQ;
int proc_count;
int SMP_count;
PCB * current_proc;
int parameter;
int parameter2;
char message[101];

void TotalInfo(){
	printf("\033[0m-------------------------------------------\033[0;32m\n");

	PCB * current;

	printf("Total process: %i\n", proc_count);

	printf("\nCurrent process:\n");
	printPCB(current_proc);
	
	printf("\nHigh priority processes (%i): \n", ListCount(ReadyQ_High));
	current = ListFirst(ReadyQ_High);
	while(current != NULL){
		printPCB(current);
		current = ListNext(ReadyQ_High);	
	}

	printf("\nNormal priority processes (%i): \n", ListCount(ReadyQ_Norm));
	current = ListFirst(ReadyQ_Norm);
	while(current != NULL){
		printPCB(current);
		current = ListNext(ReadyQ_Norm);	
	}	

	printf("\nLow priority processes (%i): \n", ListCount(ReadyQ_Low));
	current = ListFirst(ReadyQ_Low);
	while(current != NULL){
		printPCB(current);
		current = ListNext(ReadyQ_Low);		
	}

	printf("\n");

}

PCB * SearchAll(int PID){
	PCB * Pinfo;

	if(PID == current_proc->PID) {
		Pinfo = current_proc;
	}else {
		ListFirst(ReadyQ_High);
		Pinfo = ListSearch(ReadyQ_High, comparator, &PID);
		if (Pinfo == NULL) {
			ListFirst(ReadyQ_Norm);
			Pinfo = ListSearch(ReadyQ_Norm, comparator, &PID);
			if(Pinfo == NULL){
				ListFirst(ReadyQ_Low);
				Pinfo = ListSearch(ReadyQ_Low, comparator, &PID);
			}
		}
	}
	return Pinfo;
}

PCB * create(int priority, int status){

	PCB * new_proc = new_PCB(proc_count+1, priority, status);
	if(new_proc == NULL) {
		printf("WARNING!: Process Creation failed.\n");
		return NULL;
	}
	proc_count++;

	if(priority == 2) ListAppend(ReadyQ_Low, new_proc);
	if(priority == 1) ListAppend(ReadyQ_Norm, new_proc);
	if(priority == 0) ListAppend(ReadyQ_High, new_proc);

	printf("\033[0m-------------------------------------------\033[0;32m\n"
		" The following proccess is created: \n");
	printPCB(new_proc);
	return new_proc;

}

void Fork(){
	if(current_proc->PID == 1){
		printf("WARNING!: Cannot fork initial process.\n");
		return;
	}
	PCB * fork_proc = create(current_proc->priority,current_proc->status);
	memcpy(fork_proc, current_proc, sizeof(PCB));
	fork_proc->PID = proc_count;
	fork_proc->status = 0;
	fork_proc->needtoreply = 0;
	printf("Successfully forked: \n");
	printPCB(fork_proc);
}

void Quantum(){

	int lastprocess;
	int a;

	if(current_proc == NULL) lastprocess = -1;
	else lastprocess = current_proc->PID;

	if(current_proc != NULL){
		if(current_proc->status != -1 && current_proc->msg == 0 && current_proc->waitformessage == 0
		&& current_proc->needtoreply == 0 && current_proc->waitforreply == 0 && current_proc->PID != 1){
			current_proc->priority = 1;
		}

		if (current_proc->PID == 1) {//if ini P -> Low
			current_proc->status = 0;
			ListAppend(ReadyQ_Low, current_proc);
		}else{

			if (current_proc->status == -1 || current_proc->priority == 0) {
				ListAppend(ReadyQ_High, current_proc);//if blocked -> High
			}else{//if not blocked -> Norm
				ListAppend(ReadyQ_Norm, current_proc);
			}
		}
		if(current_proc->status != -1) current_proc->status = 0;

	}
	a = ListCount(ReadyQ_High); //Get High priority process
	while(a != 0){
		ListFirst(ReadyQ_High);
		current_proc = ListRemove(ReadyQ_High);
		if (current_proc->status == 0 && current_proc->PID != lastprocess && proc_count > 2) {
			
			break;
		}
		ListAppend(ReadyQ_High, current_proc);
		a--;
	}

	if(a == 0){ //Get Normal priority process
		a = ListCount(ReadyQ_Norm);

		while(a != 0){
			ListFirst(ReadyQ_Norm);
			current_proc = ListRemove(ReadyQ_Norm);
			if (current_proc->status == 0) break;
			ListAppend(ReadyQ_High, current_proc);
			a--;
		}

		if(a == 0){
			ListFirst(ReadyQ_Low);
			current_proc = ListRemove(ReadyQ_Low);
		}
	}
	current_proc->status = 1;
	printf("\033[0;32m");
	printf(" Current running process:\n");
	printPCB(current_proc);
	printf("\033[0m");

}

void Kill(int PID){
	PCB * to_be_killed = SearchAll(PID);

	if(to_be_killed == NULL){
		printf("Cannot find the PID to delete.\n");
		return;
	}

	if (to_be_killed == current_proc) {
		if(to_be_killed->priority == 2){
			if(proc_count != 1) {
				printf("Cannot Kill initial process, other process(es) still running. \n");
				return;
			}	
			ListRemove(ReadyQ_Low);
			proc_count--;
			exit(1);
		}
		free(current_proc);
		current_proc = NULL;
		proc_count--;
		Quantum();
		return;
	}
	if(to_be_killed->priority == 0) ListRemove(ReadyQ_High);
	else if(to_be_killed->priority == 1) ListRemove(ReadyQ_Norm);
	else if(to_be_killed->priority == 2){
		if(proc_count != 1) {
			printf("Cannot Kill initial process, other process(es) still running. \n");
			return;
		}	
		ListRemove(ReadyQ_Low);
		exit(1);
	}
	proc_count--;
}

void Exit(){
	Kill(current_proc->PID);
}

void Send(int PID, char * msg){
	PCB * receive_proc = SearchAll(PID);
	if(receive_proc == NULL){
		printf(" Receiving PID does not exist.\n");
		return;
	}
	if(current_proc->PID == 1){
		printf(" Cannot send message from initial process.\n");
		return;
	}
	if(current_proc->status == -1){
		printf(" Cannot send, current process is blocked.\n");
		return;
	}
	if(PID == 1){
		printf(" Cannot send message to initial process.\n");
		return;
	}
	if(receive_proc->msg == 1){
		printf(" Cannot send, receiver has unreceived message.\n");
		return;	
	}
	if(receive_proc->status == -1 && receive_proc->smp != 0){
		printf(" Cannot send, receiver is currently blocked by a semaphore.\n");
		return;
	}
	if(receive_proc->status == -1 && receive_proc->waitforreply == 1){
		printf(" Cannot send, reverive is waiting for a reply.\n");
		return;
	}
	if(current_proc->msg == 1){
		printf(" Cannot send, the current process has unread message from another process.\n");
		return;
	}

	strcpy(receive_proc->message, msg);
	receive_proc->msg = 1;
	receive_proc->sender = current_proc->PID;
	receive_proc->needtoreply = 1;
	receive_proc->status = 0;
	receive_proc->waitformessage = 0;
	current_proc->status = -1;
	current_proc->waitforreply = 1;
	current_proc->priority = 0;

	if(receive_proc->priority == 1){
		ListRemove(ReadyQ_Norm);
		ListAppend(ReadyQ_High, receive_proc);
		receive_proc->priority = 0;
	}
	if(current_proc->status == -1) {
		printf(" Message sent, proccess %i will be blocked while waiting for reply, next process loaded.\n", current_proc->PID);
		Quantum();
	}
}

void Receive(){
	if(current_proc->status == -1 && current_proc->waitforreply == 1){
		printf(" Cannot start receiving, the current process is waiting for reply.\n");
		return;
	}
	if(current_proc->msg == 0){
		current_proc->status = -1;
		current_proc->waitformessage = 1;
		current_proc->priority = 0;
		printf(" No message to receive, process blocked until message arrives.\n");
		Quantum();
		return;
	}
	PCB * sender = SearchAll(current_proc->sender);
	printf("\n Message from process %i: ", sender->PID);

	puts(current_proc->message);

	current_proc->msg = 0;

	if(current_proc->status != -1 && current_proc->msg == 0 && current_proc->waitformessage == 0
		&& current_proc->needtoreply == 0 && current_proc->waitforreply == 0 && current_proc->PID != 1){
		current_proc->priority = 1;
	}
}

void Reply(int PID, char * msg){
	PCB * replyto = SearchAll(PID);

	if(PID != current_proc->sender){
		printf("You can only reply to process %i.\n", current_proc->sender);
		return;
	}
	replyto->status = 0;
	replyto->waitforreply = 0;
	replyto->msg = 1;
	replyto->sender = current_proc->PID;
	strcpy(replyto->message, msg);
	current_proc->needtoreply = 0;

	if(current_proc->status != -1 && current_proc->msg == 0 && current_proc->waitformessage == 0
		&& current_proc->needtoreply == 0 && current_proc->waitforreply == 0 && current_proc->PID != 1){
		current_proc->priority = 1;
	}

}

void NewSemaphore(int SID, int val){
	if(SMP_count == 4){
		printf(" There are already 5 semaphores, cannot created more.\n");
		return;
	}
	SMP * newSemaphore = new_SMP(SID, val);
	Semaphore_List[SID] = newSemaphore;
	SMP_count++;
	printf(" New Semaphore created, SID is: %i\n", SID);
}

void SemaphoreP(int SID){
	if(current_proc->PID == 1){
		printf(" Cannot add initial process to Semaphore!\n");
		return;
	}
	if(current_proc->status == -1){
		printf(" The current process is already blocked, cannot semaphoreP.\n");
		return;
	}
	if(Semaphore_List[SID] == 0){
		printf(" The semaphore does not exist.\n");
		return;
	}
	SMP * current_semaphore = Semaphore_List[SID];
	current_semaphore->val--;

	printf(" Semaphore %i has val %i :", SID, current_semaphore->val);
	if(current_semaphore->val < 0){

		ListAppend(current_semaphore->proc, current_proc);
		current_proc->status = -1;
		current_proc->smp = SID;
		printf(" Process %i is block by Semaphore %i", current_proc->PID, current_semaphore->SID);
		current_proc->priority = 0;
		Quantum();
		return;
	}
	printf(" Added process %i to semaphore %i.\n", current_proc->PID, current_semaphore->SID);
}

void SemaphoreV(int SID){
	if(Semaphore_List[SID] == 0){
		printf(" Semaphore %i does not exist.\n", SID);
		return;
	}

	SMP * current_semaphore = Semaphore_List[SID];
	if(current_semaphore->val > 0){
		printf("There is nothing blocked by semaphore %i\n", current_semaphore->SID);
		return;
	}
	current_semaphore->val++;
	PCB * ready_process;
	ListFirst(current_semaphore->proc);
	ready_process = ListRemove(current_semaphore->proc);
	ready_process->smp = 0;
	ready_process->status = 0;
	printf("Process %i is made ready.\n", ready_process->PID);
}



void Proinfo(int PID){
	printf("\033[0m-------------------------------------------\033[0;32m\n");
	
	PCB * Pinfo = SearchAll(PID);
	if (Pinfo == NULL){
		printf("Process not found\n.");
		return;
	}
	printPCB(Pinfo);
}

void printmenu(){
	printf("\033[0m");
	printf(	"-------------------------------------------\n"
		"		Main Menu\n"
		"-------------------------------------------\n"
		"	[C] create a new process\n"
		"	[F] copy current process\n"
		"	[K] kill a process\n"
		"	[E] kill this corrent process\n"
		"	[Q] execute the next ready process\n"
		"	[S] send a message\n"
		"	[R] receive a message\n"
		"	[Y] reply to another process\n"
		"	[N] create new semaphore\n"
		"	[P] semaphore P\n"
		"	[V] semaphore V\n"
		"	[I] display info of a process\n"
		"	[T] display all processes\n"
		"	[Z] clear screen\n"
		"	[M] show all semaphore\n");
		printf("\033[0;32m");

}

int main(){
	system("clear");
	char command;
	proc_count = 0;
	SMP_count = 0;

	ReadyQ_High = ListCreate();
	ReadyQ_Norm = ListCreate();
	ReadyQ_Low = ListCreate();

	create(2,1); //create(low priority, ready)

	ListFirst(ReadyQ_Low);
	current_proc = ListRemove(ReadyQ_Low);
	printmenu();
	while(1){

		printf("\033[0m-------------------------------------------\n");
		printf("Please select a function (Z to show Menu): ");	

		command = getchar();
		if(command != '\n'){
			while(getchar() != '\n');			
		}

		printf("\033[0;32m");

		switch(command){
			case 'Z':
				system("clear");
				printmenu();
				break;
			case 'M':
				for(int i= 0; i<6; i++){
					if (Semaphore_List[i] != 0){
						printf("Semaphore %i has value %i.\n", Semaphore_List[i]->SID, Semaphore_List[i]->val);
					}
				};
				break;
			case 'C':
				create(1,0);//create(priority, status)
				break;
			case 'F':
				Fork();
				break;

			case 'K':
				printf("Please enter the PID to Kill: ");
				scanf("%d", &parameter);
				getchar();
				Kill(parameter);
				break;

			case 'E':
				Exit();
				break;

			case 'Q':
				Quantum();
				break;

			case 'S':
				printf("\033[0mlease enter the PID to Send to: ");
				scanf("%d", &parameter);
				getchar();
				printf("\033[0mPlease enter the message to send: ");
				fgets(message, 100, stdin);
				printf("\033[0;32m");					

				Send(parameter, message);
				memset(message, 0, 101);				
				break;

			case 'R':
				Receive();
				break;

			case 'Y':
				printf("\033[0mPlease enter the PID to reply to: ");
				scanf("%d", &parameter);
				getchar();			
				printf("\033[0mPlease enter the message to reply: ");
				fgets(message, 100, stdin);
				printf("\033[0;32m");
				Reply(parameter, message);
				memset(message, 0, 101);				
				break;

			case 'N':
				parameter = -1;
				while(parameter < 1 || parameter > 5){
					printf("\033[0mPlease enter the SID of semaphore to create (1-5): ");
					scanf("%d", &parameter);
					getchar();
					printf("\033[0;32m");					
				}
				if(Semaphore_List[parameter] != NULL){
					printf("A semaphore with that SID already exist.\n");
					break;
				}
				printf("\033[0mPlease enter the val of semaphore to create: ");
				scanf("%d", &parameter2);
				getchar();
				printf("\033[0;32m");					

				NewSemaphore(parameter, parameter2);
				break;

			case 'P':
				printf("\033[0mPlease enter the s of semaphore to call P: ");
				scanf("%d", &parameter);
				getchar();
				printf("\033[0;32m");
				SemaphoreP(parameter);			
				break;

			case 'V':
				printf("\033[0mPlease enter the s of semaphore to call V: ");
				scanf("%d", &parameter);
				getchar();
				printf("\033[0;32m");
				SemaphoreV(parameter);	
				break;

			case 'I':
				printf("\033[0mPlease enter the PID to show info: ");
				scanf("%d", &parameter);
				getchar();
				printf("\033[0;32m");
				Proinfo(parameter);
				break;

			case 'T':
				TotalInfo();
				break;

			default:
				break;
		}
	}
	return 0;
}