#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char* argv[]) {

	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");
	ofstream of;
	of.open(output);

	LinkedList l;
	l.storeData(input);
	l.cmdHandler(command);
	l.outputLinkedList(l.getHead(), of);
}