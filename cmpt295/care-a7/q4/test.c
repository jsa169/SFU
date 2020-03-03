#include <stdio.h>

long new_42(void) {
    long x;
    long *ret;

    x = 42;
    ret = &x;

    return *x;
} // new_42

long N = 10;
void donotmuchofanything(long *a) {
    if (N--) {
        donotmuchofanything(a);
        N++;
    }
} // donotmuchofanything

void main () {
    long *long_ptr;
    long a = 42;

    long_ptr = new_42();
    printf("The current value is %ld.\n", *long_ptr);
    printf("The pointer value is %x.\n", long_ptr);

    donotmuchofanything(long_ptr);
    printf("The current value is %ld.\n", *long_ptr);
    printf("The pointer value is %x.\n", long_ptr);
}