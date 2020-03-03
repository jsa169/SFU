#include <stdio.h>
#include <stdlib.h>
#include "intarr.h"

/* LAB 5 TASK 1 */

// Create a new intarr_t with initial size len.  If successful
// (i.e. memory allocation succeeds), returns a pointer to a
// newly-allocated intarr_t.  If unsuccessful, returns a null pointer.
intarr_t* intarr_create( unsigned int len ){
	intarr_t * a = malloc(sizeof(intarr_t));
	if(a == NULL){
		return NULL;
	}
	a->len = len;
	a->data = malloc(sizeof(int)*a->len);
	return a;
}

// Frees all memory allocated for ia. If the pointer is null, do
// nothing. If the ia->data is null, do not attempt to free it.
void intarr_destroy( intarr_t* ia ){
	if (ia == NULL){
		return;
	}
	free(ia);
}

/* LAB 5 TASK 2 */

// If index is valid, set the value at ia->data[index] to val and return
// INTARR_OK. Otherwise, leave the array unmodified and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_set( intarr_t* ia, 
			    unsigned int index, 
			    int val ){
	if(ia == NULL){
		return INTARR_BADARRAY;
	}
	if(index < ia->len){
		ia->data[index] = val;
		return INTARR_OK;
	}
	return INTARR_BADINDEX;
}

// If index is valid and i is non-null, set *i to ia->data[index] and return
// INTARR_OK. Otherwise do not modify *i and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_get( const intarr_t* ia, 
			    unsigned int index, 
			    int* i ){
	if(ia == NULL){
		return INTARR_BADARRAY;
	}
	if(index < ia->len && i != NULL){
		*i = ia->data[index];
		return INTARR_OK;
	}
	return INTARR_BADINDEX;

}

/* LAB 5 TASK 3 */

// Return a duplicate of ia, allocating new storage for the duplicate
// data (we call this a "deep copy"). If unsuccessful (i.e. memory
// allocation for the copy fails, or ia is null), return a null pointer. 
intarr_t* intarr_copy( const intarr_t* ia ){
	intarr_t* a = malloc(sizeof(intarr_t));
	if(a == NULL){
		return NULL;
	}
	a->len = ia->len;
	a->data = malloc(sizeof(int)*ia->len);
	for(int i = 0; i < ia->len; i++){
		a->data[i] = ia->data[i];
	}
	return a;
}

/* LAB 5 TASK 4 */

// Sort ia by value smallest-to-largest, so that data[i] < data[i+1]
// for all valid i, then return INTARR_OK. Works in-place: contents of
// ia are sorted on return. If ia is null, return
// INTARR_BADARRAY.
intarr_result_t intarr_sort( intarr_t* ia ){
	if(ia == NULL){
		return INTARR_BADARRAY;
	}
	for(int i = 0; i < ia->len - 1; i++){
		for(int j = i + 1; j < ia->len; j++){
			if(ia->data[i] >= ia->data[j]){
				int temp = ia->data[i];
				ia->data[i] = ia->data[j];
				ia->data[j] = temp;
			}
		}
	}
	return INTARR_OK;
}

/* LAB 5 TASK 5 */

// Find the first occurance of the target in the array, searching from
// index 0. If the target is found and i is non-null, set *i to the
// location index and return INTARR_OK. If target does not occur in
// the array, leave *i unmodified and return INTARR_NOTFOUND. If ia is
// null, return INTARR_BADARRAY.
intarr_result_t intarr_find( intarr_t* ia, int target, int* i ){
	if(ia == NULL){
		return INTARR_BADARRAY;
	}
	for (int j = 0; j < ia->len; j++){
		if(ia->data[j] == target){
			*i = j;
			return INTARR_OK;
		}
	}
	return INTARR_NOTFOUND;
}

/* LAB 5 TASK 6 */

// HINT: First, do TASK 7, since you will need to resize your array
//       by +1 in order to successfully push val.
// Append val to the end of ia (allocating space for it). If
// successful, return INTARR_OK, otherwise return
// INTARR_BADALLOC. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_push( intarr_t* ia, int val ){
	if(ia == NULL){
			return INTARR_BADARRAY;
		}
	int * new = realloc(ia->data, sizeof(int)*(ia->len + 1));
	ia->data = new;
	ia->len++;
	ia->data[ia->len - 1] = val;
	if(ia->data[ia->len-1] == val){
		return INTARR_OK;
	}
	return INTARR_BADALLOC;
	

}

// HINT: You will need to decrement len so that it always represents
//       the number of int's stored in the array data.
// If the array is not empty, remove the value with the highest index
// from the array, and, if i is non-null, set *i to the removed value,
// then return INTARR_OK. If the array is empty, leave *i unmodified
// and return INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_pop( intarr_t* ia, int* i ){
	if(ia == NULL){
		return INTARR_BADARRAY;
	}
	if(ia->len == 0){
		return INTARR_BADINDEX;
	}
	if(i != NULL){
		*i = ia->data[ia->len - 1];
		int * new =realloc(ia->data, sizeof(int)*(ia->len-1));
		ia->data = new;
		ia->len--;
		return INTARR_OK;
	}
}

/* LAB 5 TASK 7 */

// HINT: Do this task before doing TASK 6.
// Resize ia to contain newlen values. If newlen is less than the
// original array length, the end of the array is discarded. If newlen
// is greater than the original array length, intialize all the new
// integers to zero. If the allocation is successful, return
// INTARR_OK, otherwise return INTARR_BADALLOC. If ia is null, return
// INTARR_BADARRAY.
intarr_result_t intarr_resize( intarr_t* ia, unsigned int newlen ){
	if(ia == NULL){
		return INTARR_BADARRAY;
	}
	if (newlen < 0){
		return INTARR_BADALLOC;
	}
	int *new = realloc(ia->data, sizeof(int)*newlen);
	if(newlen > ia->len){
		for(int i = ia->len; i < newlen; i++){
			new[i] = 0;
		}
	}
	ia->data = new;
	ia->len = newlen;
	return INTARR_OK;
}

/* LAB 5 TASK 8 */

// Get a deep copy of a portion of ia from index first to index last
// inclusive. If successful, return a pointer to a newly-allocated
// intarr_t containing a copy of the specfied section. If an error
// occurs, i.e. ia is null, first or last are out of bounds, last <
// first, or memory allocation fails, return a null pointer.
intarr_t* intarr_copy_subarray( intarr_t* ia, 
				unsigned int first, 
				unsigned int last ){
	if(ia == NULL || first > ia->len || last > ia->len || last < first){
		return NULL;
	}
	intarr_t *dup = malloc(sizeof(intarr_t));
	if(dup == NULL){
		return NULL;
	}
	dup->len = last - first + 1;
	dup->data = malloc(sizeof(int)*dup->len);
	for (int i = first; i <= last; i++){
		dup->data[i-first] = ia->data[i];
	}
	return dup;
}
