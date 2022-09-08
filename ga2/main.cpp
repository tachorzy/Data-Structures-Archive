#include <fstream>
#include <iostream>
#include <string>
#include "ArgumentManager.h"
#include <queue> 
#include <stack>
#include "LinkedList.h"
using namespace std;

bool isbalanced(string &exp){
  stack<char> st;
  char c;
  for(int i = 0; i < exp.length(); i++){
    if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[') {
      st.push(exp[i]);
      continue;
    }
    switch(exp[i]){
      case ')':
        c = st.top();
        st.pop();
        if(c != '(')
          return false;
        break;
      case '}':
        c = st.top();
        st.pop();
        if(c != '{')
          return false;
        break;
      case ']':
        c = st.top();
        st.pop();
        if(c != '[')
          return false;
        break;
    }
  }
  return (st.empty()); 
}

void distributeString(string &s)
{
  for(int k = 0; k < s.length()-1; k++)
  {
    int c = 0;
    if(s[k] == '+' && s[k+1] == '(')
    {
      s.erase(k+1, 1);
      
      for(int w = k+2; w < s.length(); w++)
      {
        if(s[w] == '('){
          c++;
          continue;
        }
        if(s[w] ==  ')' && c > 0)
        {
          c--;
          continue;
        }
        else if (s[w] == ')' && c == 0)
        {
           s.erase(w,1);
           break;

        }
      }
    }
    else if (s[k] == '-' && s[k+1] == '(')
      {
        int c = 0;
        s.erase(k+1, 1);
        for(int w = k+2; w < s.length(); w++)
        {
            if(s[w] == '+' && c == 0)
              s[w] = '-';
            else if(s[w] == '-' && c == 0)
              s[w] = '+';
            if(s[w] == '('){
              c++;
              continue;
            }
            if(s[w] == ')' && c != 0){
              c--;
              continue;
            }
            if(s[w] == ')' && c == 0){
              s.erase(w, 1);
            break;
            }
        }
    }
  }
}

void something(stack<int> &stk)
{
  stack<int> qq;
  while(stk.top()!='(')
  {
    qq.push(stk.top());
    stk.pop();
    
  }
  stk.pop();
  
  while(qq.size() != 1)
  {
    int total = 0;
    int num1 = qq.top();
    qq.pop();
    char op = qq.top();
    qq.pop();
    int num2 = qq.top();
    qq.pop();

    
    if(op == '+')
    {
      total += num1 + num2;
    }
    else if(op == '-')
    {
      total += num1 - num2;
    }
    qq.push(total);
  }
   stk.push(qq.top());
   qq.pop();
}

void reverse(stack<int> &stk, string &ret){
  queue<char> qq;
  while(!stk.empty())
  {
    qq.push(stk.top());
    stk.pop();
  }
  while(!qq.empty()){
    stk.push(qq.front());
    qq.pop();
  }
  int c = 0;
  while(!stk.empty()){
    ret+=stk.top();
    stk.pop();
    c++;
  }
}

int calculateString(string s)
{
  stack<int> reee;
  stack<int> qq;
  
  for(int k = 0; k<s.length(); k++)
    reee.push(s[k]);
  while(!reee.empty())
  {
    qq.push(reee.top());
    reee.pop();
  } //had to reverse cause operations were being done backwards

  int total = 0;

  while(qq.size() != 1)
  {
    total = 0;
    int num1 = qq.top();
    qq.pop();
    char op = qq.top();
    qq.pop();
    int num2 = qq.top();
    qq.pop();

    if(op == '+')
      total += num1 + num2;
    else if(op == '-')
      total += num1 - num2;
    qq.push(total);
  }
  return total;
}

void dealWithBackToBackOperators(string& s)
{
  for(int k = 0; k < s.length()-1; k++)
  {
    if(s[k] == '+' && s[k+1] == '+')
        s.erase(k, 1);
    else if (s[k] == '+' && s[k+1] == '-')
    {
      s.erase(k, 1);
    }

    else if (s[k] == '-' && s[k+1] == '+')
    {
      s.erase(k+1, 1);
    }
    else if (s[k] == '-' && s[k+1] == '-')
    {
      s[k+1] = '+';
      s.erase(k, 1);
    }
  }
}

//only call after knowing string s is balanced
string convertBracketsToPara(string s)
{
  for(int k = 0; k < s.length(); k++)
  {
    if(s[k]=='{' || s[k]=='[')
    {
      s[k] = '(';
    }
    else if(s[k]=='}' || s[k]==']')
      s[k] = ')';
    
  }
  return s;
}

string ret(string s)
{
  string ret="";
  stack<int> succ;
  int c = 0;
  while(c!=s.size())
  {
    if(s[c]!=')')
    {
      if(!isdigit(s[c]))
        succ.push(s[c]);
      else
        succ.push(s[c] - '0');
    }
    else{
      something(succ);
    }
    c++;
  }
  reverse(succ, ret);
  return ret;
}

//post: 
void getInputs(ifstream& inputFile, ofstream& outputFile, LinkedList& LL)
{
  int counter = 0;
 // LinkedList LL;
  while(!inputFile.eof())
  { 
    string s;
    getline(inputFile, s);
    if (s == "")
      continue;
    counter++;
    LL.addAtEnd(LL.getHead(), s, counter, isbalanced(s));
  }

}

void calculate(LinkedList temp, queue<int> &q){
  Node* tmp = temp.getHead(); 

  while(tmp != nullptr)
  {
    string s;
    s = tmp->exp;
    distributeString(s);
    dealWithBackToBackOperators(s);
    if(s[0] == '+')
    {
        s.erase(0, 1);
    }
    s = ret(s);
    q.push(calculateString(s));
    tmp = tmp->next;
  }
}

int evaluateExp(string exp){
  stack<char> operators;
  stack<int> operands;
  
  for(int i = 0; i < exp.length(); i++){
    if(isalnum(exp[i]))
      operands.push(int(exp[i]));
  
    else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '(') 
      operators.push(exp[i]);

    if(exp[i] == ')' || i == exp.length()-1){
      while(!operators.empty() && operators.top() != '('){
        int num2 = operands.top();
        operands.pop();

        int num1 = operands.top();
        operands.pop();

        char operation = operators.top();
        operators.pop();
        
        switch(operation){
          case '+':
            operands.push(num1 + num2);
            break;
          case '-':
            operands.push(num1 - num2);
            break;
        }
        if(operators.size() == 1) //pop parantheses '('
          operators.pop();
        else if (operators.size() > 1){

        }
      }
    }
  }
  return operands.top();
}

void calculate(stack<char>& operators, stack<int>& operands){
  int num2 = operands.top();
  operands.pop();

  int num1 = operands.top();
  operands.pop();

  char operation = operators.top();
  operators.pop();
  
  switch(operation){
    case '+':
      operands.push(num1 + num2);
      break;
    case '-':
      operands.push(num1 - num2);
      break;
  } 
}

bool isSimilar(LinkedList LL){
    Node* head = LL.getHead();
    Node* cu = LL.getHead()->next;

    int headEval = evaluateExp(head->exp);
    int cuEval;
    while(cu != nullptr)
    {
      cuEval = evaluateExp(cu->exp);
      if(headEval != cuEval)
        return false;
      continue;
    }
    return true;
}

void convertLLBrackets(LinkedList& LL)
{
  Node* cu = LL.getHead();

  while(cu != nullptr)
  {
    if(cu->balanced){
      string s = cu->exp;
      cu->exp = convertBracketsToPara(s);
    }
    cu = cu->next;
  }
}



int main(int argc, char* argv[])
{
  ArgumentManager am(argc, argv);
  string infilename = am.get("input");
  string outfilename = am.get("output");

  ifstream inputFile(infilename);
  ofstream outputFile(outfilename);

  queue<int> q;
  LinkedList LL;
  getInputs(inputFile, outputFile, LL);

  LinkedList LL2;

  if(LL.search(LL.getHead(), false))
    LL.printErrors(LL.getHead(), outputFile);
  else
    {
      convertLLBrackets(LL);
      calculate(LL,q);
      bool check = true;
      if(!q.empty())
      {
        int one = q.front();
        q.pop();
        while(!q.empty())
          {
          int two = q.front();
          q.pop();
          if(one != two)
          {
            check = false;
            break;
          }
      }
      if(check == true)
      {
        outputFile << "Yes" << endl;
      }
      else
        {
        outputFile << "No" << endl;
        }
      }
    }
  return 0;
} 