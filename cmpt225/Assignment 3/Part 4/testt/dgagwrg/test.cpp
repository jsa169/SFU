#include "PriorityQueue.h"
#include "Queue.h"
#include "Event.h"
#include "EmptyDataCollectionException.h"
#include <iostream>

using namespace std;


int main(){

	//Create an empty queue bankQueue to represent the bank line
	Queue<int> bankQ;
	
	//Create an empty priority queue eventListPQueuefor the event list     
	PriorityQueue<Event> eventListPQ;

	bool tellerAvailable =  true;

	// Create and add arrival events to event list
	int arrival, duration;
	
	Event E;
	while(cin>>arrival){
		cin>>duration;
		E = Event('A', arrival, duration);
		E.printEvent();
		eventListPQ.enqueue(E);
	}
	
	E = eventListPQ.peek(); 
		// Get current time         
		//currentTime =  time of newEvent
	E.printEvent();
	
	int currentTime = E.getTime(); 

	return 0;
}

