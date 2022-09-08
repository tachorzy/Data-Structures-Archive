#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
#include "Graph.h"

int main(int argc, char* argv[]) {
  ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

  ifstream inFile;
  inFile.open(input);

  ofstream outFile;
  outFile.open(output);

  int V, E, S, D;
  int a, b, c;

  inFile >> V >> E >> S >> D;
  Graph g(V+1);
  while(!inFile.eof()){
    inFile >> a >> b >> c;
    g.addEdge(a,b,c);
  }
  g.shortestPath(S, D, outFile);
} 