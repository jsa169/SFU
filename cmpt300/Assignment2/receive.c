#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//For socket()
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

struct addrinfo *local_address, *foreign_address;
int s;
int main(){
	struct addrinfo hints;
	memset(&hints, 0, sizeof (hints));
	hints.ai_flags = AI_PASSIVE;

	int result;
	result = getaddrinfo(NULL, "5000", &hints, &local_address);
	if(result){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
        freeaddrinfo(local_address);
    	freeaddrinfo(foreign_address);
        exit(1);
	}

	char host[256];
 	getnameinfo(local_address->ai_addr, local_address->ai_addrlen, host, sizeof (host), NULL, 0, NI_NUMERICHOST);
       puts(host);


	result = getaddrinfo("jack-VirtualBox", "5001", &hints, &foreign_address);
	if(result){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
        freeaddrinfo(local_address);
    	freeaddrinfo(foreign_address);
        exit(1);
	}

	s = socket(AF_INET, SOCK_DGRAM, 0);

	bind(s, local_address->ai_addr, local_address->ai_addrlen);

	char buffer[100];


 /*   for (;;) {
        printf("waiting on port\n");
        int recvlen = recvfrom(s, recMsg, 100, 0, 0 ,0);
        //printf("%s",recMsg);
        write(1, recMsg,10);
        return 0;
    }*/
	int len;

	while (buffer[0] != '?'){
		len = recvfrom(s, buffer, 100, 0, 0, 0);
		write(1, buffer, len);
		//printf("\n");
	}

	

	return 0;
}