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
#include "Rule.h"

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

void Database::EvalRule(Rule* rulePtr) {
  Relation rel1, rel2, rel3, rel4, rel5;
  vector<Relation> newRels{rel1, rel2, rel3, rel4, rel5};
  for (unsigned int k = 0; k < rulePtr->predlist.size(); k++) {
    Predicate* predPtr = rulePtr->predlist.at(k);
    string schname = predPtr->getIdent();
    newRels.at(k).name = schname;
    newRels.at(k).tuples = this->data[schname]->tuples;
    newRels.at(k).relScheme = this->data[schname]->relScheme;
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
      newRels.at(k).Select(constPos1, const1);
      if (constPos2 != -1) {
        newRels.at(k).Select(constPos2, const2);
        if (constPos3 != -1) {
          newRels.at(k).Select(constPos3, const3);
        }
      }
    }
    vector<int> delList;
    unsigned int j;
    for (i = 0; i < var.size(); i++) {
      for (j = i; j < var.size(); j++) {
        if (i != j && var.at(i) == var.at(j)) {
          newRels.at(k).Select(varPos.at(i), varPos.at(j));
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
    newRels.at(k).Project(varPos);
    newRels.at(k).Rename(var);
  }

  //Join Predicates on RHS
  for (unsigned int i = 1; i < rulePtr->predlist.size(); i++) {
    newRels.at(0).Join(&newRels.at(i));
  }

  //Manipulate intermediate relation to produce new rule
  unsigned int i;
  unsigned int j;
  vector<int> projPos;
  for (i = 0; i < rulePtr->head->paramlist.size(); i++) {
    for (j = 0; j < newRels.at(0).relScheme.attributes.size(); j++) {
      if (rulePtr->head->paramlist.at(i)->value == newRels.at(0).relScheme.attributes.at(j)) {
        projPos.push_back(j);
      }
    }
  }
  newRels.at(0).Project(projPos);
  newRels.at(0).relScheme.name = rulePtr->head->ident;

  //UNION PROCESS
  //Make compatible
  newRels.at(0).Rename(this->data[newRels.at(0).relScheme.name]->relScheme.attributes);

  //Output new tuples
  cout << rulePtr->ToString() << endl;
  set<Tuple>::iterator ittup;
  for (ittup = newRels.at(0).tuples.begin(); ittup != newRels.at(0).tuples.end(); ittup++) {
    for (i = 0; i < newRels.at(0).relScheme.attributes.size(); i++) {
      if (i == 0) {cout << "  ";}
      cout << newRels.at(0).relScheme.attributes.at(i) << "=" << ittup->elements.at(i);
      if (i != newRels.at(0).relScheme.attributes.size() - 1) {cout << ", ";}
      else {cout << endl;}
    }
  }

  //cout << newRels.at(0).ToString() << endl;
  this->data[newRels.at(0).relScheme.name]->Unite(newRels.at(0));
}

void Database::EvalQuery(Predicate* predPtr) {
  string schname = predPtr->getIdent();
  Scheme newSch = this->data[schname]->relScheme;
  Relation newRel = *this->data[schname];
  newRel.relScheme = newSch;
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

  //OUTPUT QUERY
  cout << "Query Evaluation" << endl;
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
