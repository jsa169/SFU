#include <stdio.h>

int main(){

  	char ch, a;
 	long unsigned int charcount = 0; 
   	long unsigned int wordcount = 0; 
   	long unsigned int linecount = 0;
   	char temp = ' ';
	char temp2 = ' ';

	while (a = scanf("%c", &ch)!= EOF){
   		
   		if (ch == '\n'){
   			linecount++;
   		}

   		charcount++;

   		if (((temp < 'A') || ((temp > 'Z') && (temp < 'a')) || (temp > 'z')) && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))){
			
			if (((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) && (temp != '\'')){
				wordcount++;

			}			
   		}

		/*if ((ch >= '0' && ch <= '9') && (temp < '0' || temp > '9') && (temp2 < '0' || temp2 > '9')){
			wordcount--;
			
		}

		if (((ch >= 'a' && ch <= 'b') || (ch >= 'A' && ch <= 'b')) && (temp >= '0' && temp <= '9')){
			wordcount++;
		}8*/

		temp2 = temp;
   		temp = ch;

   	}

	printf( "%lu %lu %lu\n", charcount, wordcount, linecount );

   	return 0;

}
