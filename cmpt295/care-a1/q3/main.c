
#include <stdio.h>

int mystery(char *, int);

char *str = "Reference letter";

void main () {
    int n = 0;
    printf("The return value was:  %d.\n", mystery(str,n));
    
    for (int i = 1; i<=17; i++){
    	n = i;
    	printf("The return value was:  %d.\n", mystery(str,n));   	
    }

	
    return;
}
