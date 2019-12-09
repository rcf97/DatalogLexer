#pragma once
#include <map>
#include <vector>
#include <string>
#include <set>
using namespace std;

#include "Node.h"
#include "Rule.h"

class Graph {
private:
  vector<Rule*> rules;
  map<int, Node> graph;
  map<int, Node> revGraph;
  int count;
  vector<int> postorder;
public:
  Graph(vector<Rule*> rules);
  ~Graph();
  string ToString();
  string RevToString();
  vector<set<int>> SCC();
  vector<set<int>> DFS();
  void RevDFS();
  void Visit(Node* root);
  void Visit(Node* root, set<int>* scc);
  bool Depends(int i);
  string SCCToString(vector<set<int>> sccs);
};
