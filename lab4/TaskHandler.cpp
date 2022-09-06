#include "TaskHandler.h"
vector<pair<string, double>> TaskHandler::retrieveInput(ifstream& in) {
	string line, task;
	double prio;
	
	vector<pair<string, double>> toDoList;

	while (getline(in, line)) {
		if (line == "")
			continue;
		cout << "line is: " << line << endl;

		if (line.find_first_of("0123456789") != string::npos) {
			task = line.substr(0, line.find_first_of("12345678910")-1);
			prio = stod(line.substr(line.find_first_of("12345678910")));
			toDoList.push_back(pair<string, double>(task, prio));
		}
	}
	return toDoList;
}



