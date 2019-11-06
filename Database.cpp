#include <iostream>
#include <map>
#include <string>
#include <iterator>
using namespace std;

#include "Database.h"
#include "Predicate.h"
#include "Relation.h"
#include "Scheme.h"
#include "Tokens.h"

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

void Database::EvalQuery(Predicate* predPtr) {
  string schname = predPtr->getIdent();
  Scheme newSch = *this->data[schname]->relScheme;
  Relation newRel = *this->data[schname];
  newRel.relScheme = &newSch;
  //cout << newRel.ToString() << endl;
  unsigned int i;
  int constPos1 = -1;
  string const1;
  int constPos2 = -1;
  string const2;
  int constPos3 = -1;
  string const3;
  vector<int> varPos;
  vector<string> var;
  for (i = 0; i < predPtr->paramlist.size(); i++) {
    switch(predPtr->paramlist.at(i)->WhatIs()) {
      case ID:
        varPos.push_back(i);
        var.push_back(predPtr->paramlist.at(i)->ToString());
        break;
      case String:
        if (constPos1 == -1) {
          constPos1 = i;
          const1 = predPtr->paramlist.at(i)->ToString();
        }
        else if (constPos2 == -1) {
          constPos2 = i;
          const2 = predPtr->paramlist.at(i)->ToString();
        }
        else if (constPos3 == -1) {
          constPos3 = i;
          const3 = predPtr->paramlist.at(i)->ToString();
        }
        break;
      case expression:
        cout << "error: expression" << endl;
        break;
      default:
        cout << "error" << endl;
    }
  }
  if (constPos1 != -1) {
    newRel.Select(constPos1, const1);
    if (constPos2 != -1) {
      newRel.Select(constPos2, const2);
      if (constPos3 != -1) {
        newRel.Select(constPos3, const3);
      }
    }
  }
  vector<int> delList;
  unsigned int j;
  for (i = 0; i < var.size(); i++) {
    for (j = i; j < var.size(); j++) {
      if (i != j && var.at(i) == var.at(j)) {
        newRel.Select(varPos.at(i), varPos.at(j));
        delList.push_back(j);
      }
    }
  }
  for (i = 0; i < delList.size(); i++) {
    if (varPos.size() > 1) {
      varPos.erase(varPos.begin() + delList.at(i) - i);
      var.erase(var.begin() + delList.at(i) - i);
    }
  }
  newRel.Project(varPos);
  newRel.Rename(var);
  //cout << "orig." << this->data[newRel.name]->ToString() << endl;

  //OUTPUT QUERY
  cout << predPtr->ToString() << "? ";
  if (newRel.tuples.size() == 0) {
    cout << "No" << endl;
  }
  else {
    cout << "Yes(" << newRel.tuples.size() << ")" << endl;
    if (var.size() != 0) {
      set<Tuple>::iterator it;

      for (it = newRel.tuples.begin(); it != newRel.tuples.end(); it++) {
        Tuple tpl = *it;
        for (i = 0; i < var.size(); i++) {
          if (i == 0) { cout << "  "; }
          cout << var.at(i) << "=" << tpl.elements.at(i);
          if (i != var.size() - 1) { cout << ", "; }
        }
        cout << endl;
      }
    }
  }
}
