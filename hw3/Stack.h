#pragma once
#include <string>
using namespace std;

struct sNode {
	string op;
	sNode* next;
};

class Stack {
	private:
		sNode* top;
	public:
		Stack() { top = nullptr; }
		inline bool isempty() { return (top == nullptr); }
		int getSize();
		void push(string);
		void pop();
		string peek();
		void print(sNode*);
};
