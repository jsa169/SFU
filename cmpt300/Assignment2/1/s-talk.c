#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include<fcntl.h>
#include<string.h>
#include <pthread.h> 

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>



#include "list.h"

int end_convo = 0;

struct addrinfo *remote_addr_info;
struct addrinfo *local_addr_info;
int s; //socket


LIST *g_to_send;
LIST *g_to_print;
LIST *g_length_of_message;

//message lengths
int readlen = 0;
int recvlen = 0;

//mutex
pthread_mutex_t g_recv_mutex;
pthread_mutex_t g_send_mutex;

//condition variables
pthread_cond_t g_recv_cv;
pthread_cond_t g_send_cv;

//to clear lists when exiting process
void itemFree(void *a) { 
    a= NULL;
} 

//retrieves the message pointed to by current list pointer and sends to remote host
void *sendMsg(){
    pthread_mutex_lock (&g_send_mutex);
    while(end_convo==0){
        pthread_cond_wait(&g_send_cv, &g_send_mutex);
        ListFirst(g_to_send);  
        ListFirst(g_length_of_message);
        sendto(s, ListCurr(g_to_send), *(int *)ListCurr(g_length_of_message), 0, remote_addr_info->ai_addr, remote_addr_info->ai_addrlen);
        ListRemove(g_to_send);
        ListRemove(g_length_of_message);  
        pthread_mutex_unlock(&g_send_mutex);
    }
    sendto(s, "`",2, 0, remote_addr_info->ai_addr, remote_addr_info->ai_addrlen);
    write(1, "\033[0;31mLeaving chatroom...\033[0m\n",32);
    pthread_exit(NULL);
}

//reads user input and stores in list at current list pointer
void *inputMsg (){
    char buf[100];
    while(end_convo == 0){
        readlen = read(0, buf, sizeof(char)*100);
        if(*buf=='`') {
            end_convo = 1;        
        }
        pthread_mutex_lock (&g_send_mutex);
        ListAppend(g_to_send, (void*)buf); 
        ListAppend(g_length_of_message, &readlen); 
        pthread_cond_signal(&g_send_cv);
        pthread_mutex_unlock(&g_send_mutex);

    }
    pthread_exit(NULL);
}

//stores received message in list at current lister pointer
void *receiveMsg(){
    char buf[100];
    while(end_convo==0){
        recvlen = recvfrom(s, buf, 100, 0, 0 ,0);
        if(*buf=='`'){
            end_convo = 1;
            write(1, "\033[0;31mRemote user requesting termination, Press enter to leave the chat..\033[0m",79);        
        }
        pthread_mutex_lock (&g_recv_mutex);
        ListAppend(g_to_print,buf);
        pthread_cond_signal(&g_recv_cv);
        pthread_mutex_unlock(&g_recv_mutex);
    }
   pthread_exit(NULL);
}

//retrieves message at current list pointer and prints to terminal
void *outputMsg (){
    pthread_mutex_lock (&g_recv_mutex);
    while(end_convo == 0) {
        pthread_cond_wait(&g_recv_cv, &g_recv_mutex);
        ListFirst(g_to_print);
        if(end_convo==0){          
            write(1, "\033[0;33mRemote User: ",21);
            write(1, ListCurr(g_to_print),recvlen);
            write(1, "\033[0;32m",8);        
        }
        ListRemove(g_to_print);
        pthread_mutex_unlock(&g_recv_mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if(argc != 4){
        printf("\033[0;31mPlease enter your arguments in the following format:\n"); 
        printf("[your port] [name of remote device] [port of remote device]\033[0;33m\n");
        return -1;
    }

    //whether host information is obtained successfully
    int status;

    //configuration for local socket
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_flags = AI_PASSIVE;     // automatically fill in my IP

    //get address info of local host
    status = getaddrinfo(NULL, argv[1], &hints, &local_addr_info);
    if(status!=0){
        printf("\033[0;31mError while getting my address\033[0m\n"); 
        pthread_exit(NULL);
        freeaddrinfo(remote_addr_info);
        freeaddrinfo(local_addr_info);        
        return -1;
    }

    char host[256];
    getnameinfo(local_addr_info->ai_addr, local_addr_info->ai_addrlen, host, sizeof (host), NULL, 0, NI_NUMERICHOST);
       puts(host);
    
    //get address info of remote host
    status = getaddrinfo(argv[2], argv[3], NULL, &remote_addr_info);
    if(status!=0){
        printf("\033[0;31mError while getting remote address\033[0m\n"); 
        pthread_exit(NULL);
        freeaddrinfo(remote_addr_info);
        freeaddrinfo(local_addr_info);
        return -1;
    }

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if(s==-1){
        printf("\033[0;31mError while creating endpoint\033[0m\n"); 
        pthread_exit(NULL);
        freeaddrinfo(remote_addr_info);
        freeaddrinfo(local_addr_info);        
        return -1;
    }
    bind(s, local_addr_info->ai_addr, local_addr_info->ai_addrlen);

    printf("\033[0;31mYou are now chatting with %s\033[0;32m\n", argv[2]);
    
    //for storing message data
    g_to_send = ListCreate();
    g_to_print = ListCreate();
    g_length_of_message = ListCreate();

    //set thread attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //creating threads    
    pthread_t threads[2];
    int receiveThread = pthread_create(&threads[0],NULL,receiveMsg, NULL);
    int outputThread = pthread_create(&threads[1],NULL,outputMsg,NULL);
    int sendThread = pthread_create(&threads[2],NULL,sendMsg,NULL);
    int inputThread = pthread_create(&threads[3],NULL,inputMsg,NULL);

    //mutex
    pthread_mutex_init(&g_send_mutex, NULL);
    pthread_mutex_init(&g_recv_mutex, NULL);

    //Clean up threads
    for (int i=0; i<4; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&g_send_mutex);
    pthread_mutex_destroy(&g_recv_mutex);

    //close socket and free memory for address information
    close(s);
    freeaddrinfo(remote_addr_info);
    freeaddrinfo(local_addr_info);

    //free lists
    ListFree(g_to_send, itemFree);
    ListFree(g_to_print, itemFree);
    ListFree(g_length_of_message, itemFree);


    printf("\033[0;31mYou have left the chatroom\033[0m\n");
    pthread_exit(NULL);
}