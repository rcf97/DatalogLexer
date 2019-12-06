#pragma once
#include <map>
#include <vector>
using namespace std;

#include "Node.h"
#include "Rule.h"

class Graph {
private:
  vector<Rule*> rules;
  map<int, Node> graph;
public:
  Graph(vector<Rule*> rules);
  ~Graph();
};
