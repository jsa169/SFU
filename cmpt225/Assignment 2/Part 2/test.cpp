//test.cpp
//
//
//
//

#include <iostream>
#include "Stack.h"

using namespace std;

int main(){
	Stack s = Stack();
	cout<<"The last element is: "<<s.peek()<<endl;

	s.pop();

	if(s.isEmpty() == true)
		cout<<"The stack is empty."<<endl;

	for(int i = 0; i < 15; i++){
		cout<<"Pushing "<<1<<endl;
		s.push(i);
	} 
	cout<<"The last element is: "<<s.peek()<<endl<<endl;

	for(int i = 0; i < 15; i++){
		cout<<"Popping "<<1<<endl;

		s.pop();
		cout<<"The last element is: "<<s.peek()<<endl<<endl;




	}

	cout<<"The last element is: "<<s.peek()<<endl;



	if(s.isEmpty() == true)
		cout<<"The stack is empty."<<endl;
}