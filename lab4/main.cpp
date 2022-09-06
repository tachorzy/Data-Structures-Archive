#include <fstream>
#include <iostream>
#include "PriorityQueue.h"
#include "TaskHandler.h"
#include "ArgumentManager.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");
    string command = am.get("command");

    ifstream inFile;
    inFile.open(input);

    ofstream outFile;
    outFile.open(output);

    TaskHandler t;
    vector<pair<string, double>> v = t.retrieveInput(inFile);
    PriorityQueue p(v.size());

    for (int i = 0; i < v.size(); i++)
        p.insert(v[i]);
    p.buildHeap();
    p.extractAll(v.size(), outFile);
}
