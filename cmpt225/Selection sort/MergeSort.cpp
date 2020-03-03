//SelectionSort.cpp
//
//
//
//Jack




#include <iostream>

using namespace std;

void merge(int * a, int low, int mid, int high){
	int l = low;
	int m = mid + 1;
	int index = 0;
	int arr[high-low+1];
	while((l < mid+1)&&(m < high)){
		if (a[l] < a[m]){
			arr[index] = a[l];
			l++;
		}else{
			arr[index] = a[m];
			m++;
		}
		index++;
	}
	while(l < mid){
		arr[index] = a[l];
		index++;
		l++;
	}
	while(m < high){
		arr[index] = a[m];
		index++;
		m++;
	}
	for(int i = 0; i <= (high - low); i++){
		a[low+i] = arr[i];
	}
}

void mergeSort(int * a, int low, int high){

	if(low < high){
		int mid = (low + high)/2;
		mergeSort(a, low, mid);
		mergeSort(a, mid + 1, high);
		merge(a, low, mid, high);
	}



}

int main(){
	int len = 10;
	int a[10] = {6,5,4,3,2,7,8,9,1,0};
	for(int i = 0; i < len; i++){
		if(i == 0) cout<<"[";
		if(i == len - 1) cout<<a[i]<<"]"<<endl;
		else cout<<a[i]<<", ";
	}

	mergeSort(a, 0, len);

		for(int i = 0; i < len; i++){
		if(i == 0) cout<<"[";
		if(i == len - 1) cout<<a[i]<<"]"<<endl;
		else cout<<a[i]<<", ";
	}
}