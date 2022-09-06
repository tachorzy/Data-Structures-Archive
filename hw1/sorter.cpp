#include <iostream>m
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;

vector<string> removeWhitespace(string f) {
	ifstream input_file;
	input_file.open(f);
	string line;

	vector<string> data;

	while (getline(input_file, line)) {
		line.erase(remove(line.begin(), line.end(), ' '), line.end()); //common method to remove whitespace; source: stackoverflow.
		data.push_back(line);
	}

	input_file.close();
	return data;
}

vector<string> dataValidifier(vector<string> in) {
	vector<string> valid_data;

	for (int i = 0; i < in.size(); i++) {
		if (in[i].find("genre") == string::npos || in[i].find("title") == string::npos || in[i].find("author") == string::npos || in[i].find("year") == string::npos) //checks for missing data
			continue;
		else if (in[i].find("genre") != 1 || in[i].find("title") > in[i].find("author") || in[i].find("year") < in[i].find("author")) //checks if they are in order
			continue;
		else
			valid_data.push_back(in[i]);
	}

	return valid_data;
}

struct criteria { //declaring a struct for our cmd data 
	vector<string> genres;
	vector<string> titles;
	vector<string> authors;
	vector<string> years;

	int genresSize = 0, titlesSize = 0, authorsSize = 0, yearsSize = 0, totalSize = 0;
};

struct book { //struct for book data
	string genre = "";
	string title = "";
	string author = "";
	string year = "";
};

struct criteria getCommandData(string cmd) {
	ifstream cmd_file;
	cmd_file.open(cmd);
	string line;

	criteria c;

	while (getline(cmd_file, line)) {
		if (line.find("genre") != string::npos) {
			c.genres.push_back(line);
			c.titles.push_back(""), c.authors.push_back(""), c.years.push_back("");
			c.totalSize++, c.genresSize++;
		}
		else if (line.find("title") != string::npos) {
			c.titles.push_back(line);
			c.genres.push_back(""), c.authors.push_back(""), c.years.push_back("");
			c.totalSize++, c.titlesSize++;
		}
		else if (line.find("author") != string::npos) {
			c.authors.push_back(line);
			c.genres.push_back(""), c.titles.push_back(""), c.years.push_back("");
			c.totalSize++, c.authorsSize++;
		}
		else if (line.find("year") != string::npos) {
			c.years.push_back(line);
			c.genres.push_back(""), c.titles.push_back(""), c.authors.push_back("");
			c.totalSize++, c.yearsSize++;
		}
	}

	return c;
}

vector<book> getBooks(vector<string> data) {
	vector<book> books;

	for (int i = 0; i < data.size(); i++) {
		book temp;
		temp.genre = data[i].substr(data[i].find("genre"), (data[i].find("title") - data[i].find("genre")) - 1);
		temp.title = data[i].substr(data[i].find("title"), (data[i].find("author") - data[i].find("title")) - 1);
		temp.author = data[i].substr(data[i].find("author"), (data[i].find("year") - data[i].find("author")) - 1);
		temp.year = data[i].substr(data[i].find("year"), (data[i].find('}') - data[i].find("year")));

		books.push_back(temp);
	}

	return books;
}

void bookSearcher(criteria c, vector<string> data, vector<book> books, string out) {
	ofstream output_file;
	output_file.open(out);

	if (c.totalSize > 0) { //test cases 2 and 3
		string genres = "", titles = "", authors = "", years = "";

		for (int i = 0; i < c.totalSize; i++) {
			genres += c.genres[i];
			titles += c.titles[i];
			authors += c.authors[i];
			years += c.years[i];
		}

		for (int i = 0; i < data.size(); i++) {
			if ((genres.find(books[i].genre) != string::npos || c.genresSize == 0) && (titles.find(books[i].title) != string::npos || c.titlesSize == 0)
				&& (authors.find(books[i].author) != string::npos || c.authorsSize == 0) && (years.find(books[i].year) != string::npos || c.yearsSize == 0))
				output_file << data[i] << endl;
		}
	}
	else if (c.totalSize == 0) //test case 1 
		for (int i = 0; i < data.size(); i++)
			output_file << data[i] << endl;
}


int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string command = am.get("command");

	vector<string> data = dataValidifier(removeWhitespace(input));

	bookSearcher(getCommandData(command), data, getBooks(data), output);
	return 0;
}