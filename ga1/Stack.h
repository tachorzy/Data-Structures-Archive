struct letter { 
  char l;
  letter* next;
};

class Stack { 
  private:
    letter* top;
  public:
    Stack() { top = nullptr; }
    ~Stack(){}
    letter* getTop(){return top;}
    bool isempty(){return (top == nullptr);}
    int getSize(){
      letter* cu = new letter();
      cu = top;
      int c = 0;
      while(cu->next != nullptr) {
        cu = cu->next;
        c++; 
      }
      return c;
    }

    void push(char c) { 
      letter* temp = new letter();
      temp->l = c;
      temp->next = top;
      top = temp;
    }
    void pop() { //deletes
      if(isempty()) {
        cout << "the stack is currently empty." << endl;
        return;
      }
        letter* temp = top;
        top = top->next;
        delete temp;
        return;
    }  
    char peek(){ //returns the top value
      if(!isempty()) {
        return top->l;
      }
      else
        return 'z';
    }
    void print() { 
      letter* cu = top;
      while (cu != nullptr){ 
        cout << cu->l << " ";
        cu = cu->next;
      }
    }

};