#include <stdio.h>
#include <stdlib.h>		/* getenv(), etc. */
#include <unistd.h>		/* sleep(), etc.  */
#include <stdint.h>             /* uint8_t */
#include <math.h>               /* for floor() and ceil() */
#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>

/*This function calculates the location of the target 
cell using coordinates. i.e (x,y) to arr[n]*/

int pos(int x,int high){
	if (x < 0){
		return high - 1;
	}
	else if (x > (high - 1)) {
		return 0;
	}
	else if (x >= 0 && x <= (high - 1)){
		return x;
	}
}	

void life( uint8_t arr[], 
	     unsigned int cols, 
	     unsigned int rows )
{
	//Clone the original array, used to check original conditions while changing original array
	uint8_t a[cols*rows];
	for (int i = 0; i < cols*rows; i++){
		a[i] = arr[i];
	}


	int n = 0;
	int x,y;
	//Go through every cell, calculate n/8 cells thats == 255
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			for (int k = 0; k < 3; k++){
				x = pos(i-1, rows);
				y = pos(j-1+k, cols);
				if(a[x*cols+y] == 255){
					n++;
				}
			}
			x = pos(i, rows);
			y = pos(j-1, cols);
			if(a[x*cols+y] == 255){
					n++;
			}
			x = pos(i, rows);
			y = pos(j+1, cols);
			if(a[x*cols+y] == 255){
					n++;
			}
			for (int k = 0; k < 3; k++){
				x = pos(i+1, rows);
				y = pos(j-1+k, cols);
				if(a[x*cols+y] == 255){
					n++;
				}
			}
			//Check for Game Conditions
			if((a[i*cols + j] == 255) && (n < 2)){arr[i*cols + j] = 0;} 
			if((a[i*cols + j] == 255) && (n > 3)){arr[i*cols + j] = 0;}
			if((a[i*cols + j] != 255) && (n == 3)){arr[i*cols + j] = 255;}
			n = 0;
		}
	}
}

/*
int fxy(int k,int limit)          // use this function to determin the location of the nearby pixels of image.
                                  //(else if used to find the border pixels)
{    
	if (k>=0 && k<=limit-1)
	{
		return k;
	}
	else if (k<0)
	{
		return limit-1;
	}
	else if (k>limit-1)
	{
		return 0;
	}
}

void life( uint8_t array[], 
     unsigned int cols, 
     unsigned int rows )
{
	int i,count,m,n,x,y;
	int checkarr[rows*cols];     //create a new array to store the num of count.
	int a[3]={-1,0,1};
	for(i=0;i<rows*cols;i++)
	{
		count=0;
		for (m=0;m<3;m++)
		{
			x=fxy(i%cols+a[m],cols);
			for (n=0;n<3;n++)
			{
				y=fxy(i/cols+a[n],rows);
				if (array[y*cols+x]==255)
				{
					count++;
				}
			}
		}
		checkarr[i]=count;
		
	}
	for(i=0;i<rows*cols;i++)
	{
		if(array[i]==255)
		{
			if (checkarr[i]!=3 && checkarr[i]!=4)  // As the rule required a livel pixel got 2 or 3 live pixel.
			{                                          // we use 3 or 4 as the count counted array[i] itself, so +1
				array[i]=0;
			}			
		}
		else 
		{
			if (checkarr[i]==3)
			{
				array[i]=255;
			}
		}
	}
	
}
*/