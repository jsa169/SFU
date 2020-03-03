/* main.cpp */

#include "BST.h"
#include <iostream>

using namespace std;

int main () {
	int A[7] = {5, 8, 2, 3, 1, 9, 4};
  BST S;

	for (int i = 0; i < 7; i++) {
    cout << S << endl;
		S.insert(A[i]);
		if (i > 4) {
			S.top5();
		}
	}
  return 0;
}
