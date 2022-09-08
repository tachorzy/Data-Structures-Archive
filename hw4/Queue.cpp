#include "Queue.h"
#include <iostream>

using namespace std;

int Queue::getSize() {
  int c = 0;
  qNode* cu = front;
  while(cu->next != nullptr) {
    cu = cu->next;
    c++;
  }
  return c;
}

void Queue::push(string data) {
  qNode* temp = new qNode();
  temp->data = data;
  temp->next = nullptr;

  if(empty()) {
    front = rear = temp;
    return;
  }
  
  rear->next = temp;
  rear = temp;
}

void Queue::pop() {
  if(front == nullptr)
    return;

  qNode* temp = new qNode();
  temp = front;
  front = front->next;

  if(front == nullptr)
    rear = nullptr;

  delete temp;
}

void Queue::print(qNode* headref) {
  if(headref == nullptr)
    return;
  cout << headref->data << " ";
  print(headref->next);
}
