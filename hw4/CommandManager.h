#pragma once
#include "PriorityQueue.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "Queue.h"

using namespace std;

class CommandManager {
	private:
		Queue q;
		PriorityQueue pq;
	public:
		Queue getQueue() { return q; }
		PriorityQueue getPQueue() { return pq; }

		void fileHandler(ifstream& in);
		void commandHandler(ofstream&);
		void decode(string);
		void replace(char c1, char c2);
		void add(char c1, char c2);
		void remove(char c);
		void swap(char c1, char c2);
		void print(ofstream&);
};