#include <stdio.h>

int InRectangle( float pt[2], float rect[4]){
	if ((pt[0] >= rect[0] && pt[0] <= rect[2]) || (pt[0] <= rect[0] && pt[0] >= rect[2])){
		// If point is between x1 and x2

		if((pt[1] >= rect[1] && pt[1] <= rect[3]) || (pt[1] <= rect[1] && pt[1] >= rect[3])){
			// If point is between y1 and y2
			return 1;
		}

		return 0;

	}

	return 0;
}
