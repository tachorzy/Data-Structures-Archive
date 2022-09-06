#include "NodeManager.h"
#include <iostream>
#include <algorithm>
#include <sstream>

int NodeManager::priority(char x) {
	if (x == '/' || x == '*')
		return 2;
	if (x == '-' || x == '+')
		return 1;
	return -1;
}

bool NodeManager::isOperator(char c) {
	if (c == '*' || c == '/' || c == '+' || c == '-')
		return true;
	return false;
}
bool NodeManager::isInt(string s) {
	string::iterator iter = s.begin();
	while (iter != s.end() && isdigit(*iter)) { iter++; }
	return(!s.empty() && iter == s.end() || *s.begin() == '-'); //true if its the end and the string is empty. False if there wasn't a digit
}

void NodeManager::commandHandler(ifstream& in, ofstream& out) {
	string line;
	while (getline(in, line)) {
		if (line.find("convertList") != string::npos) {
			string argument = line.substr(line.find('(')+1, line.find(')') - line.find('(') - 1);
			convertList(argument);
		}
		else if (line.find("removeList") != string::npos) {
			string argument = line.substr(line.find('(')+1, line.find(')') - line.find('(') - 1);
			removeList(argument);
		}
		else if (line.find("printList") != string::npos && line.find("printListBackwards") == string::npos) {
			out << "List:" << endl;
			printList(linkedlist.getHead(), out);
			out << endl;
		}
		else if (line.find("printListBackwards") != string::npos) {
			out << "Reversed List:" << endl;
			printListBackwards(linkedlist.getTail(), out);
			out << endl;
		}
		else if (line.find("pushReserve") != string::npos) {
			string argument = line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1);
			cout << "(3) The current arg is: " << argument << endl;
			pushReserve(argument);
		}
		else if (line.find("popReserve") != string::npos) {
			string argument = line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1);
			popReserve(argument);
		}
		else if (line.find("flipReserve") != string::npos) {
			flipReserve();
		}
		else if (line.find("printReserveSize") != string::npos) {
			printReserveSize(out);
			out << endl;

		}
		else if (line.find("convertReserve") != string::npos) {
			convertReserve();
		}
		else if (line.find("printReserveTop") != string::npos) {
			printReserveTop(out);
			out << endl;
		}
		else if (line.find("emptyReserve") != string::npos) {
			string argument = line.substr(line.find('(')+1, line.find(')') - line.find('(') - 1);
			emptyReserve(argument);
		}
	}
}

string NodeManager::prefixToPostfix(string exp) {
	Stack stack;
	string postfix;
	for (int i = exp.length(); i >= 0; i--) {
		if (isalnum(exp[i])) {
			string temp= "";
			temp += exp[i];
			stack.push(temp);
		}
		else if (!stack.isempty() && isOperator(exp[i])) {
			string op1 = stack.peek();
			stack.pop();
			string op2 = stack.peek();
			stack.pop();
			postfix = op1 + op2 + exp[i];
			stack.push(postfix);
		}
	}
	return postfix;
}

string NodeManager::postfixToPrefix(string exp) {
	Stack stack;
	string prefix;
	for (int i = 0; i < exp.length(); i++) {
		if (isalnum(exp[i])) {
			string temp = "";
			temp += exp[i];
			stack.push(temp);
		}
		else if (!stack.isempty() && isOperator(exp[i])) {
			string op2 = stack.peek();
			stack.pop();
			string op1 = stack.peek();
			stack.pop();
			prefix = exp[i] + op1 + op2;
			stack.push(prefix);
		}
	}
	return prefix;
}

void NodeManager::fillList(ifstream& in) {
	string line, data;
	while (getline(in, line)) {
		line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
		linkedlist.addAtEnd(line);
	}
}

void NodeManager::convertList(string cmd) {	
	Node* cu = new Node();
	cu = linkedlist.getHead();

	while (cu != nullptr) {
		if (cmd == "all") {
			if (cu->notation == "prefix") {
				cu->expression = prefixToPostfix(cu->expression);
				cu->notation = "postfix";
			}
			else if (cu->notation == "postfix") {
				cu->expression = postfixToPrefix(cu->expression);
				cu->notation = "prefix";
			}
		}
		else if (cmd == "prefix" && cu->notation == "prefix") {
			cu->expression = prefixToPostfix(cu->expression);
			cu->notation = "postfix";
		}
		else if (cmd == "postfix" && cu->notation == "postfix") {
			cu->expression = postfixToPrefix(cu->expression);
			cu->notation = "prefix";
		}

		if (isInt(cmd)) {
			stringstream ss(cmd);
			int n = 0;
			ss >> n;

			if (n > linkedlist.getSize()) { return; }

			for (int pos = 0; pos < linkedlist.getSize(); pos++) {
				if ((*cmd.begin() == '-') && (pos == 0) || (n == pos)) {
					if (cu->notation == "prefix") {
						cu->expression = prefixToPostfix(cu->expression);
						cu->notation = "postfix";
					}
					else if (cu->notation == "postfix") {
						cu->expression = postfixToPrefix(cu->expression);
						cu->notation = "prefix";
					}
					return;
				}
			}
		}
		cu = cu->next;
	}
}

void NodeManager::removeList(string cmd) { //FIX ME @ the end of the Semester.
	if (isInt(cmd)) {
		if ((*cmd.begin() == '-') && isInt(cmd) || cmd == "0")
			linkedlist.delAtPos(0);
		else {
			stringstream ss(cmd);
			int n = 0;
			ss >> n;
			if (n > linkedlist.getSize())
				return;
			linkedlist.delAtPos(n);
			return;
		}
	}
	else if (cmd == "all") {
		Node* cu = linkedlist.getHead();
		while (!linkedlist.isempty() && cu != nullptr) {
			linkedlist.delNode(&cu, cu);
			if (cu != nullptr)
				cu = cu->next;
		}
	}
	else if (cmd == "prefix" || cmd == "postfix"){
		Node* cu = linkedlist.getHead();
		while (cu != nullptr) {
			if (cu->notation == cmd) {
				linkedlist.delNode(&cu, cu);
				if (cu != nullptr)
					cu = cu->next;
			}
		}
	}
}

void NodeManager::printList(Node* headref, ofstream& out) {
	if (linkedlist.isempty()) {
		out << "EMPTY" << endl;
		return;
	}
	if (headref == nullptr)
		return;
	out << headref->notation << ":" << headref->expression << endl;
	return printList(headref->next, out);
}

void NodeManager::printListBackwards(Node* tailref, ofstream& out) { //maybe do this a more efficient way?
	if (linkedlist.isempty()) {
		out << "EMPTY" << endl;
		return;
	}
	if (tailref == nullptr)
		return;
	out << tailref->notation << ":" << tailref->expression << endl;
	return printListBackwards(tailref->prev, out);
}

void NodeManager::pushReserve(string cmd) { //FIX ME @ the end of the semester, account for brevity and time and space complexity this time
	Node* temp = new Node();
	Node* cu = new Node();
	LinkedList t; //FIND A MUCH BETTER WAY TO DO THIS!!!

	cu = linkedlist.getHead();

	if (linkedlist.isempty()) { return; }

	if (isInt(cmd)) {
		if (*cmd.begin() == '-' || cmd == "0") {
			reserve.push(cu->notation + ":" + cu->expression);
			linkedlist.delAtPos(0);
		}
		else {
			stringstream ss(cmd);
			int pos = 0;
			ss >> pos;
			for (int i = 0; cu != nullptr && i < pos; i++)
				cu = cu->next;
			if (pos > linkedlist.getSize())
				return;
			reserve.push(cu->notation + ":" + cu->expression);
			linkedlist.delAtPos(pos);
		}
		return;
	}

	while(cu != nullptr) {
		string cuData = cu->notation + ":" + cu->expression;

		if ((cmd == "prefix" || cmd == "postfix") && cu->notation == cmd) {
			temp = cu;
				reserve.push(cu->notation + ":" + cu->expression);
				cout << reserve.getSize() << endl;

				linkedlist.delNode(&cu, temp);
		}
		else if (cmd == "all") {
			reserve.push(cuData);
			linkedlist.delNode(&cu, temp); //ends up deleting all?
			cu = cu->next;
		}
		else if(cu->notation != cmd){
			t.addAtEnd(cuData); //FIND A MUCH BETTER WAY TO DO THIS!!!
			cu = cu->next; //TEST THIS AT THE END OF THE ASSIGNMENT
		}
		if (cu == nullptr) { break;};
	}

	linkedlist = t;//FIND A MUCH BETTER WAY TO DO THIS!!!
}

void NodeManager::popReserve(string cmd) {
	string newData;
	if (isInt(cmd)) {
		if (*cmd.begin() == '-' || cmd == "0") {
			newData = reserve.peek();
			reserve.pop();
			linkedlist.addAtBeg(newData);
		}
		else {
			stringstream ss(cmd);
			int pos = 0;
			ss >> pos;
			newData = reserve.peek();
			reserve.pop();
			linkedlist.addAtPos(newData, pos);
		}
		return;
	}
	return;
}

void NodeManager::flipReserve() {

	if (reserve.isempty() || reserve.getSize() <= 1)
		return;

	Stack temp;
	while(!reserve.isempty()) {
		temp.push(reserve.peek());
		reserve.pop();
	}
	reserve = temp;
}

void NodeManager::printReserveSize(ofstream& out) {
	out << "Reserve Size: " << reserve.getSize() << endl;
}

void NodeManager::printReserveTop(ofstream& out) {
	out << "Top of Reserve: " << reserve.peek() << endl;
}

void NodeManager::convertReserve() {
	string reserveTop = reserve.peek();
	if (reserveTop.find("prefix") != string::npos) {
		string notation = "postfix";
		string expression = prefixToPostfix(reserveTop.substr(reserveTop.find(':') + 1));
		reserve.pop();
		reserve.push(notation + ":" + expression);
	}
	else if (reserveTop.find("postfix") != string::npos) {
		string notation = "prefix";
		string expression = postfixToPrefix(reserveTop.substr(reserveTop.find(':') + 1));
		reserve.pop();
		reserve.push(notation + ":" + expression);
	}

}

void NodeManager::emptyReserve(string cmd) {
	string cuData;
	int pos = 0;
	if (isInt(cmd)) {
		if (*cmd.begin() == '-' || cmd == "0") {
			while(!reserve.isempty()){
				cuData = reserve.peek();
				linkedlist.addAtBeg(cuData);
				reserve.pop();
			}
		}
		else {
			stringstream ss(cmd);
			ss >> pos;
			if (pos >= reserve.getSize()) {
				while(!reserve.isempty()) {
					cuData = reserve.peek();
					linkedlist.addAtEnd(cuData);
					reserve.pop();
				}
			} 
			else {
				while(!reserve.isempty()) {
					cuData = reserve.peek();
					linkedlist.addAtPos(cuData, pos);
					reserve.pop();
				}
			}
	}
	
	}
}