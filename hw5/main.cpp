#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include "BTree.h"
#include "ArgumentManager.h"

int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
  string command = am.get("command");

  ifstream inFile;
  inFile.open(input);
  ifstream cmdFile;
  cmdFile.open(command);

  ofstream outFile;
  outFile.open(output);

  int deg;
  string temp, line;
  cmdFile >> temp;
  deg = stoi(temp.substr(temp.find_first_of("1234567890")));
  BTree*  t = new BTree(deg);
  
  int n;
  set<int> s;
  while(!inFile.eof()){
    getline(inFile, line);
    replace(line.begin(), line.end(), '\t', ' ');
    stringstream ss(line);
    while(getline(ss, temp, ' ')){
      n = stoi(temp);
      if(s.find(n) == s.end()){
        t->insert(t->root, n);
      }
      s.insert(n);
    }
  }
  
  outFile << "Height=" << t->height(t->root) << endl;

  while(getline(cmdFile, line)){
    if(line.find("Level") != string::npos){
      int lvl = stoi(line.substr(line.find_first_of("1234567890")));
      t->levelOrder(lvl, outFile);
    }
  }
} 