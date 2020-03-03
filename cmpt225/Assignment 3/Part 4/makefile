all: bsim

bsim: BankSimApp.o PriorityQueue.h BinaryHeap.h Queue.h Event.o EmptyDataCollectionException.o
	g++ -Wall -o bsim BankSimApp.o Event.o EmptyDataCollectionException.o

BankSimApp.o: BankSimApp.cpp
	g++ -c -std=c++98 BankSimApp.cpp

Event.o: Event.cpp Event.h
	g++ -c Event.cpp

EmptyDataCollectionException.o: EmptyDataCollectionException.cpp EmptyDataCollectionException.h
	g++ -c EmptyDataCollectionException.cpp

clean:
	rm -f bsim *.o
