all: qtd

qtd: QueueTestDriver.o Queue.h EmptyDataCollectionException.o
	g++ -Wall -o qtd QueueTestDriver.o EmptyDataCollectionException.o

QueueTestDriver.o: QueueTestDriver.cpp 
	g++ -c QueueTestDriver.cpp -std=c++98

EmptyDataCollectionException.o: EmptyDataCollectionException.cpp EmptyDataCollectionException.h
	g++ -c EmptyDataCollectionException.cpp -std=c++98

clean:
	rm -f qtd *.o