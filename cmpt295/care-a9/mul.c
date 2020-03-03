//mul.c
//
//Description: Calculate product of matrix
//
//Auther: Jichuan Shi
//Data: 2019-11-28
//

#include "mul.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int **mul(int **A, int rA, int cA, int **B, int rB, int cB) {
    if (cA != rB) {
        printf("Incompatible multiplication: %d x %d times a %d x %d\n", rA, cA, rB, cB); exit(-1);
    }

    int **C = newMatrix(rA, cB);
    if (C == NULL) return C;

    int **D = newMatrix(rB, cB);
    for(int i = 0; i < rB; i++){
        for (int j = 0; j < cB; j++){
            D[j][i] = B[i][j];
        }
    }

    /*
    // alg1

    int i, j, k;
    int sum, r;
    for (i = 0; i < rA; i++) {
        for (j = 0; j < cB; j++) {
            sum = 0;
            for (k = 0; k < cA; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    */


    /*
    // alg2

    int i, j, k;
    int sum, r;
    for (i = 0; i < rA; i++) {
        for (j = 0; j < cB; j++) {
            C[i][j] = 0;
        }
    }
    for (j = 0; j < cB; j++) {
        for (k = 0; k < cA; k++) {
            r = B[k][j];
            for (i = 0; i < rA; i++) {
                C[i][j] += A[i][k] * r;
            }
        }
    }
    */


    /*
    // alg3

    int i, j, k;
    int sum, r;
    for (i = 0; i < rA; i++) {
        for (j = 0; j < cB; j++) {
            C[i][j] = 0;
        }
    }
    for (i = 0; i < rA; i++) {
        for (k = 0; k < cA; k++) {
            r = A[i][k];
            for (j = 0; j < cB; j++) {
                C[i][j] += B[k][j] * r;
            }
        }
    }
    */

    // alg4

    int i, j, k;
    int sum, r;
    for (i = 0; i < rA; i++) {
        for (j = 0; j < cB; j++) {
            sum = 0;
            for (k = 0; k < cA; k++) {
                sum += A[i][k] * D[j][k];
            }
            C[i][j] = sum;
        }
    }

    return C;
}


