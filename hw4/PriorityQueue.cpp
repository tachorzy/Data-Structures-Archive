#include "PriorityQueue.h"

void PriorityQueue::enqueue(string command, int prio) {
	Node* newNode = new Node();
	newNode->prio = prio;
	newNode->command = command;
	
	if (isempty())
		front = newNode;
	else if (front->prio > newNode->prio) {
		newNode->next = front;
		front = newNode;
	}
	else {
		Node* cu = front;
		while (cu->next != nullptr && cu->next->prio <= newNode->prio)
			cu = cu->next;

		newNode->next = cu->next;
		cu->next = newNode;
	}
}

void PriorityQueue::dequeue() {
	if (isempty())
		return;

	Node* temp = new Node();
	temp = front;
	front = front->next;
	delete temp;
} 

string PriorityQueue::peek() {
	if (isempty())
		return "the priority queue is empty.";
	return front->command;
}

