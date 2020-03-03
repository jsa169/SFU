#include <stdio.h>
#include <math.h>

int calculate (float i){	
	double a, b, c;
	a = floorf(i);
	b = roundf(i);
	c = ceilf(i);
	
	printf("%.lf %.lf %.lf\n", a, b, c);
	return 0;
}

int main (){
	float i = 0;
	int check = 0;
	while (check != EOF){
		check = scanf("%f", &i);
		if (check == EOF){	
		}
		else{
		calculate(i);
		}
	}
	printf("Done.\n");
}
