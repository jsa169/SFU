#include <stdio.h>

int main(){
	int a = sizeof(char);
	int b = sizeof(unsigned char);	
	int c = sizeof(int);	
	int d = sizeof(unsigned int);	
	int e = sizeof(long);	
	int f = sizeof(unsigned long);	
	int g = sizeof(float);	
	int h = sizeof(double);	
	int i = sizeof(long double);
	
printf("%lu %lu %lu %lu %lu %lu %lu %lu %lu\n",a*8 , b*8, c*8, d*8, e*8, f*8, g*8, h*8, i*8);

}

