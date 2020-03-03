#include "image.hpp"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int main(){
	Image* img = new Image;
	img->resize(640,480,0);
printf("%d %d\n", img->cols, img->rows);

	img->resize(100,100,72);
		printf("%d %d\n", img->cols, img->rows);

	img->resize(32,32,72);
	//img->set_pixel(100,100,255);
	printf("%d %d\n", img->cols, img->rows);
	delete img;

}