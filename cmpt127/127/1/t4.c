#include <stdio.h>
#include <math.h>

int main (){	
	float i = 0;
	double a, b, c;
	int x;
	x = scanf("%f", &i);
	if (x == 1){
		a = floorf(i);
		b = roundf(i);
		c = ceilf(i);
	

		printf("%.lf %.lf %.lf\n", a, b, c);
		return 0;
	}
	else{
	printf("scanf error: (%d)\n", x);
	}
}
