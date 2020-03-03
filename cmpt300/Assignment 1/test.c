#include<stdlib.h>
#include<stdio.h>

void printall(int a[]){
	for (int i = 0; i < 10; i++){
		printf("%d ", a[i]);
	}

	printf("\n");

}

int main(){
	int a[10] = {};

	printall(a);

	int b = 1;
	for (int i = 0; i < 5; i ++){
		a[i] = b;
	}

	printall(a);
	
	b = 2;
	printall(a);

	return 0;
}