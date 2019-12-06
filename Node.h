#pragma once
#include <set>
using namespace std;

class Node {
public:
  set<ints> successors;
  bool visited = false;
  int postOrder;
  Node() {}
  ~Node() {}
};
