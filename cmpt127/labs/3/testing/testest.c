#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

uint8_t* region_copy( const uint8_t array[], 
              unsigned int cols, 
              unsigned int rows,
              unsigned int left,
              unsigned int top,
              unsigned int right,
              unsigned int bottom )
{
    // your code here
  unsigned int a = right - left;
  unsigned int b = bottom - top;
  int count = 0;
  uint8_t* q = malloc(sizeof(array[0])*2*1);
 
  for (int i = 0; i < rows; i++){
    if (left == right || top == bottom){
      break;
      }

    for(int j = 0; j < cols; j++){

        if ((i >= top && i <= bottom -1) && (j >= left && j <= right - 1)){
          q[count] = array[i*cols + j];

          count++;
        }
      } 
    }

    if (count == 0) {return NULL;}
    else {return q;}
}


int main(){
	uint8_t array[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	unsigned int cols = 5;
	unsigned int rows = 4;
	unsigned int left = 1;
    unsigned int top = 1;
    unsigned int right = 3;
    unsigned int bottom = 3;
    uint8_t color = 0;

	uint8_t *r = malloc(sizeof(array[0])*5*4);

	r = region_copy(array, cols, rows, left, top, right, bottom);
  for (int i = 0; i < 20; i++){
  	printf("%d ", r[i]);
  }
 }