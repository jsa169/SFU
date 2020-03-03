#include "image.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

using namespace std;
Image::Image()
{
	cols = 0;
	rows = 0;
	pixels = NULL;//
}

 Image::~Image()
 {
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