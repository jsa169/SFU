#include <stdio.h>

int main(){

  	char ch, a;
 	long unsigned int charcount = 0; 
   	long unsigned int wordcount = 0; 
   	long unsigned int linecount = 0;
   	char temp = ' ';
   	printf( "%lu %lu %lu\n", charcount, wordcount, linecount );

	while (a = scanf("%c", &ch)!= EOF){
   		
   		if (ch == '\n'){
   			linecount++;
   		}

   		if (ch != '\n'){
   			charcount++;
   		}

   		if ((temp == ' ' || temp == '\n') && ch != ' ' && ch != '\n'){
   			wordcount++;
   		}

   		temp = ch;

   	}

	printf( "%lu %lu %lu\n", charcount, wordcount, linecount );

   	return 0;

}