#include <iostream>
#include <map>
#include <string>
#include <iterator>
using namespace std;

#include "Database.h"
#include "Predicate.h"
#include "Relation.h"
#include "Scheme.h"

Database::Database() {

}

Database::~Database() {

}

void Database::AddScheme(Predicate* predPtr) {
  Scheme* schemePtr;
  schemePtr = new Scheme(predPtr);
  Relation* relPtr;
  relPtr = new Relation(schemePtr);
  this->data[schemePtr->getName()] = relPtr;
}

void Database::AddFact(Predicate* predPtr) {
  this->data[predPtr->getIdent()]->AddFact(predPtr);
}

void Database::ToString() {
  map<string, Relation*>::iterator it;
  for (it = this->data.begin(); it != data.end(); it++) {
    cout << it->second->ToString();
  }
}
