#include <stdio.h>
#include <stdlib.h>		/* getenv(), etc. */
#include <unistd.h>		/* sleep(), etc.  */
#include <stdint.h>             /* uint8_t */
#include <math.h>               /* for floor() and ceil() */
#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>

void draw_circle( uint8_t img[], 
                  unsigned int cols,
                  unsigned int rows,
		 		  int x,
		  		  int y,
		 		  int r,
		  		  uint8_t color ){

	if (r == 0 || x < 0 || y < 0 || x > cols || y > rows) {exit(0);}
	else{
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				if(round(hypot((y - i),(x - j))) < r){
					img[i*cols + j] = color;
				}
			}
		}
	}
}
