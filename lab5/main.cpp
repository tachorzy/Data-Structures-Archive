#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;

map<string, int> filehandler(ifstream& in) {
	string line, temp;
	map<string, int> m;
	getline(in, temp); //skip first line.

	while (getline(in, line, ' ')) {
		line.erase(remove(line.begin(), line.end(), '\n'), line.end());
		if(m.find(line) != m.end())
			m[line]++;
		else
			m.insert(pair<string, int>(line, 1));
	}
	return m;
}

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	ifstream inFile;
	inFile.open(input);
	ofstream outFile;
	outFile.open(output);

	map<string, int> m = filehandler(inFile);
	for (map<string,int>::iterator it = m.begin(); it != m.end(); it++)
		outFile << it->first << ": " << it->second << endl;;
}

