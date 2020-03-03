all: test

test: test.o PriorityQueue.h BinaryHeap.h Queue.h Event.o EmptyDataCollectionException.o
	g++ -Wall -o test test.o Event.o EmptyDataCollectionException.o

test.o: test.cpp
	g++ -c -std=c++98 test.cpp

Event.o: Event.cpp Event.h
	g++ -c Event.cpp

EmptyDataCollectionException.o: EmptyDataCollectionException.cpp EmptyDataCollectionException.h
	g++ -c EmptyDataCollectionException.cpp

clean:
	rm -f test *.o
