#include <stdlib.h>

long *new_42(void) {
    long x;
    long *ret = malloc(sizeof(long));

    x = 42;
    ret[0] = x;

    return ret;
} // new_42

long N = 10;

void donotmuchofanything(long *a) {
    if (N--) {
        donotmuchofanything(a);
        N++;
    }
} // donotmuchofanything

