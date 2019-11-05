#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <string>
using namespace std;

#include "Relation.h"
#include "Scheme.h"
#include "Predicate.h"
#include "Tuple.h"

Relation::Relation(Scheme* schemePtr) {
  this->name = schemePtr->getName();
  this->relScheme = schemePtr;
}

void Relation::AddFact(Predicate* predPtr) {
  vector<string> elements;
  unsigned int i;
  for (i = 0; predPtr->paramlist.size(); i++) {
    elements.push_back(predPtr->paramlist.at(i)->ToString());
  }
  Tuple* tplPtr;
  tplPtr = new Tuple(elements);
  tuples.insert(tplPtr);
}

string Relation::ToString() {
  string output = "";
  output += this->name;
  output += "\n";
  set<Tuple*>::iterator it;
  for (it = tuples.begin(); it != tuples.end(); it++) {
    output += "\t";
    Tuple* tplPtr = *it;
    output += tplPtr->ToString();
    output += "\n";
  }
  return output;
}
