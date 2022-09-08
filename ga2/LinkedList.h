struct Node {
  string exp;
  int lineNum;
  bool balanced;
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
    void addAtEnd(Node* headref, string exp, int num, bool b) {
      Node* newNode = new Node();
      newNode->exp = exp;
      newNode->lineNum = num;
      newNode->balanced = b;
    
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
      return addAtEnd(headref->next, exp, num, b);
    }
    
    bool delAtVal(Node* headref, string key) {
      if(isempty() || headref == nullptr) //edge case
        return false;
      if(headref->exp != key)
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
      cout << headref->exp << " " <<  headref->lineNum << " " <<  headref->balanced << endl;
      return print(headref->next);
    }
    
    void printErrors(Node* headref, ofstream& outputFile) {
      if(isempty() || headref == nullptr)
        return;
      if(headref->balanced == false)
        outputFile << "Error at: " <<  headref->lineNum << endl;
      return printErrors(headref->next, outputFile);
    }



    bool search(Node* headref, bool key) {
      if(isempty()){
        return false;
      }
      if(headref == nullptr)
        return false;
      if(headref->balanced == key)
        return true;
      return search(headref->next, key);
    }
    /*
    //override of search function, this one will return the index of the node found.
    int search(Node* headref, bool key) {
      if(isempty()){
        return -1;
      }
      if(headref == nullptr)
        return -1;
      if(headref->balanced == key)
        return headref->lineNum;
      return search(headref->next, key);
    }*/
};