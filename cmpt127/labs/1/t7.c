#include <stdio.h>

int main() {
	int n = 0;
	int i;
	int x = scanf("%d", &n);
	while (x != EOF){
		for (i = 0; i < n; i++){
			printf("#");
		}
		printf("\n");
		x = scanf("%d", &n);
	}	
}
