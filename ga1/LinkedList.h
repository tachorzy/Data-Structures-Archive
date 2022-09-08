struct Node {
  string data;
  Node* next;
  Node* prev;
};

class LinkedList {
  private: 
    Node* head;
    Node* tail;
  public: 
    LinkedList(){ head = tail = nullptr;}
    ~LinkedList(){}
    bool isempty(){ return (head == nullptr);}
    Node* getHead() { return head;}
    Node* getTail() { return tail; }
    //all of these below are recursive:
    int getLength(Node* headref, int count=0) {
      if(headref == nullptr)
        return count;
      return getLength(headref->next, ++count);
    }
    void addAtEnd(Node* headref, string data) {
      Node* newNode = new Node();
      newNode->data = data;
      if(isempty()){ //edge case
        head = headref = newNode;
        return;
      }
      if(headref->next == nullptr){ //base case.
        headref->next = newNode;
        newNode->prev = headref;
        tail = newNode;
        return;
      }
      return addAtEnd(headref->next, data);
    }
    
    bool delAtVal(Node* headref, string key) {
      if(isempty() || headref == nullptr) //edge case
        return false;
      if(headref->data != key)
        return delAtVal(headref->next, key);
      else //base cases
        if(head == headref) {
          head = headref->next;
          head->prev = nullptr;
          delete headref;
        }
        else if(tail == headref){
          tail = headref->prev;
          tail->next = nullptr;
          delete headref;
        }
        else {
          headref->prev->next = headref->next;
          headref->next->prev = headref->prev;
          delete headref;
        }
      return true;
    }
    
    void print(Node* headref) {
      if(isempty() || headref == nullptr)
        return;
      cout << headref->data << endl;
      return print(headref->next);
    }
    bool search(Node* headref, string key) {
      if(isempty()){
        return false;
      }
      if(headref == nullptr)
        return false;
      if(headref->data == key)
        return true;
      return search(headref->next, key);
    }
    
    bool isJimmyCool()
    {
      return true; //>:D
    }
};