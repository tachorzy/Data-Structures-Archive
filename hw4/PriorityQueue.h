#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
//LinkedList implementation of a Priority Queue, where the head is always the highest priority
struct Node {
	int prio;
	string command;
	Node* next;
};

class PriorityQueue {
	private:
		Node* front;
	public:
		PriorityQueue() { front = nullptr; }
		bool isempty() { return (front == nullptr); }
		void enqueue(string command, int prio);
		void dequeue();
		string peek();	
};