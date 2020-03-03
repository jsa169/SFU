// QueueTestDriver.cpp

#include "Queue.h"
#include <iostream>
using namespace std;


int main () {
    Queue Q;

    // enqueue 1, 2, 3, 4, 5
    /*for (int i = 1; i <= 20; i++) {
        
        cout <<endl<< "enqueue " << i << endl;
        Q.enqueue(i);
    }*/


    // dequeue 2x elements
    for (int i = 0; i < 2; i++) {
        int y = Q.peek();
        
        cout <<endl << "peek " << y << endl;
        Q.dequeue();
    }


    // enqueue 6, 7, 8, 9, 10
    for (int i = 21; i <= 35; i++) {
        
        cout <<endl << "enqueue " << i << endl;
        Q.enqueue(i);
    }


    // dequeue all elements
    while (!Q.isEmpty()) {
        int y = Q.peek();
        
        cout <<endl << "peek " << y << endl;
        Q.dequeue();
    }

    return 0;
}

