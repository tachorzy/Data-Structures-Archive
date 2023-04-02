#pragma once
#include <string>

using namespace std;

struct Node {
	string data = "";
	Node* next;
};

class LinkedList {
	private:
		Node* head;
		Node* tail;
	public:
		LinkedList();
		bool isempty();
		bool isduplicate(string);
		Node* getHead();
		Node* getTail();
		string getFirstLine(string f);
		void storeData(string);
		int getLength(Node* n);
		void sortAlphabetically();
		void sortByLength();
		void addAtBeg(string);
		void addAtEnd(string);
		void addAtPos(string, int);
		void deleteEnd();
		void deleteAtVal(string);
		void cmdHandler(string);
		void outputLinkedList(Node* n, ofstream &outputFile);
};