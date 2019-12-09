#include <map>
#include <vector>
#include <string>
#include <set>
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
    this->graph[i - 1].addIdent(i - 1);
    Node revNewNode;
    this->revGraph[i - 1] = revNewNode;
    this->revGraph[i - 1].addIdent(i - 1);
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
  this->count = 1;
  this->postorder.clear();
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

vector<set<int>> Graph::SCC() {
  this->RevDFS();
  this->count = 1;
  return this->DFS();
}

string Graph::RevToString() {
  string output = "Reverse Dependency Graph\n";
  map<int, Node>::iterator it;
  set<int>::iterator sit;
  for (it = this->revGraph.begin(); it != this->revGraph.end(); it++) {
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

vector<set<int>> Graph::DFS() {
  unsigned int i;
  vector<int> revPO;
  vector<set<int>> sccs;
  set<int> temp;
  for (i = 0; i < this->postorder.size(); i++) {
    revPO.insert(revPO.begin(), this->postorder.at(i));
  }
  for (i = 0; i < revPO.size(); i++) {
    if (!this->graph[revPO.at(i)].visited) {
      temp.clear();
      sccs.push_back(temp);
      this->Visit(&this->graph[revPO.at(i)], &sccs.back());
    }
  }
  return sccs;
}

void Graph::Visit(Node* root, set<int>* scc) {
  root->visited = true;
  scc->insert(root->ident);
  set<int>::iterator it;
  for (it = root->successors.begin(); it != root->successors.end(); it++) {
    if (!this->graph[*it].visited) {
      this->Visit(&this->graph[*it], scc);
    }
  }
  root->postOrder = this->count;
  this->count++;
}

void Graph::RevDFS() {
  map<int, Node>::iterator it;
  for (it = this->revGraph.begin(); it != revGraph.end(); it++) {
    if (!it->second.visited) {
      this->Visit(&it->second);
    }
  }
}

void Graph::Visit(Node* root) {
  root->visited = true;
  set<int>::iterator it;
  for (it = root->successors.begin(); it != root->successors.end(); it++) {
    if (!this->revGraph[*it].visited) {
      this->Visit(&this->revGraph[*it]);
    }
  }
  root->postOrder = this->count;
  this->postorder.push_back(root->getIdent());
  this->count++;
}

bool Graph::Depends(int i) {
  bool flag = false;
  set<int>::iterator it;
  for (it = this->graph[i].successors.begin(); it != this->graph[i].successors.end(); it++) {
    if (*it == i) {
      flag = true;
    }
  }
  return flag;
}

string Graph::SCCToString(vector<set<int>> sccs) {
  string output = "List of Strongly Connected Components\n";
  set<int>::iterator it;
  for (unsigned int i = 0; i < sccs.size(); i++) {
    output += "SCC";
    output += to_string(i + 1);
    output += ": ";
    for (it = sccs.at(i).begin(); it != sccs.at(i).end(); it++) {
      output += "R";
      output += to_string(*it);
      output += ",";
    }
    if (output.back() == ',') {
      output.pop_back();
    }
    output += "\n";
  }
  return output;
}
