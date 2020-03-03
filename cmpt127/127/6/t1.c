#include <stdio.h>
#include <stdlib.h>
#include "intarr.h"
#include <assert.h> 
/* LAB 6 TASK 1 */

/*
  Save the entire array ia into a file called 'filename' in a binary
  file format that can be loaded by intarr_load_binary(). Returns
  zero on success, or a non-zero error code on failure. Arrays of
  length 0 should produce an output file containing an empty array.
*/
int intarr_save_binary( intarr_t* ia, const char* filename ){
	if(filename == NULL) return 1;
	if(ia == NULL) return 1;
	FILE *f = fopen(filename,"w");
	
	if(fwrite(ia->data, sizeof(int), ia->len, f) == ia->len){
		fclose(f);
		return 0;
	}
	fclose(f);
	return 1;

}


/*
  Load a new array from the file called 'filename', that was
  previously saved using intarr_save_binary(). Returns a pointer to a
  newly-allocated intarr_t on success, or NULL on failure.
*/
intarr_t* intarr_load_binary( const char* filename ){
	if (filename == NULL) return NULL;
	FILE *f = fopen(filename, "r");
	
	if(f == NULL) return NULL;

	fseek(f, 0, SEEK_END);
	int len = (ftell(f)/sizeof(int));
	fseek(f, 0, SEEK_SET);
	intarr_t * new = malloc(sizeof(intarr_t));
	new->data = malloc(sizeof(int)*len);
	new->len = len;
	int flen = fread(new->data, sizeof(int), len, f);

	if (flen != new->len){
		fclose(f);
		return NULL;
	}
	else{
		fclose(f);
		return new;
	}
}