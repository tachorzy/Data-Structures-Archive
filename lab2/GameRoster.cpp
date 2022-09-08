#include "GameRoster.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>

int GameRoster::getSize(player* head) { 
	int count = 0;
	player* current = new player();
	current = head;
	while (current != nullptr) {
		count++;
		current = current->next;
	}
	return count;
}

void GameRoster::dataManager(ifstream &inFile, ofstream &outFile) { 
	string line;
	int numOfCommas = 0;

	if (inFile.peek() == ifstream::traits_type::eof()) { outFile << "No valid data in input" << endl; return; }

	while (getline(inFile, line)) {
		numOfCommas = 0;
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == ',')
				numOfCommas++;
		}
		if (numOfCommas > 1 || numOfCommas == 0){
			continue;
		}
		else { 
			int score = getScore(removeWhitespace(line));
			string username = getName(removeWhitespace(line));

			if (score != -1 && username != "")
				addAtBeg(score, username);
			else
				continue;
		}
	}
}

string GameRoster::removeWhitespace(string line) {
	line.erase(remove(line.begin(), line.end(), ' '), line.end());

	//removing escape characters
	if(line.find("\n") != string::npos)
		line.erase(remove(line.begin(), line.end(), '\n'), line.end());
	else if(line.find("\r") != string::npos)
		line.erase(remove(line.begin(), line.end(), '\r'), line.end());
	else if(line.find("\t") != string::npos)
		line.erase(remove(line.begin(), line.end(), '\t'), line.end());

	return line;
}

int GameRoster::getScore(string line) { 
	int score;
	string s = line.substr(line.find(',')+1);
	try {
		score = stoi(s);
	}
	catch (...	) {return -1; }

	return score;
}

string GameRoster::getName(string line) {
	stringstream ss(line);
	string s ;
	getline(ss, s, ',');
	if (s.empty()) {
		return "";
	}
	return s;
}


void GameRoster::addAtBeg(int score, string username) {
	player* current = new player();
	player* temp = new player();
	temp->name = username;
	temp->score = score;
	temp->next = nullptr;

	if (isempty()) { head = temp; }
	else {
		temp->next = head;
		head = temp;
	}
} 

void GameRoster::selectionSort() {
	if (head == nullptr)
		return;

	player* current = head;
	while (current->next != nullptr) {
		player* next = current->next;
		player* max = current;
		while (next != nullptr) {
			if (next->score > max->score)
				max = next;
			next = next->next; 
		}
		int tempScore = current->score;
		string tempName = current->name;
		current->score = max->score;
		current->name = max->name;
		max->score = tempScore;
		max->name = tempName;

		current = current->next;
	}
}

void GameRoster::outputLinkedList(player* p, ofstream& outputFile) {

	if (isempty()) {
		outputFile << "No valid data in input" << endl;
		return;
	}

	if (p == 0)
		return;
	else
		outputFile << p->name << "," << p->score << endl;
	outputLinkedList(p->next, outputFile);
}

void GameRoster::print(player* p) {
	if (p == 0)
		return;
	else
		cout << p->name << "," << p->score << endl;
	print(p->next);
}
