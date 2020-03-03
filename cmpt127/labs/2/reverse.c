void reverse( int arr[], unsigned int len ){
	int a[len];
	int count = 0;
	for (int i = len - 1; i >= 0;i--){
		a[count] = arr[i];
		count++;
	}
	for (int i = len - 1; i >=0; i--){
		arr[i] = a[i];
	}
}

