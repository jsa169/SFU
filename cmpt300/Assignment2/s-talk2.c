/*	s-talk2.c

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h> 

struct addrinfo *local_address, *foreign_address;	//Adress Info
int s;	//Socket

LIST *message;	//List to store incoming and out going message
pthread_mutex_t Array_change_lock;	//mutex that control Array changes

int terminate = 1; //if = 0: program ends
int recvlen;	//length of received message

int srs = 2; //send_receive_signal if 0: send signal, if 1: write signal, if 2: nothing
pthread_mutex_t send_receive_signal_lock;	//mutex that controls srs

void send_receive_signal(int a){//Set srs
	pthread_mutex_lock(&send_receive_signal_lock);
		srs = a;
	pthread_mutex_unlock(&send_receive_signal_lock);
}

void add_remove_message(int i, char msg[]){//Append or remove from list
	pthread_mutex_lock(&Array_change_lock);
		if(i == 0) ListPrepend(message, msg);
		else ListTrim(message);
	pthread_mutex_unlock(&Array_change_lock);
}

void *sendtoforeign(){//Send to other user from list
	char a[1];
	while(1){
		if(ListCount(message) != 0 && srs == 0){//if there is message & signal srs is send
			sendto(s, ListCurr(message), strlen(ListCurr(message)), 0, foreign_address->ai_addr, foreign_address->ai_addrlen);
			add_remove_message(1, a);//remove message from list after sending
			send_receive_signal(2);//change srs to nothing
		}
		if(terminate == 0){
			a[0] = '?';
			sendto(s, a, 1, 0, foreign_address->ai_addr, foreign_address->ai_addrlen);
			pthread_exit(NULL);
		}
	}
}

void *inputfromkb(){//take input from keyboard and store in list
	char buffer[100];
	while(1){
		if(terminate == 0) pthread_exit(NULL);
		fgets(buffer, 100, stdin);//take input from stdin
		if (buffer[0] == '?') {
			terminate = 0;
			break;
		}
		add_remove_message(0, buffer);//store message ito list
		send_receive_signal(0);//set srs to send signal
	}
}

void *displayons(){//take message from list and display on screen
	char a[1];
	while (1){
		if(terminate == 0) return NULL;
		if(ListCount(message) != 0 && srs == 1){//if there is message & signal srs is write
			write(1, "Message received: ", 18);
			write(1, ListCurr(message), recvlen);
			add_remove_message(1, a); //REmove from list after writing on stdin
			send_receive_signal(2);//Set srs to nothing
		}
	}
}

void *receivefrom(){//REceive message from other user. then store in list
	char buffer[100];
	while (1){
		if(terminate == 0) return NULL;
		recvlen =recvfrom(s, buffer, 100, 0, 0, 0); //receive message
		if (buffer[0] == '?') terminate = 0;
		add_remove_message(0, buffer);//add message to list
		send_receive_signal(1);//Set srs to write status
	}
}

int main(int argc, char** argv){
	if(argc != 4) exit(1);
	printf("Welcome to s-talk!\n");

	struct addrinfo hints;//set up Address Info for later use
	memset(&hints, 0, sizeof (hints));
	hints.ai_flags = AI_PASSIVE;

	int result;
	result = getaddrinfo(NULL, argv[1], &hints, &local_address);//get local address
	if(result){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
        freeaddrinfo(local_address);
        freeaddrinfo(foreign_address);

        exit(1);
	}

	result = getaddrinfo(argv[2], argv[3], &hints, &foreign_address);//get other user address
	if(result){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
        freeaddrinfo(local_address);
    	freeaddrinfo(foreign_address);
        exit(1);
	}

      printf("You can start chatting now. Type '?' to quit");
      printf("\n");

	s = socket(AF_INET, SOCK_DGRAM, 0);//Bind socket
	bind(s, local_address->ai_addr, local_address->ai_addrlen);

	pthread_t send, receive, input, display;

	message = ListCreate();

	while(1){ //Creating threads
		if (pthread_create(&send, NULL, sendtoforeign, NULL) !=0 ) break;
		if (pthread_create(&receive, NULL, receivefrom, NULL) !=0 ) break;
		if (pthread_create(&input, NULL, inputfromkb, NULL) !=0 ) break;
		if (pthread_create(&display, NULL, displayons, NULL) !=0 ) break;

		if (pthread_mutex_init(&Array_change_lock, NULL) !=0 ) break;//Initiating locks
		if (pthread_mutex_init(&send_receive_signal_lock, NULL) !=0 ) break;

		pthread_join( send, NULL);
		pthread_join( receive, NULL);
		//pthread_join( inputfromkb, NULL); taken out so it does not keep on waiting for input even when program ends.
		pthread_join( display, NULL);
		break;		
	}
	pthread_mutex_destroy(&Array_change_lock);//Destroy locks

    freeaddrinfo(local_address);
    freeaddrinfo(foreign_address);
    close(s);

	return 0;
}

/*void *sendtoforeign(){
	char msg[100];
	while(1){
		if(terminate == 0) return NULL;
		fgets(msg, 100, stdin);
	
		sendto(s, msg, strlen(msg), 0, foreign_address->ai_addr, foreign_address->ai_addrlen);
		if (msg[0] == '?') terminate = 0;

	}

}*/
/*void *receivefrom(){
	char buffer[100];
	while (1){
		if(terminate == 0) pthread_exit(NULL);

		recvlen = recvfrom(s, buffer, 100, 0, 0, 0);
		if (buffer[0] == '?') {
			terminate = 0;
			printf("hahhahahahahahahahahahahahahahahaa\n");
		}
		write(1, buffer, recvlen);
		//printf("\n");
	}
	return NULL;

}*/