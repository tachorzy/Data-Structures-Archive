#include "Stack.h"
#include <iostream>

int Stack::getSize() {
	sNode* cu = top;
	int c = 0;

	if (top == nullptr) { return c; }

	while (cu != nullptr) {
		c++;
		cu = cu->next;
	}
	return c;
}
void Stack::push(string s) {
	sNode* temp = new sNode();
	temp->op = s;
	temp->next = top;
	top = temp;
}

void Stack::pop() {
	if (isempty()) {
		return;
	}
	sNode* temp = top;
	top = top->next;
	delete temp;
	return;
}

string Stack::peek() {
	if (!isempty())
		return top->op;
	else {
		return "EMPTY";
	}
} 

void Stack::print(sNode* topref) {
	if (topref == nullptr)
		return;
	cout << topref->op << endl;
	return print(topref->next);
}