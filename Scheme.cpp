#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "Scheme.h"
#include "Predicate.h"
#include "Parameter.h"

Scheme::Scheme(Predicate* predPtr) {
  this->name = predPtr->getIdent();
  unsigned int i;
  for (i = 0; i < predPtr->paramlist.size(); i++) {
    this->attributes.push_back(predPtr->paramlist.at(i)->ToString());
  }
}

Scheme::Scheme(string name, vector<string> att) {
  this->name = name;
  this->attributes = att;
}

Scheme::~Scheme() {

}

string Scheme::getName() {
  return this->name;
}

string Scheme::ToString() {
  string output = "";
  output += this->name;
  output += "(";
  for (unsigned int i = 0; i < this->attributes.size(); i++) {
    output += this->attributes.at(i);
    if (i != this->attributes.size() - 1) {
      output += ",";
    }
  }
  output += ")";
  output += "\n";
  return output;
}
