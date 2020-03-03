// QueueTestDriver.cpp

#include "Queue.h"
#include <iostream>
using namespace std;


int main () {
    Queue<int> Q;

    // enqueue 1, 2, 3, 4, 5
    /*for (int i = 1; i <= 20; i++) {
        
        cout <<endl<< "enqueue " << i << endl;
        Q.enqueue(i);
    }*/


    // dequeue 2x elements
        int y;
        try{ 
            y = Q.peek();
            cout <<endl << "peek " << y<< endl;
        }catch(EmptyDataCollectionException & anException){
            cout<<anException.what()<<endl;
        }



        try{
            Q.dequeue();
        }catch(EmptyDataCollectionException & anException){
            cout<<anException.what()<<endl;
        }



     //enqueue 6, 7, 8, 9, 10
    for (int i = 1; i <= 10; i++) {
        
        cout <<endl << "enqueue " << i << endl;
        Q.enqueue(i);
    }
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


