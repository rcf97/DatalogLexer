#pragma once
#include <map>
#include <vector>
#include <string>
using namespace std;

#include "Node.h"
#include "Rule.h"

class Graph {
private:
  vector<Rule*> rules;
  map<int, Node> graph;
  map<int, Node> revGraph;
public:
  Graph(vector<Rule*> rules);
  ~Graph();
  string ToString();
};
