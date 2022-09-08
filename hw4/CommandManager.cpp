#include "CommandManager.h"

void CommandManager::fileHandler(ifstream& in) {
	string line;
	while (getline(in, line)) {
		if (line.find("DECODE") != string::npos || line.find("REPLACE") != string::npos || line.find("ADD") != string::npos
			|| line.find("REMOVE") != string::npos || line.find("SWAP") != string::npos || line.find("PRINT") != string::npos) {
			string cmd = line.substr(0, line.find('('));
			int prio = stoi(line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1));
			pq.enqueue(cmd, prio);
		}
	}
}

void CommandManager::commandHandler(ofstream& out) {
	while (!pq.isempty()) { 
		string cmd = pq.peek();
    pq.dequeue();
		if (cmd.find("DECODE") != string::npos)
			decode(cmd.substr(cmd.find('[') + 1, cmd.find(']') - cmd.find('[') - 1));
		else if (cmd.find("REPLACE") != string::npos)
			replace(cmd.at(cmd.find(',') - 1), cmd.at(cmd.find(',') + 1));
		else if (cmd.find("ADD") != string::npos)
			add(cmd.at(cmd.find(',') - 1), cmd.at(cmd.find(',') + 1));
		else if (cmd.find("REMOVE") != string::npos)
			remove(cmd.at(cmd.find('[') + 1));
		else if (cmd.find("SWAP") != string::npos)
			swap(cmd.at(cmd.find(',') - 1), cmd.at(cmd.find(',') + 1));
		else if (cmd.find("PRINT") != string::npos)
			print(out);
	}
}

void CommandManager::decode(string s) {
	q.push(s);
}

void CommandManager::replace(char c1, char c2) {
	if (q.empty()) 
		return;

	string s = q.getFront();
	q.pop();
	std::replace(s.begin(), s.end(), c1, c2);
	q.push(s);
}

void CommandManager::add(char c1, char c2) {
	if (q.empty())
		return;
	
	string s = q.getFront();
	q.pop();
  string temp;

  for(int i = 0; i < s.length(); i++){
    if(s[i] == c1){
      temp += s[i]; temp += c2;
    }
    else 
      temp += s[i];
  }
  
	q.push(temp);
}

void CommandManager::remove(char c) {
	if (q.empty()) 
		return;
	
	string s = q.getFront();
	q.pop();
	s.erase(std::remove(s.begin(), s.end(), c), s.end());
	q.push(s);
}

void CommandManager::swap(char c1, char c2) {
	if (q.empty()) 
		return;
	
	string s = q.getFront();
	q.pop();
	
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == c1)
			s[i] = c2;
		else if (s[i] == c2)
			s[i] = c1;	
	}
	q.push(s);
}

void CommandManager::print(ofstream& out) {
	if (q.empty()) 
		return;

	out << q.getFront() << endl;
	q.pop();
}