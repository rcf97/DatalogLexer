#pragma once
#include <map>
using namespace std;

#include "Node.h"
#include "Rules.h"

class Graph {
private:
  vector<Rule*> rules;
  map<int, Node> graph;
public:
  Graph();
  ~Graph();
};
