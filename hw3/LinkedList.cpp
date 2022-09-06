#include "LinkedList.h"
#include <iostream>

int LinkedList::getSize() {
	Node* cu = new Node();
	cu = head;
	int c = 0;
	while (cu != nullptr) {
		c++;
		cu = cu->next;
	}

	return c;
}
void LinkedList::addAtBeg(string s) {
	Node* temp = new Node();
	temp->notation = s.substr(0, s.find(':'));
	temp->expression = s.substr(s.find(':') + 1);
	temp->next = nullptr;

	if (isempty()) {
		head = temp;
		tail = temp;
		return;
	}
	temp->notation = s.substr(0, s.find(':'));
	temp->expression = s.substr(s.find(':') + 1);
	temp->next = head;
	head->prev = temp;
	head = temp;
	return;
}

void LinkedList::addAtEnd(string s) {
	Node* temp = new Node();
	temp->notation = s.substr(0, s.find(':'));
	temp->expression = s.substr(s.find(':')+1);
	temp->next = nullptr;

	if (isempty()) {
		head = temp; 
		tail = temp;
		return;
	}
	temp->prev = tail;
	tail->next = temp;
	tail = temp;
	return;
}

void LinkedList::addAtPos(string s, int pos) { //Check over this when coming back @ the end of the semester
	Node* newNode = new Node();
	Node* cu = new Node();
	Node* next = new Node();
	cu = head;
	newNode->notation = s.substr(0, s.find(':'));
	newNode->expression = s.substr(s.find(':') + 1);

	if (isempty()){
		head = tail = newNode;
		return;
	}

	if (pos <= 0) {
		cu->next = head;
		head->prev = newNode;
		head = newNode;
		return;
	}

	while (pos != 1) {
		cu = cu->next;
		pos--;
	}

	if (cu == nullptr || pos > getSize()) {
		cu->next = newNode;
		newNode->prev = cu;
	}
	else {
		next = cu->next;
		cu->next = newNode;
		next->prev = newNode;
		newNode->next = next;
		newNode->prev = cu;
	}
	return;

}

//REVISIT @ THE END OF THE SEMESTER
void LinkedList::delAtPos(int pos) {
	Node* cu = head; 
	Node* temp = new Node();

	if (isempty()) { return; }

	if (pos <= 0 && head != nullptr) {
		head->prev = nullptr;
		head = cu->next;
		delete(cu); 
		return; 
	}
	
	for (int i = 0; i < pos && cu->next != nullptr; i++)
		cu = cu->next;

	if (cu->next == nullptr) {
		temp = cu->prev;
		temp->next = nullptr;
	}
	else {
		cu->prev->next = cu->next;
		cu->next->prev = cu->prev;
	}
	delete(cu);
}
//REVISIT @ THE END OF THE SEMESTER
bool LinkedList::delNode(Node** headref, Node* cu) { //based on a tutorialpoints function.
	Node* temp = new Node();

	if (isempty() || cu == nullptr) { return false; }

	if (cu == *headref) {
		head = *headref = cu->next;
	}
	if (cu->next != nullptr) {
		cu->next->prev = cu->prev;
	}
	if (cu->prev != nullptr) {
		cu->prev->next = cu->next;
	}
	if (cu->prev == nullptr) { head = cu->next; }
	delete(cu);
	return true;
}

void LinkedList::print(Node* headref) {
	if (headref == nullptr)
		return;
	cout << headref->notation << ':' << headref->expression << endl;
	return print(headref->next);
}