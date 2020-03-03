#include <stdio.h>

int main (){	
	float i = 0;		
	scanf("%f", &i);		// Ask for first input
	float s = i;			// smallest
	float l = i;			// largest
	float t = i;			// total
	int check = 0; 			
	float n = 1;			// count
	while (check != EOF){	
		check = scanf("%f", &i);
		if (check == EOF){	
		}
		else{
			t = t + i;
			n = n + 1;
			if (i > l){
				l = i;
			}		
			else if (i < s){
				s = i;
			}
		}
	}
	printf("%.2f %.2f %.2f\n", s, l, t/n);
}

