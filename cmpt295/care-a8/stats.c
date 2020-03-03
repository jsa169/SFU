//stats.c
//
//Description: Calculates max, min, and avg of an array. The overall, row and col values are all
//              calculated
//
//Name: Jichuan Shi
//
//Date: 11/21/2019
//
//

#include <stdio.h>
#include <math.h>


void min_max_avg(float **grid, int N, int M, 
                 float *min, float *max, float *avg, 
                 float *col_min, float *col_max, float *col_avg, 
                 float *row_min, float *row_max, float *row_avg) {


    int i, j;

    for(j = 0; j < M; j++){
        col_min[j] = INFINITY;
        col_max[j] = -INFINITY;
        col_avg[j] = 0;
    }

    float avgg = 0;
    float avgg_0 = 0;

    float minn = INFINITY;
    float maxx = -INFINITY;
    float current;
    float current_0;

    // compute stat, the loop is only traversed once, stats for both row and col
    for (i = 0; i < N; i++) {
        row_min[i] = +INFINITY;
        row_max[i] = -INFINITY;
        row_avg[i] = 0;
        for (j = 0; j < M-2; j+=2) {
            current = grid[i][j];
            row_min[i] = (current < row_min[i]) ? current: row_min[i];
            row_max[i] = (current > row_max[i]) ? current:row_max[i];

            row_avg[i] += current;
            avgg += current;

            col_min[i] = (current < col_min[i]) ? current: col_min[i];
            col_max[i] = (current > col_max[i]) ? current:col_max[i];

            col_avg[j] += current;


            current_0 = grid[i][j+1];
            if (current_0 < row_min[i]) {
                row_min[i] = current_0;
            }
            if (current_0 > row_max[i]) {
                row_max[i] = current_0;
            }
            row_avg[i] += current_0;
            avgg_0 += current_0;

            if(current_0 < col_min[j+1]){
                col_min[j] = current_0;
            }
            if(current_0 > col_max[j+1]){
                col_max[j+1] = current_0;
            }
            col_avg[j+1] += current_0;
          
        }
        avgg += avgg_0;
        avgg_0 = 0;
        for(;j<M;j++){
            current = grid[i][j];
            if (current < row_min[i]) {
                row_min[i] = current;
            }
            if (current > row_max[i]) {
                row_max[i] = current;
            }
            row_avg[i] += current;
            avgg += current;

            if(current < col_min[j]){
                col_min[j] = current;
            }
            if(current > col_max[j]){
                col_max[j] = current;
            }
            col_avg[j] += current;
        }
        row_avg[i] = (M == 0) ? NAN:row_avg[i]/(float)M;

    }
    *avg = (N*M > 0) ? avgg/(float)(M*N):NAN; //Part b) pointer is only used at the end of calculation


    //Calculate col avg,
    for(j = 0; j < M; j++){
        col_avg[j] = (M==0) ? NAN:col_avg[j]/(float)N;
    }   



    // compute overall min
    for (i = 0; i < N; i++) {
    	minn = (row_min[i] < minn) ? row_min[i]:minn;
        //if (row_min[i] < minn) minn = row_min[i];
    }
    *min = minn;//Part b) pointer is only used at the end of calculation

        // compute overall max
    for (i = 0; i < N; i++) {
        maxx = (row_max[i] > maxx) ? row_max[i]:maxx;
    	//if (row_max[i] > maxx) maxx = row_max[i];
    }
    *max = maxx;//Part b) pointer is only used at the end of calculation

} // min_max_avg

