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
  for (i = 0; predPtr->paramlist.size(); i++) {
    this->attributes.push_back(predPtr->paramlist.at(i)->ToString());
  }
}

string Scheme::getName() {
  return this->name;
}
