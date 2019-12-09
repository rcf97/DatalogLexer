#pragma once
#include <set>
using namespace std;

class Node {
public:
  set<int> successors;
  bool visited = false;
  int postOrder;
  int ident;
  Node() {}
  ~Node() {}
  void addIdent(int i) {
    this->ident = i;
  }
  int getIdent() {
    return this->ident;
  }
};
