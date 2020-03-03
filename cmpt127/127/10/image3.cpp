#include "image3.hpp"
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
 	if( pixels != NULL ) {
 		for (int i = 0; i < rows; i++){
 			delete[] pixels[i];
 		}
       	delete[] pixels; 
    }
    cols = 0;
    rows = 0;
}

int Image::resize( unsigned int width,  unsigned int height, uint8_t fillcolor ){
 	if(pixels != NULL){
	 	for (int i = 0; i < rows; i++){
	 			delete[] pixels[i];
	 		}
       	delete[] pixels; 
    }
 	pixels = new uint8_t*[height];
 	for(int i = 0; i < height; i++){
 		pixels[i] = new uint8_t[width];
 	}
 	assert(pixels != NULL);
 	cols = width ;
 	rows = height ;

 	for (int i=0; i < height; i++){
 		for(int j=0; j < width; j++)
 		pixels[i][j] = fillcolor;
 	}

 	return 0;
}  

int Image::set_pixel( unsigned int x, unsigned int y, uint8_t color ){
 	assert(pixels != NULL);
 	if(x >= cols || y >= rows) return 1;
 	pixels[y][x] = color;
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
 	*colorp = pixels[y][x];
 	return 0;
}

int Image::save( const char* filename ){
	
	if(filename == NULL) return 1;

	FILE*f = fopen(filename, "w+");
	if(f==NULL) return 1;

	fprintf(f, "[");
	fprintf(f, "%d,", cols);
	fprintf(f, "%d,", rows);
	for (int i=0; i < rows; i++){
 		for(int j=0; j < cols; j++){
 			fprintf(f, "%d",pixels[i][j]);
 		if((i+1)*(j+1) < (cols*rows-1)) fprintf(f, ",");
 		}
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
	for (int i=0; i < rows; i++){
 		for(int j=0; j < cols; j++){
    		while (fscanf(f, "%d", &val) != 1) fseek(f, 1, SEEK_CUR);
    		pixels[i][j] = val;
   		}
   	}
   	fclose(f);
  	return 0;
}

