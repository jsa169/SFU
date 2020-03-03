int scrambled( unsigned int a[], unsigned int b[], unsigned int len ){
	if (len == 0){
		return 1;
	}
	
	int x = 0;
	int y = 0;	

	for (int i = 0; i < 99; i++){
		for (int j = 0; j < len; j++){
			if (a[j] == i){
				x++;
			}
			if (b[j] == i){
				y++;
			}
		}
		if (x != y){
			return 0;
		}
		x = 0;
		y = 0;
	}
	return 1;
}


