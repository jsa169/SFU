// QueueTestDriver.cpp

#include "BinaryHeap.h"
#include <iostream>
#include <math.h>

using namespace std;


int main () {
    BinaryHeap<int> Q;

    // enqueue 1, 2, 3, 4, 5
    /*for (int i = 1; i <= 20; i++) {
        
        cout <<endl<< "enqueue " << i << endl;
        Q.enqueue(i);
    }*/


    // dequeue 2x elements
        int y;
        try{ 
            y = Q.retrieve();
            cout <<endl << "retrieve " << y<< endl;
        }catch(EmptyDataCollectionException & anException){
            cout<<anException.what()<<endl;
        }



        try{
            Q.remove();
        }catch(EmptyDataCollectionException & anException){
            cout<<anException.what()<<endl;
        }

        int a = 0;
        Q.insert(a);

        try{ 
            y = Q.retrieve();
            cout <<endl << "retrieve " << y<< endl;
        }catch(EmptyDataCollectionException & anException){
            cout<<anException.what()<<endl;
        }

        while(a < 5){
            Q.insert(a);
            a++;
        }

        Q.printBinaryHeap();


        while(a >0){
            Q.insert(a);
            a--;
        }

        Q.printBinaryHeap();

        Q.remove();

        Q.printBinaryHeap();




    /* enqueue 6, 7, 8, 9, 10
    for (int i = 1; i <= 10; i++) {
        
        cout <<endl << "enqueue " << i << endl;
        Q.enqueue(i);
    }

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


