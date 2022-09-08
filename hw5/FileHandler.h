#include <string>
#include <fstream>
#include "BTree.h"

using namespace std;

class FileManager{
  private:
    BTree t;
  public:
    int getDegree(ifstream& cmd){
      int deg;
      cmd >> deg;
      return deg;
    }
    void inputHandler(ifstream& in, int deg){
      t = new BTree(deg);
      int n;
      while(in >> n))
        t->insert(t->root, n);
    }
    void commandHandler(ifstream& cmd){
      string line;
      while(cmd >> line){
        if(line.find("Level") != string::npos){
          int lvl = stoi(line.find_first_of("1234567890"));
          t->levelOrder(lvl);
        }
      }
    }



};