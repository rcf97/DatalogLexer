#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "Rule.h"

Rule::Rule(Predicate* head) {
  this->head = head;
}

void Rule::addPred(Predicate* add) {
  this->predlist.push_back(add);
}

string Rule::ToString() {
  string output = "";
  output += this->head->ToString();
  output += " :- ";
  for (unsigned int i = 0; i < this->predlist.size(); i++) {
    output += this->predlist.at(i)->ToString();
    if (i != this->predlist.size() - 1) {
      output += ",";
    }
    else {
      output += ".";
    }
  }
  return output;
}
