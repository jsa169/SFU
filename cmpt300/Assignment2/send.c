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
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;


	int result;
	result = getaddrinfo(NULL, "5001", &hints, &local_address);
	if(result){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
        freeaddrinfo(local_address);
    	freeaddrinfo(foreign_address);
        exit(1);
	}

	char host[256];
 	getnameinfo(local_address->ai_addr, local_address->ai_addrlen, host, sizeof (host), NULL, 0, NI_NUMERICHOST);
       puts(host);


	result = getaddrinfo("jack-VirtualBox", "5000", &hints, &foreign_address);
	if(result){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
        freeaddrinfo(local_address);
    	freeaddrinfo(foreign_address);
        exit(1);
	}

	s = socket(AF_INET, SOCK_DGRAM, 0);

	bind(s, local_address->ai_addr, local_address->ai_addrlen);

	char msg[100];
	while(msg[0] != '?'){
		fgets(msg, 100, stdin);
		sendto(s, msg, strlen(msg), 0, foreign_address->ai_addr, foreign_address->ai_addrlen);
	}
	//read(0, msg, 100);
	//msg[0] = 'H';
	//msg[1] = '\n';


	return 0;
}