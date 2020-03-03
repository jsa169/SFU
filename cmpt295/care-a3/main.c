
#include <stdio.h>

char dot_prod(void *A, void *B, int n, int i, int j);

#define N 4

char A[N][N] = { 1, 1,  1,  1,
                1,  1, 1,  1,
                 1,  1,  1,  1,
                1,  1,  1,  1};

char B[N][N] = { 1, 1,  1, 1,
                 1, 1, 1,  1,
                1, 1,  1,  1,
                1,  1, 1, 1};
/*
char A[N][N] = { 32, -15,  38, -26,
                -52, 112, -27,  38,
                 52, -33,  64, -22,
                -22,  62, -44,  13};

char B[N][N] = { 27,  54,  -89, -18,
                 12,  36, -100,  25,
                -23,  28,   57,  46,
                 -6, -14,  107,   7};
*/
char C[N][N];

void print_matrix(void *A, int n);


void main () {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = dot_prod(A, B, N, i, j);
        }
    }

    print_matrix(A, N);
    print_matrix(B, N);
    print_matrix(C, N);
    return;
}


void print_matrix(void *A, int n) {
    int i, j;
    char val;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            val = *((char*)(A + i*n + j));
            printf("%4d", val);
        }
        putchar('\n');
    }
    putchar('\n');
}

