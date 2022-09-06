#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "NodeManager.h"
#include "ArgumentManager.h"

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	ifstream inFile;
	inFile.open(input);
	
	ifstream commandFile;
	commandFile.open(command);

	ofstream outFile;
	outFile.open(output);

	NodeManager nm;
	nm.fillList(inFile);
	nm.commandHandler(commandFile, outFile);
}
