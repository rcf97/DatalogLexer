#include <map>
#include <vector>
#include <string>
#include <set>
#include <stack>
using namespace std;

#include "Graph.h"
#include "Node.h"
#include "Rule.h"

Graph::Graph(vector<Rule*> rules) {
  unsigned int i;
  unsigned int j;
  unsigned int k;
  for (i = 1; i < rules.size(); i++) {
    this->rules.push_back(rules.at(i));
    Node newNode;
    this->graph[i - 1] = newNode;
    Node revNewNode;
    this->revGraph[i - 1] = revNewNode;
  }
  for (i = 0; i < this->rules.size(); i++) {
    for (k = 0; k < this->rules.at(i)->predlist.size(); k++) {
      for (j = 0; j < this->rules.size(); j++) {
        if (this->rules.at(j)->head->ident == this->rules.at(i)->predlist.at(k)->ident) {
          this->graph[i].successors.insert(j);
          this->revGraph[j].successors.insert(i);
        }
      }
    }
  }

}

Graph::~Graph() {

}

string Graph::ToString() {
  string output = "Dependency Graph\n";
  map<int, Node>::iterator it;
  set<int>::iterator sit;
  for (it = this->graph.begin(); it != this->graph.end(); it++) {
    output += "R";
    output += to_string(it->first);
    output += ":";
    for (sit = it->second.successors.begin(); sit != it->second.successors.end(); sit++) {
      output += "R";
      output += to_string(*sit);
      output += ",";
    }
    if (output.back() == ',') {
      output.pop_back();
    }
    output += "\n";
  }
  return output;
}

void Graph::DFS() {
  stack<Node*> myStack;
  
}
