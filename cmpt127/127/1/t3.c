#include <stdio.h>
#include <math.h>

int main (){
	float i = 0;
	double a, b, c;
	scanf("%f", &i);
	a = floorf(i);
	b = roundf(i);
	c = ceilf(i);
	

	printf("%.lf %.lf %.lf\n", a, b, c);
	return 0;
}
