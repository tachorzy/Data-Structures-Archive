#pragma once
#include <string>
using namespace std;

struct Node {
	string expression;
	string notation;
	Node* prev;
	Node* next;
};

class LinkedList {
private:
	Node* head;
	Node* tail;
public:
	LinkedList() { head = tail = nullptr; };
	bool isempty() { return (head == nullptr || tail == nullptr); }
	Node* getHead() { return head; }
	Node* getTail() { return tail; }
	int getSize();
	void addAtBeg(string);
	void addAtEnd(string);
	void addAtPos(string, int);
	void delAtPos(int);
	bool delNode(Node**,Node*);
	bool delNode(Node*);
	void delVals(string targ);
	void print(Node* headref);
} ;