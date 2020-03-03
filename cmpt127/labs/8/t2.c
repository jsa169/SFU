#include "point_array.h"
#include <stdio.h>
#include <stdlib.h>



/* TASK 1 */

// Safely initalize an empty array structure.
void point_array_init( point_array_t* pa ){
	pa->len = 0;
	pa->reserved = 2;
	pa->points = malloc(sizeof(point_t)*2);
}
/* TASK 2 */

// Resets the array to be empty, freeing any memory allocated if
// necessary.
void point_array_reset( point_array_t* pa ){
	pa->points=realloc(pa->points, 0);
	pa->len = 0;
	pa->reserved = 0;

}
/* TASK 3 */

// Append a point to the end of an array. If successful, return 0,
// else return 1;
int point_array_append( point_array_t* pa, point_t* p ){
	if(p == NULL) return 0;
	if(pa->len < pa->reserved){
		pa->points[pa->len].x = p->x;
		pa->points[pa->len].y = p->y;
		pa->points[pa->len].z = p->z;
		pa->len++;
		return 0;
	}
	pa->points = realloc(pa->points, sizeof(point_t)*(pa->len)*2);
	if(pa->points == NULL) return 1;
	pa->points[pa->len].x = p->x;
	pa->points[pa->len].y = p->y;
	pa->points[pa->len].z = p->z;
	pa->len++;
	pa->reserved = pa->reserved*2;
	return 0;
}
/* TASK 4 */

// Remove the point at index i from the array, reducing the number of elements
// stored in the array by one. The order of points in the array may change.
// If successful, return 0, else return 1; 
int point_array_remove( point_array_t* pa, unsigned int i ){
	if(pa-> len == 0 || i >= pa->len) return 1;
	pa->points[i].x = pa->points[pa->len-1].x;
	pa->points[i].y = pa->points[pa->len-1].y;
	pa->points[i].z = pa->points[pa->len-1].z;
	pa->points[pa->len-1].x = 0;
	pa->points[pa->len-1].y = 0;
	pa->points[pa->len-1].z = 0;
	pa->len--;
	return 0;

}