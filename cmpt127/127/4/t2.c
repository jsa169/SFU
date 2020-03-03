#include <stdio.h>
#include <stdlib.h>		/* getenv(), etc. */
#include <unistd.h>		/* sleep(), etc.  */
#include <stdint.h>             /* uint8_t */
#include <math.h>               /* for floor() and ceil() */
#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>


void draw_rectangle( uint8_t array[], 
		          unsigned int cols, 
		          unsigned int rows, 
		          int x,
		          int y,
		          int rect_width,
		          int rect_height,
		          uint8_t color ){

	if (rect_height == 0 || rect_height == 0) {exit(0);}
	else{
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				if((((i == y)||(i == y + rect_height)) && (((j <= x + rect_width) && (j >= x)) || ((j >= x + rect_width) && (j <= x)))) //while i = y or i = y + rect_height, x in range (x, x + rect_width)
					|| (((j == x) || (j == x +rect_width)) && (((i <= y + rect_height) && (i >= y)) || ((i >= y + rect_height) && (i <= y)))) //while j = x or j = x + rect_width, y in range (y, y+rect_height)
					){
					array[i*cols + j] = color;
				}
			}
		}
	}	
}
