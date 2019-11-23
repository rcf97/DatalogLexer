#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <string>
#include <map>
using namespace std;

#include "Relation.h"
#include "Scheme.h"
#include "Predicate.h"
#include "Tuple.h"

Relation::Relation(Scheme* schemePtr) {
  this->name = schemePtr->getName();
  this->relScheme = schemePtr;
}

Relation::~Relation() {

}

void Relation::AddFact(Predicate* predPtr) {
  vector<string> elements;
  unsigned int i;
  for (i = 0; i < predPtr->paramlist.size(); i++) {
    elements.push_back(predPtr->paramlist.at(i)->ToString());
  }
  Tuple* tplPtr;
  tplPtr = new Tuple(elements);
  Tuple tpl = *tplPtr;
  this->tuples.insert(tpl);
}

void Relation::Select(int pos, string val) {
  set<Tuple>::iterator it;
  vector<Tuple> eraseS;
  for (it = this->tuples.begin(); it != this->tuples.end(); it++) {
    Tuple tpl = *it;
    if (tpl.elements.at(pos) != val) {
      //this->tuples.erase(tpl);
      eraseS.push_back(tpl);
    }
  }
  for (unsigned int i = 0; i < eraseS.size(); i++) {
    this->tuples.erase(eraseS.at(i));
  }
    //cout << this->ToString() << endl << endl;
}

void Relation::Select(int pos1, int pos2) {
  set<Tuple>::iterator it;
  for (it = this->tuples.begin(); it != this->tuples.end(); it++) {
    Tuple tpl = *it;
    if (tpl.elements.at(pos1) != tpl.elements.at(pos2)) {
      this->tuples.erase(tpl);
    }
  }
    //cout << this->ToString() << endl << endl;
}

void Relation::Project(vector<int> pos) {
  unsigned int i;
  vector<string> newAt;
  for (i = 0; i < pos.size(); i++) {
    newAt.push_back(this->relScheme->attributes.at(pos.at(i)));
  }
  this->relScheme->attributes = newAt;
  set<Tuple>::iterator it;
  set<Tuple> newSet;
  for (it = this->tuples.begin(); it != this->tuples.end(); it++) {
    vector<string> newEl;
    Tuple tpl = *it;
    for (i = 0; i < pos.size(); i++) {
      newEl.push_back(tpl.elements.at(pos.at(i)));
    }
    tpl.elements = newEl;
    newSet.insert(tpl);
  }
  this->tuples = newSet;
  //cout << this->ToString() << endl << endl;
}

void Relation::Rename(vector<string> var) {
  unsigned int i;
  for (i = 0; i < var.size(); i++) {
    this->relScheme->attributes.at(i) = var.at(i);
  }
  //cout << this->ToString() << endl << endl;
}

void Relation::Join(Relation rel1) {
  string newName = this->name + rel1.name;
  vector<string> att;
  unsigned int i;
  unsigned int j;
  set<int> notInclude;
  map<int, int> common;
  for (i = 0; i < this->relScheme->attributes.size(); i++) {
    for (j = 0; j < rel1.relScheme->attributes.size(); j++) {
      string temp1 = this->relScheme->attributes.at(i);
      string temp2 = rel1.relScheme->attributes.at(j);
      if (temp1 == temp2) {
        common[i] = j;
        notInclude.insert(j);
      }
    }
  }
  for (i = 0; i < this->relScheme->attributes.size(); i++) {
    att.push_back(this->relScheme->attributes.at(i));
  }
  for (i = 0; i < rel1.relScheme->attributes.size(); i++) {
    if (notInclude.find(i) == notInclude.end()) {
      att.push_back(rel1.relScheme->attributes.at(i));
    }
  }

  delete this->relScheme;
  this->relScheme = nullptr;
  this->relScheme = new Scheme(newName, att);
  set<Tuple>::iterator it1;
  set<Tuple>::iterator it2;
  vector<string> newTup;
  vector<Tuple*> newTuples;
  map<int, int>::iterator it;
  bool add;
  if (notInclude.size() == 0) {
    for (it1 = this->tuples.begin(); it1 != this->tuples.end(); it1++) {
      for (it2 = rel1.tuples.begin(); it2 != rel1.tuples.end(); it2++) {
        for (i = 0; i < it1->elements.size(); i++) {
          string temp = it1->elements.at(i);
          newTup.push_back(temp);
        }
        for (i = 0; i < it2->elements.size(); i++) {
          string temp = it2->elements.at(i);
          if (notInclude.find(i) == notInclude.end()) {
            newTup.push_back(temp);
          }
        }
        Tuple* newTpl;
        newTpl = new Tuple(newTup);
        newTuples.push_back(newTpl);
        newTup.clear();
      }
    }
  }
  else {
    for (it1 = this->tuples.begin(); it1 != this->tuples.end(); it1++) {
      for (it2 = rel1.tuples.begin(); it2 != rel1.tuples.end(); it2++) {
        add = true;
        for (it = common.begin(); it != common.end(); it++) {
          if (it1->elements.at(it->first) != it2->elements.at(it->second)) {
            add = false;
          }
        }
        if (add) {
          for (i = 0; i < it1->elements.size(); i++) {
            newTup.push_back(it1->elements.at(i));
          }
          for (i = 0; i < it2->elements.size(); i++) {
            if (notInclude.find(i) == notInclude.end()) {
              newTup.push_back(it2->elements.at(i));
            }
          }
          Tuple* newTpl;
          newTpl = new Tuple(newTup);
          newTuples.push_back(newTpl);
          newTup.clear();
        }
      }
    }
  }
  this->tuples.clear();
  for (i = 0; i < newTuples.size(); i++) {
    this->tuples.insert(*newTuples.at(i));
  }
}

string Relation::ToString() {
  string output = "";
  output += this->relScheme->ToString();
  //output += "\n";
  set<Tuple>::iterator it;
  for (it = tuples.begin(); it != tuples.end(); it++) {
    output += "\t";
    Tuple tpl = *it;
    output += tpl.ToString();
    output += "\n";
  }
  return output;
}
