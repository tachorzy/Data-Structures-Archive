/*
   Zachary Peyton
   Tariq Achor Zyad
   Jimmy Vuong
   Tan Huynh
*/
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include "ArgumentManager.h"
#include <queue> 
#include "LinkedList.h"
#include "Stack.h"
using namespace std;

void PEMDAS(Stack &stk)
{
  queue<char> qq;
  while(stk.peek()!='(')
  {
    qq.push(stk.peek());
    stk.pop();
  }
  stk.pop();
  while(!qq.empty())
  {
    stk.push(qq.front());
    qq.pop();
  }
}
void reverse(Stack &stk, string &ret){
  queue<char> qq;
  while(!stk.isempty())
  {
    qq.push(stk.peek());
    stk.pop();
  }
  while(!qq.empty()){
    stk.push(qq.front());
    qq.pop();
  }
  int c = 0;
  while(!stk.isempty()){
    ret+=stk.peek();
    stk.pop();
    c++;
  }
}
string decodeID(string s)
{
  string ret="";
  Stack succ;
  int c = 0;
  while(c!=s.size())
  {
    if(s[c]!=')')
      succ.push(s[c]);
    else{
      PEMDAS(succ);
    }
    c++;
  }
  reverse(succ, ret);
  return ret;
}

void addInputToQueues(ifstream &inputFile, queue<string> &queueBar1, queue<string> &queueBar2)
{
string s = "";
bool addToBar1 = false; //if addToBar1 is true, inputs would be added to queueBar1
  while(!inputFile.eof())
  {
    getline(inputFile, s);
    if(s.find("Bar1") != -1)
    {
      addToBar1 = true;
      continue;
    }
    else if (s.find("Bar2") != -1)
    {
      addToBar1 = false;
      continue;
    }
    
    if(addToBar1 && s != "")
      queueBar1.push(s);
    else if(!addToBar1 && s != "")
      queueBar2.push(s);
  }
}
void printQueues(queue<string> queueBar1)
{
  queue<string> q = queueBar1;
    string s = "";
  //cout << q.size() << endl;
  while(!q.empty())
  {
    s += q.front() + "\n";
    q.pop();
  }
  cout << s << endl;
  
}
void populateLinkedListWQueue(LinkedList &tempLLBar, queue<string> queueBar)
{
  queue<string> q = queueBar;
  while(!q.empty())
  {
    string s = q.front();
    q.pop();
    //cout << s << endl;
    
    tempLLBar.addAtEnd(tempLLBar.getHead(), s);
  }
}

//returns a LL of guilty ID by comparing queueBar1 and queueBar2
LinkedList getGuiltyLL(queue<string> queueBar1, queue<string> queueBar2)
{
  LinkedList tempLLBar1;
  LinkedList tempLLBar2;
  LinkedList guiltyLL;

  string tmpid1, tmpid2;
  int decodedid1, decodedid2;

  populateLinkedListWQueue(tempLLBar1, queueBar1);
  populateLinkedListWQueue(tempLLBar2, queueBar2);

  Node* tempLLBar1headRef = tempLLBar1.getHead();
  Node* tempLLBar2headRef = tempLLBar2.getHead(); 

  while(tempLLBar1headRef != nullptr)
  {
    tmpid1 = tempLLBar1headRef->data;
    decodedid1 = stol(tmpid1);
    tempLLBar2headRef = tempLLBar2.getHead();
    while(tempLLBar2headRef != nullptr)
    {
      tmpid2 = tempLLBar2headRef->data;
      decodedid2 = stol(tmpid2);
      if(tmpid1 == tmpid2)
      {
        guiltyLL.addAtEnd(guiltyLL.getHead(), tempLLBar1headRef->data);
        break;
      }
      else
      {
        tempLLBar2headRef = tempLLBar2headRef->next;
      }
    }
    tempLLBar1headRef = tempLLBar1headRef->next;
  }


 return guiltyLL;
  //nested loops
  //outer loop gets element of bar1
  //inner loop compares bar1 element with all elements of bar2
    //if elements are the same then put them into a guilty container
}

LinkedList getInnocent(queue<string> queueBar1, queue<string> queueBar2, LinkedList guiltyIDs)
{
  LinkedList innocence;
  queue<string> tempQBar1 = queueBar1;
  queue<string> tempQBar2 = queueBar2;

  while(!tempQBar1.empty())
  {
    string s = tempQBar1.front();
    tempQBar1.pop();

    if(!guiltyIDs.search(guiltyIDs.getHead(), s))
    {
      innocence.addAtEnd(innocence.getHead(), s);
    }
  }

  while(!tempQBar2.empty())
  {
    string s = tempQBar2.front();
    tempQBar2.pop();

    if(!guiltyIDs.search(guiltyIDs.getHead(), s))
    {
      innocence.addAtEnd(innocence.getHead(), s);
    }
  }

  return innocence;

  //2 loops
  //first loop loops through bar1 and check if ID from bar1 is guilty from guiltyIDs if not equal then add it to innocentID
  //second loop loops through bar2 and check if ID from bar2 is guilty from guiltyIDs if not equal then add it to innocentID
}

void decoding(queue<string> &q1, queue<string> &q2) 
{
  queue<string> tmp1, tmp2;

  while(!q1.empty())
  {
    tmp1.push(decodeID(q1.front()));
    q1.pop();
  }

  while(!q2.empty())
  {
    tmp2.push(decodeID(q2.front()));
    q2.pop();
  }

  while(!tmp1.empty())
  {
    q1.push(tmp1.front());
    tmp1.pop();
  }

  while(!tmp2.empty())
  {
    q2.push(tmp2.front());
    tmp2.pop();
  }
  
}

//Mergesort for the LinkedList
void split(Node* headref, Node** list1, Node** list2){
  Node* ptr1 = headref, *ptr2 = headref->next;
  //by the end ptr1 will be mid, and ptr2 will be the tail.
  while(ptr2->next != nullptr && ptr2->next->next != nullptr){ 
    ptr1 = ptr1->next;
    ptr2 = ptr2->next->next;
  }
  *list1 = headref;
  *list2 = ptr1->next;
  ptr1->next = nullptr;
}

Node* merge(Node* list1, Node* list2){
  Node* temp;
  if(list1 == nullptr) //edgecase, same as left <= mid.
    return list2;
  if(list2 == nullptr) //edgecase, same as right <= high
    return list1;

  if(stol(list1->data) <= stol(list2->data)){ //if the left is less than the right
    temp = list1;
    temp->next = merge(temp->next, list2); // same as temp[i++] = a[left++]
  }
  else {
    temp = list2;
    temp->next = merge(list1, temp->next); //same as temp[i++] = a[right++]
  }
  return temp; //instead of deleting we're returning a new list.
}

void mergesort(Node** h){
  Node* headref = *h;
  Node* list1, *list2;
  if(headref == nullptr || headref->next == nullptr)
    return;
  split(headref, &list1, &list2); //(1) Divide
  mergesort(&list1);//(2) Recur
  mergesort(&list2);
  *h = merge(list1, list2); //(3) Conquer/Merge
}

//output function:
void output(Node* headref, ofstream& out) {
  if(headref == nullptr) //base case
    return;
  if(headref->next == nullptr) {//edgecase, no extra line in file.
    out << headref->data;
    return;
  }
  out << headref->data << endl;
  return output(headref->next, out);
}


int main(int argc, char* argv[])
{
//argmanag
  ArgumentManager am(argc, argv);
  string infilename = am.get("input");
  string outfilename = am.get("output");
//file streams
  ifstream inputFile(infilename);
  ofstream outputFile(outfilename);
  
  queue<string> queueBar1;
  queue<string> queueBar2;
  addInputToQueues(inputFile, queueBar1, queueBar2);
  cout << "Printing Queues" << endl;
  printQueues(queueBar1);
  printQueues(queueBar2);  
  //string somethingId = decodeID("(4(23)1)(13(22)123)12");
  //cout << somethingId << endl;

   decoding(queueBar1, queueBar2);
  cout << "Decoded IDs: " << endl;
  printQueues(queueBar1);
  printQueues(queueBar2);

  //need to make queueBar1 and queueBar2 have their decoded IDs

  cout << "guilty\n"; 
  LinkedList guiltyIDs = getGuiltyLL(queueBar1, queueBar2);
  LinkedList innocentIDs = getInnocent(queueBar1, queueBar2, guiltyIDs);
  
  // = getInnocent(queueBar1, queueBar2, guiltyIDs);
  //those two functions *should* work
  //if guiltyID.getHead() == nullptr, there are no guiltyIDs
  

  //Guilty print testing
  //guiltyIDs.print(guiltyIDs.getHead());
  
  //Innocent print testing
  //cout << "\ninnocent\n";
  //innocentIDs.print(innocentIDs.getHead());

  //Jimmy Easter Egg
  //if(guiltyIDs.isJimmyCool())
  //  cout << "Tan smells" << endl; 
  
  //MergeSort down here
  Node* guiltyHead = guiltyIDs.getHead();
  Node* innoHead = innocentIDs.getHead();
  
  mergesort(&guiltyHead);
  mergesort(&innoHead);

  //output stuff, only outputs if head != null
  if(guiltyHead && innoHead){
    outputFile << "Guilty:" << endl;
    output(guiltyHead, outputFile);
    outputFile << "\nInnocent:" << endl;
    output(innoHead, outputFile);
  }
  else if(innoHead){
    outputFile << "Innocent:" << endl;
    output(innoHead, outputFile);
  }
  else if(guiltyHead){
    outputFile << "Guilty:" << endl;
    output(guiltyHead, outputFile);
  }
}
