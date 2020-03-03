#include <stdio.h>
#include <assert.h>

int is_sorted(int arr[], int len){
	for (int i = 0; i < len - 1; i++){
		if (arr[i + 1] < arr[i]) return 0;
	}
	return 1;
}

int BinarySearch(int arr[], int len, int target){
	int first = 0;
	int last = len - 1;
	while (first < last){
		assert(is_sorted(arr, len) != 0);
		int mid = (first + last ) / 2;
		if (target == arr[mid]) return mid;
		if (target < arr[mid]) last = mid - 1;
		else first = mid + 1;
	}
}

int main (){
	//int arr[10] = {12, 45, 8, 49, 5, 17, 24, 11, 38, 35};
	int arr[10] = {5, 8, 11, 12, 17, 24, 35, 38, 45, 49};
	int result = BinarySearch(arr, 10, 17);
	printf("%d is at %d\n", arr[result], result);
}