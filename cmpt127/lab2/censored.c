#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char replace_str1(char *ch, char *old, char *new){	
//All variables are pointer to the arrays
	char buffer[4096];
	char *p;

	p = strstr(ch, old);	
	//checking position of word to be cemsored
	for (int i = 0; i < p-ch; i++){		
	//Store everything before the censored word in buffer str
		buffer[i] = ch[i];
	}
	
	sprintf(buffer+(p-ch), "%s%s", new, p+strlen(old));		
	//Store "CENSORED" and everthing after in the buffer

	if(strstr(buffer, old)!= NULL){		
	//if buffer str still contain word to be replaced, run func again
		replace_str1(buffer, old, new);
	}

	strncpy(ch, "", 4096);
	//Empty input str

	strncpy(ch, buffer, strlen(buffer));
	//Replace input str with Buffer str
}

int main(int argc, char* argv[]){

	char ch[4096];
	char a;

	while ((a = fgets(ch, 4096,stdin)) != NULL){
	//Checking for End of file	

		for (int i = 1; i < argc; i++){
		//Loop through every word inputed as argc

			if (strstr(ch, argv[i]) != NULL){
			//Check if argv[] is include in stdin str.

				replace_str1(ch, argv[i], "CENSORED");
			}
		}

		printf("%s", ch);
		//Print out the final replaced str and read the next string
	}
}
	
