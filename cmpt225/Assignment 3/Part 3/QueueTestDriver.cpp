// QueueTestDriver.cpp

#include "PriorityQueue.h"
#include <iostream>
#include <math.h>
using namespace std;


int main () {
    PriorityQueue<int> Q;

    //enqueue 1, 2, 3, 4, 5
    int a = 1;

    Q.enqueue(a);

    Q.printQueue();
    // dequeue 2x elements


    cout<<"peaking "<<Q.peek()<<endl;


    // enqueue 6, 7, 8, 9, 10
    for (int i = 1; i <= 10; i++) {
        
        cout <<endl << "enqueue " << i << endl;
        Q.enqueue(i);
    }

        Q.printQueue();

    Q.dequeue();
    cout<<"peaking "<<Q.peek()<<endl;

            Q.printQueue();


/*
    for(int i = 5; i>0; i --){
        int y = Q.peek();
        
        cout <<endl << "peek " << y << endl;
        Q.dequeue();
    }

    for (int i = 11; i <= 20; i++) {
        
        cout <<endl << "enqueue " << i << endl;
        Q.enqueue(i);
    }

    for(int i = 5; i>0; i --){
        int y = Q.peek();
        
        cout <<endl << "peek " << y << endl;
        Q.dequeue();
    }

    for (int i = 21; i <= 33; i++) {
        
        cout <<endl << "enqueue " << i << endl;
        Q.enqueue(i);
    }

    // dequeue all elements
    while (!Q.isEmpty()) {
        int y = Q.peek();
        
        cout <<endl << "peek " << y << endl;
        Q.dequeue();
    }
    */
    return 0;
}


