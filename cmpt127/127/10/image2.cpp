#include "image2.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

using namespace std;
Image::Image(){
	cols = 0;
	rows = 0;
	pixels = NULL;//
}

Image::~Image(){
 	cols=0;
 	rows=0;
 	if( pixels != NULL ) 
    {
       delete[] pixels; 
    }
    
}

int Image::resize( unsigned int width,  unsigned int height, uint8_t fillcolor ){
 	delete[] pixels;
 	pixels = new uint8_t[width*height];
 	assert(pixels != NULL);
 	cols = width ;
 	rows = height ;
 	for (int i=0; i < width*height; i++){
 		pixels[i] = fillcolor;
 	}
 	
 	return 0;
}  

int Image::set_pixel( unsigned int x, unsigned int y, uint8_t color ){
 	assert(pixels != NULL);
 	if(x >= cols || y >= rows) return 1;
 	pixels[y*cols+x] = color;
 	return 0;
}
  

int Image::get_pixel( unsigned int x, unsigned int y, uint8_t* colorp ){
 	if (pixels == NULL){
 		return 1;
 	}
 	if (colorp == NULL){
 		return 1;
 	}
 	if(x >= cols || y >= rows) return 1;
 	*colorp = pixels[y*cols+x];
 	return 0;
}

int Image::save( const char* filename ){
	
	if(filename == NULL) return 1;

	FILE*f = fopen(filename, "w+");
	if(f==NULL) return 1;

	fprintf(f, "[");
	fprintf(f, "%d,", cols);
	fprintf(f, "%d,", rows);
	for(int i = 0; i < cols*rows; i++){
		fprintf(f, "%d",pixels[i]);
		if(i < cols*rows-1) fprintf(f, ",");
	}
	
	fprintf(f, "]");
	fclose(f);
	return 0;
}

int Image::load( const char* filename ){

	if(filename == NULL) return 1;

	FILE*f = fopen(filename, "r+");
	if(f == NULL) return 1;

	int val;
	fseek(f, 0, SEEK_SET);
	while(fscanf(f, "%d", &val) != 1) fseek(f, 1, SEEK_CUR);
	cols = val;

	while(fscanf(f, "%d", &val) != 1) fseek(f, 1, SEEK_CUR);
	rows = val;

	resize(cols, rows, 0);
	for (int i = 0; i < cols*rows; i++){
    	while (fscanf(f, "%d", &val) != 1) fseek(f, 1, SEEK_CUR);
    	pixels[i] = val;
   
  	}

	fclose(f);
  	return 0;
}