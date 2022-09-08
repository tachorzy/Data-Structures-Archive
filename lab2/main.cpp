#include <iostream>
#include <fstream>
#include "GameRoster.h"
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");
	
	ofstream of;
	of.open(output);

	ifstream in;
	in.open(input);

	GameRoster roster;
	roster.dataManager(in, of);
	roster.selectionSort();
	roster.outputLinkedList(roster.getHead(), of);
	roster.print(roster.getHead());
}