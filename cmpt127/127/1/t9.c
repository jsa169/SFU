#include <stdio.h>
#include <math.h>


int draw_pyramid(int w, int h){
	int i,j,k;
	double left, right;
	int word;
	for ( i = h-1; i >= 0; i--){
		left = floor( i * (w/(2.0*h)) );
		word = w - left - left;
		for (k = left; k > 0; k--){
			printf(" ");
		}
		
		if (i == h - 1){
			for (k = 0; k < word; k++){
			printf("#");
			}
			printf("\n");
			continue;
		}

		else if (i == 0){
			for (k = 0; k < word; k++){
			printf("#");
			}
			printf("\n");
			continue;
		}

		printf("#");
		for (k = 2; k < word; k++){
			printf(".");
		}
			
		printf("#\n");				
	}
}	
	
 
int main (){
	int w, z, h;	
	scanf("%d %d %d", &w, &z, &h);
	draw_pyramid(w, h);	
}	

