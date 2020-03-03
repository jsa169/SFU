//Jichuan shi
//Jan 30 / 2019 @ 8:50
//
//


#include <stdio.h>
#include <string.h>


int main(){

	int ch = 0;
	char string[4096], a;
	int letter = 0, c = 0, sum = 0; 
	float count[26] = {0};

	while ((a = fgets(string, 4096, stdin)) != NULL){
	//Get string until not more string, NULL
		while (string[c] != '\0'){
		//read each letter of the string until end of string, \0
			if (string[c] >= 'a' && string[c] <= 'z'){
			//compare char with 26 letters, add to count if found
				letter = string[c] - 'a';
				count[letter]++;
				sum++;
			}

			else if (string[c] >= 'A' && string[c] <= "Z"){
			//Same with previous if statement except for Capitalized
				letter = string[c] - 'A';
				count[letter]++;
				sum++;
			}

			c++;
		}

		c = 0;
	}
	for (int i = 0; i<26; i++){

		if (count[i] > 0){
		//Print only if count for that letter is > 0
			printf("%c %.4f\n", i + 'a', count[i]/sum);
		}
		
	}

}