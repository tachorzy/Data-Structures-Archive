#include <string>

using namespace std;

struct qNode { 
  string data;
  qNode* next;
};

class Queue {
  private:
    qNode* front;
    qNode* rear;
  public:
    Queue() { front = nullptr, rear = nullptr; }
    string getFront() { return front->data; }
    int getSize();
    bool empty() { return front==nullptr;}
    void push(string data);
    void pop();
    void print(qNode* headref);
};