/* 
 * BankSimApp.cpp
 *
 * Description: Simulates how customers line up and get serviced at a bank. A Event is recorded when
 *				ever a customer arrives or departures. At the end of the simulation, Print out the
 *				total number of customers processed, and the average amout of time spent waiting.
 *
 * Author: Jichuan Shi, Martin Suryadi
 * Date:10/27/2019
 */

//----------------------------------------------------------------------------------------------
//include Statements
#include "PriorityQueue.h"
#include "Queue.h"
#include "Event.h"
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------------------------
// Global Variables
bool tellerAvailable =  true;
int currentTime;
int customerCount = 0;
float totalWaitTime = 0;

//----------------------------------------------------------------------------------------------

// Processes an arrival event.
void processArrival(Event arrivalEvent, PriorityQueue<Event> *eventListPQ, Queue<Event> *bankQ){
	
	// Remove this event from the event list
	eventListPQ->dequeue();

	//customer = customer referenced in arrivalEvent
	Event customer = arrivalEvent;

	if (bankQ->isEmpty() && tellerAvailable){

		//departureTime = currentTime + transaction time in arrivalEvent
		int departureTime = currentTime + customer.getLength();
		
		//newDepartureEvent = a new departure event with departureTime
		Event newDepartureEvent = Event('D', departureTime);

		//eventListPQueue.add(newDepartureEvent)
		eventListPQ->enqueue(newDepartureEvent);
		tellerAvailable = false;
	 }else{
	 	bankQ->enqueue(customer);
	}
	customerCount++;

}

//----------------------------------------------------------------------------------------------
// Processes a departure event .
void processDeparture(Event departureEvent, PriorityQueue<Event> *eventListPQ, Queue<Event> *bankQ){
	// Remove this event from the event list
	eventListPQ->dequeue();

	if (!bankQ->isEmpty()){
		// Customer at front of line begins transaction
		Event customer = bankQ->peek();

		bankQ->dequeue();
		totalWaitTime += (currentTime-customer.getTime());

		//departureTime = currentTime + transaction time in customer
		int departureTime = currentTime + customer.getLength();

		//newDepartureEvent = a new departure event with departureTime
		Event newDepartureEvent = Event('D', departureTime);

		eventListPQ->enqueue(newDepartureEvent);
	}else{
		tellerAvailable = true;
	}
}

//----------------------------------------------------------------------------------------------
void simulate(){
	//Create an empty queue bankQueue to represent the bank line
	Queue<Event> bankQ;
	//Create an empty priority queue eventListPQueuefor the event list     
	PriorityQueue<Event> eventListPQ;

	cout << "Simulation Begins" << endl;

	// Create and add arrival events to event list
	int arrival, duration;
	Event E;
	while(cin>>arrival){
		cin>>duration;
		E = Event('A', arrival, duration);
		eventListPQ.enqueue(E);	
	}
	// Event  loop

	while (!eventListPQ.isEmpty())    
	{
			//newEvent = eventListPQueue.peek()
		E = eventListPQ.peek(); 

		// Get current time         
		//currentTime =  time of newEvent
		currentTime = E.getTime(); 
		//if (E an arrival event){
		if (E.getType() == 'A'){  
			processArrival(E, &eventListPQ, &bankQ);
			if(currentTime <10) cout<<"Processing an arrival event at time:\t "<< currentTime << endl; 
			else cout<<"Processing an arrival event at time:\t"<< currentTime << endl; 
		}else{          
			processDeparture(E, &eventListPQ, &bankQ);
			if(currentTime <10) cout<<"Processing a departure event at time:\t "<< currentTime << endl; 
			else cout<<"Processing a departure event at time:\t"<< currentTime << endl;     
		} 
	}

	cout << "Simulation Ends" << endl << endl;

	cout << "Final Statistics:" << endl << endl;
	cout << "\tTotal number of people processed: " << customerCount<<endl;
	cout << "\tAverage amount of time spent waiting: " << totalWaitTime/customerCount<<endl;
}

//----------------------------------------------------------------------------------------------
int main(){
	simulate();
	return 0;
}