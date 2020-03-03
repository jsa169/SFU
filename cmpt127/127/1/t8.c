#include <stdio.h>

int draw_pyramid(int w, int l){
	int i,j;
	for (i = 0; i < w; i++){
		printf("#");	
	}
	printf("\n");

	if (l == 1){
		return 0;	
	}
	if (l > 2){
		for (i = 0; i < l-2; i++){
			printf("#");
			for (j = 0; j < w-2; j++){
				printf(".");
			}
			printf("#\n");
		}
	}

	for (i = 0; i < w; i++){
		printf("#");	
	}
	printf("\n");	
}

int main () {
	int i, w, h;
	int n;	
	scanf("%d %d %d", &w, &h, &n);
	draw_pyramid(w, h);
}	

