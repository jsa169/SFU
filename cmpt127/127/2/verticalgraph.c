#include <stdio.h>

void print(int arr[], int max, int len){
	for (int i = max; i > 0; i--){
		for (int j = 0; j < len-1; j++){
			if (arr[j] < i){
				printf(" ");
			}			
			else{
				printf("#");
			}
		}
		printf("\n");	
	}
	
}

int maxx(int arr[]){
	int a = 0;	
	for (int i = 0; i < 90; i++){
		if (arr[i] > a){
			a = arr[i];
		}
	}
	return a;
}

int main (){

	int arr[90] = {};
	int i = 0, j = 0;
	char temp;
	int x;

	do {temp = scanf("%d%c", &arr[i], &temp);
	i++;
	} while(temp != EOF);
	
	
	int max = maxx(arr);
	print(arr, max, i);
}
