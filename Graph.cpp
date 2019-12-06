#include <map>
#include <vector>
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
  }
  for (i = 0; i < this->rules.size(); i++) {
    for (j = 0; j < this->rules.size(); j++) {
      for (k = 0; k < this->rules.at(j)->predlist.size(); k++) {
        if (this->rules.at(i)->head->ident ==
      }
    }
  }
}
