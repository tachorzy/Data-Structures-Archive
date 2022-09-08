#include <iostream>
#include <string>
#include "CommandManager.h"
#include "ArgumentManager.h"

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	ifstream inFile;
	inFile.open(input);
	ofstream outFile;
	outFile.open(output);

	CommandManager cm;
	cm.fileHandler(inFile);
	cm.commandHandler(outFile);
}


