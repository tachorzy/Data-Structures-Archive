#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class TaskHandler {
public:
	vector<pair<string, double>> retrieveInput(ifstream& in);
};