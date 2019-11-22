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

Relation Relation::Join(Relation rel1, Relation rel2) {
  Scheme* newSch;
  string newName = rel1.name + rel2.name;
  vector<string> att;
  unsigned int i;
  unsigned int j;
  for (i = 0; i < rel1.attributes.size(); i++) {
    att.push_back(rel1.attributes.at(i));
  }
  for (i = 0; i < rel2.attributes.size(); i++) {
    att.push_back(rel2.attributes.at(i));
  }
  map<int, int> common;
  for (i = 0; i < rel1.attributes.size(); i++) {
    for (j = i; j < rel2.attributes.size(); j++) {
      if (rel1.attributes.at(i) == rel2.attributes.at(j)) {
        common[i] = j;
      }
    }
  }
  newSch = new Scheme(name, att);
  Relation* joined;
  joined = new Relation(newSch);
  set<Tuple>::iterator it1;
  set<Tuple>::iterator it2;
  vector<string> newTup;
  map<int, int>::iterator it;
  bool add;
  if (common.size() == 0) {
    for (it1 = rel1.tuples.begin(); it1 != rel1.tuples.end(); it1++) {
      for (it2 = rel2.tuples.begin(); it2 != rel2.tuples.end(); it2++) {
        for (i = 0; i < it1->elements.size(); i++) {
          newTup.push_back(it1->elements.at(i));
        }
        for (i = 0; i < it2->elements.size(); i++) {
          newTup.push_back(it2->elements.at(i));
        }
        joined.tuples.insert(newTup);
      }
    }
  }
  else {
    for (it1 = rel1.tuples.begin(); it1 != rel1.tuples.end(); it1++) {
      for (it2 = rel2.tuples.begin(); it2 != rel2.tuples.end(); it2++) {
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
            newTup.push_back(it2->elements.at(i));
          }
          joined.tuples.insert(newTup);
        }
      }
    }
  }
  return joined;
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
