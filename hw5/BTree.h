#include <iostream>
#include <algorithm>

using namespace std;
struct BTreeNode {
  int* keys;
  int numOfKeys;
  BTreeNode** childPtrs;
  bool isleaf;
  BTreeNode* parent;
  int deg;
  BTreeNode(int degree, BTreeNode* p, bool l){
    keys = new int[degree];
    parent = p;
    isleaf = l;
    childPtrs = new BTreeNode*[degree+1];
    std::fill(childPtrs, childPtrs+degree+1, nullptr);
    deg = degree;
  }
  void printLevel(BTreeNode* cu, int lvl, int c, int h, ofstream& of);
  bool searchChildren(BTreeNode* n, BTreeNode* keyNode);
};

class BTree{
  private:
    int d;
  public:
    BTreeNode* root;
    BTree(int _d){ root = nullptr; d = _d; }
    bool isempty(){ return (root == nullptr); }
    BTreeNode* getRoot(){ return root; }

    void insert(BTreeNode* n, int key);
    void insertNonFull(BTreeNode* n, int key);
    void split(BTreeNode* fullNode);
    int height(BTreeNode*);
    void levelOrder(int, ofstream&);
};

  int BTree::height(BTreeNode* cu) {
    if(cu == nullptr)
      return 0;
    return 1 + height(cu->childPtrs[0]);
  }

  void BTree::levelOrder(int level, ofstream& of){
    if(isempty() || level > height(root))
      of << "Empty";
    else if(level == 1)
      for(int i = 0; i < root->numOfKeys; i++)
        of << root->keys[i] << " ";
    else
      root->printLevel(root, level, 1, height(root), of);
    of << endl;
  }

void BTreeNode::printLevel(BTreeNode* cu, int level, int c, int h, ofstream& of){
  if(cu == nullptr || c > h) {
    return;
  }
  if (level == c){
    for(int i = 0; i < cu->numOfKeys; i++){
      of << cu->keys[i] << " ";
    }
  }
  else if(!cu->isleaf){
    ++c;
    for(int i = 0; i <= deg; i++)
      if(cu->childPtrs[i] != nullptr)
        printLevel(cu->childPtrs[i], level, c, h, of);
  }
}

bool BTreeNode::searchChildren(BTreeNode* n, BTreeNode* keyNode){
  if(n == nullptr)
    return false;
  if(n == keyNode)
    return true;
  else
    for(int i = 0; i < deg; i++)
      searchChildren(n->childPtrs[i], keyNode);
}

void BTree::insert(BTreeNode* n, int key){
  if(isempty()){
    root = new BTreeNode(d, nullptr, true);
    root->keys[0] = key;
    root->numOfKeys = 1;
    return;
  }
  if(n->isleaf)
    return insertNonFull(n, key);

  int i = 0;
  while(i < n->numOfKeys && key > n->keys[i])
    i++;
  insert(n->childPtrs[i], key);
}

void BTree::insertNonFull(BTreeNode* n, int key){
  n->keys[n->numOfKeys] = key;
  n->numOfKeys++;
  sort(n->keys, n->keys+n->numOfKeys);
  for(int i = 0; i < n->numOfKeys; i++)
    cout << n->keys[i] << " ";
  cout << endl;

  if(n->numOfKeys >= d)
    split(n);
}

//BIG SHOUT OUT TO Johnny Le, his cougartube video inspired this code.
//Also some of this was inspired by Mayowa Awojuyigbe's fantastic video on hw5: https://www.youtube.com/watch?v=kjBI0rimo-w
void BTree::split(BTreeNode* fullNode){ 
  int mid, newSize;
  BTreeNode* right = new BTreeNode(d, fullNode->parent, fullNode->isleaf);
  
  int oldSize = fullNode->numOfKeys;

  if(d % 2 == 0)
    mid = newSize = d / 2 -1;
  else 
    mid = newSize = d / 2;

  int carry = fullNode->keys[mid];
  int j = 0;
  for(int i = newSize+1; i < oldSize; i++){
    right->keys[j] = fullNode->keys[i];
    right->numOfKeys++;
    fullNode->numOfKeys--;
    j++;
  }
  fullNode->numOfKeys--;

  if(!fullNode->isleaf){
    int j = 0;
    for(int i = mid+1; i <= d; i++){
      right->childPtrs[j] = fullNode->childPtrs[i];
      right->childPtrs[j]->parent = right;
      fullNode->childPtrs[i] = 0;
      j++;
    }
    right->isleaf = fullNode->isleaf;
  }
  
  BTreeNode* p = fullNode->parent;
  
  if(p == nullptr){ //if fullNode is the root.
    BTreeNode* newRoot = new BTreeNode(d, nullptr, false);
    fullNode->parent = right->parent = newRoot;
    int i = 0;
    while(newRoot->childPtrs[i] && i <= d)
      i++; 
    newRoot->childPtrs[i] = fullNode;
    newRoot->childPtrs[i+1] = right;
    newRoot->keys[newRoot->numOfKeys] = carry;
    newRoot->numOfKeys++;
    root = newRoot;

    return;
  }
  
  int hold = d-1;
  while(p->childPtrs[hold] != fullNode){
    p->childPtrs[hold+1] = p->childPtrs[hold];
    hold--;
  }
  p->childPtrs[hold+1] = right;
  insertNonFull(p, carry);
}