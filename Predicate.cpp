#include <iostream>
#include <string>
using namespace std;

#include "Predicate.h"

Predicate::Predicate(string ident) {
  this->ident = ident;
}

string Predicate::ToString() {
  string output = "";
  output += this->ident;
  output += "(";
  for (unsigned int i = 0; i < this->paramlist.size(); i++) {
    output += paramlist.at(i)->ToString();
    if (i != paramlist.size() - 1) {
      output += ",";
    }
  }
  output += ")";
  return output;
}
