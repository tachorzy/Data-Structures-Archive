#pragma once
#include <string>

using namespace std;

struct player { 
	string name;
	int score;
	player* next;
};

class GameRoster { 
private:
	player* head;
	player* tail;
public:
	GameRoster() { head = nullptr, tail = nullptr; }
	player* getHead() { return head; }
	player* getTail() { return tail; }
	int getSize(player* head);
	bool isempty() { return(head == 0); }
	bool issorted(player* head);
	void dataManager(ifstream &inFile, ofstream &outFile);
	string removeWhitespace(string);
	int getScore(string);
	string getName(string);
	void addAtBeg(int, string);
	void selectionSort();
	void outputLinkedList(player* n, ofstream& outputFile);
	void print(player* p);	
};