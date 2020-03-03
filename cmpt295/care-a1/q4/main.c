
#include <stdio.h>

unsigned times(unsigned, unsigned);

void main () {
    unsigned a = 0;
    unsigned b = 1000;
    printf("The product of %u and %u is %u.\n", a, b, times(a,b));
    return;
}

