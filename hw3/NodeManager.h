#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
#include "Stack.h"

class NodeManager {
	private:
		LinkedList linkedlist;
		Stack reserve;
	public:
		int priority(char);
		bool isOperator(char);
		bool isInt(string);
		string prefixToPostfix(string);
		string postfixToPrefix(string);
		void fillList(ifstream& in);
		LinkedList getList() { return linkedlist; }
		Stack getReserve() { return reserve; }
		void commandHandler(ifstream& in, ofstream& out);
		void convertList(string cmd);
		void removeList(string cmd);
		void printList(Node*, ofstream&);
		void printListBackwards(Node*, ofstream&);
		void pushReserve(string cmd);
		void popReserve(string cmd);
		void flipReserve();
		void printReserveSize(ofstream&);
		void convertReserve();
		void printReserveTop(ofstream&);
		void emptyReserve(string);

};