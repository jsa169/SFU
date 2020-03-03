//Test

#include <iostream>
#include "Patient.h"

int main(){
	Patient one = Patient("1235486825");
	cout << one;
	one.setName("sfu");
	one.setEmail("abc@sfu.ca");
	one.setPhone("111-111-1111");
	one.setAddress("999 AAA AVe");
	cout << one;
}