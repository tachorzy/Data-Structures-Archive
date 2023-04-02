#include "LinkedList.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

LinkedList::LinkedList() { 
	head = nullptr;
	tail = nullptr; }

bool LinkedList::isempty() { return(head == 0); }

bool LinkedList::isduplicate(string s) { 
	Node* current = new Node();
	current = head;

	if (current == nullptr) { return false; }
	else {
		while (current->next != nullptr) {
			if (current->data == s) {
				return true;
			}
			current = current->next;
		}
	}
}

Node* LinkedList::getHead() { return head; }
Node* LinkedList::getTail() { return tail; }

int LinkedList::getLength(Node* n) {
	int count = 0;
	Node* current = new Node();
	current = n;
	while (current != nullptr) {
		count++;
		current = current->next;
	}
	return count;
}

string LinkedList::getFirstLine(string f) { //first line of the file tells us how to intially store our data.
	ifstream input_file;
	input_file.open(f);
	string firstLine;

	if (input_file.good()) {
		getline(input_file, firstLine);
	}
	return firstLine;
} 

void LinkedList::storeData(string f) {
	ifstream input_file;
	input_file.open(f);
	string line;

	while (getline(input_file, line)) {
		if (line != "" && line != getFirstLine(f)) {
			Node* temp = new Node();
			temp->data = line;
			
			if (isduplicate(line) == true)
				continue;
			else if (getFirstLine(f) == "End") {
				if (head == nullptr) { head = temp; tail = temp; }
				else
					addAtEnd(line);
			}
			else if (getFirstLine(f) == "Alphabetically") {
				addAtBeg(line);
				sortAlphabetically();
			}
			else if (getFirstLine(f) == "Length") {
				addAtBeg(line);
				sortByLength();
			}
			else { //the other case is add at the beginning, and any invalid first line commands will be ignored this way.
				if (head == nullptr) { head = temp; tail = temp; }
				else
					addAtBeg(line);
			}
		}
	}
}

void LinkedList::sortAlphabetically() {
	Node* current = new Node();
	current = head;

	if (isempty()) { return; }

	while (current->next != nullptr) {
		Node* next = current->next;	
		while (next->next != nullptr) {
			if (current->data > next->data) {
				swap(next->data, current->data);
			}
			next = next->next;
		}
		if(next->next == nullptr && current->data > next->data)
			swap(next->data, current->data);
		current = current->next;
	}
}

void LinkedList::sortByLength() { 
	Node* current = new Node();
	current = head;

	if (isempty()) { return; }

	while (current->next != nullptr) {
		Node* next = current->next;
		while (next->next != nullptr) {
			if (current->data.length() > next->data.length()) {
				swap(next->data, current->data);
			}
			next = next->next;
		}
		if (next->next == nullptr && current->data.length() > next->data.length())
			swap(next->data, current->data);
		current = current->next;
	}
}

void LinkedList::addAtBeg(string line) { 
	Node* temp = new Node();
	temp->data = line;
	temp->next = nullptr;

	if (isempty()) { head = temp; tail = temp; return; }
	else if (isduplicate(line)) { return; }

	temp->next = head;
	head = temp;
}

void LinkedList::addAtEnd(string line) { 
	Node* current = head;
	Node* temp = new Node();
	
	temp->data = line;
	temp->next = nullptr;

	if (isempty()) { tail = temp; return; }
	else if (isduplicate(line)) { return; }

	while (current->next != nullptr)
		current = current->next;
	current->next = temp;
	tail = temp;
}

void LinkedList::addAtPos(string sentence, int pos) {
	Node* temp = new Node();
	temp->data = sentence;
	temp->next = nullptr;

	Node* current = new Node();
	current = head;

	if (pos == getLength(head)) {
		addAtEnd(temp->data);
		return;
	}

	for (int i = 0; i < pos; i++)
		current = current->next;

	temp->next = current->next;
	current->next = temp;
	cout << temp->data << endl;
}

void LinkedList::deleteEnd() { 
	Node* current = new Node();
	Node* previous = new Node();
	if (isempty()) { return; }
	if (head->next == nullptr) { delete head; return; }

	current = head;
	while (current->next != nullptr) {
		previous = current;
		current = current->next;
	}
	previous->next = nullptr;
	tail = previous;
	delete current;
}

void LinkedList::deleteAtVal(string target) {
	Node* temp = new Node();
	Node* current = new Node();
	
	if (isempty()) { return; }
	if (head->data.find(target) != string::npos) {
		temp = head;
		head = head->next;
		delete temp;
	}
	else if (tail->data.find(target) != string::npos) { deleteEnd(); }
	else {
		current = head;
		while (current->next != nullptr)
		{	
			if (current->next->data.find(target) != string::npos)
			{
				temp = current->next;
				current->next = current->next->next;
				delete temp;
			}
			else { current = current->next; }
		}
	}
}

void LinkedList::cmdHandler(string f) { 
	ifstream cmd_file;
	cmd_file.open(f);
	string cmd;

	if (cmd_file.peek() == ifstream::traits_type::eof()) { return; } //case for when a file is empty source: stackoverflow thread.

	while (getline(cmd_file, cmd)) {
		if (cmd.find("Add") != string::npos) {
			string s = cmd.substr(cmd.find('(')+1, (cmd.find(')') - cmd.find('('))-1);
			stringstream temp(s); //using a stringstream, source: geeksforgeeks
			int index;
			temp >> index;

			string content = cmd.substr(cmd.find('[')+1, (cmd.find(']') - cmd.find('[')) - 1);
			if (index > getLength(head) || index < 0) {
				continue;
			}
			else if (isduplicate(content) == true) {
				continue;
			}
			else if (index == 0)
				addAtBeg(content);
			else if (index == getLength(head)) {
				addAtEnd(content);
			}
			else {
				addAtPos(content, index);
			}
		}
		else if (cmd.find("Remove") != string::npos) {
			string target = cmd.substr(cmd.find('[') + 1, (cmd.find(']') - cmd.find('[')) - 1);
			
			for (int i = 0; i < getLength(head)+1; i++) { //thoroughly iterating every node; inclusive to the head and tail.
				deleteAtVal(target);
			}
		}

		else if (cmd.find("Sort") != string::npos) {
			if (cmd.find("alphabetically") != string::npos)
				sortAlphabetically();
			else if (cmd.find("length") != string::npos)
				sortByLength();
		}
		else { continue; } //ignores any weird lines with invalid commands.
	}
}

void LinkedList::outputLinkedList(Node* n, ofstream &outputFile) {
	if (n == 0) //base case
		return;
	else
		outputFile << n->data << endl;
	outputLinkedList(n->next, outputFile);
}