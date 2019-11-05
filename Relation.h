#pragma once
#include <iostream>
#include <string>
#include <set>
using namespace std;

#include "Tuple.h"
#include "Scheme.h"
#include "Predicate.h"

class Relation {
private:
  string name;
  Scheme* relScheme;
  set<Tuple*> tuples;
public:
  Relation(Scheme* schemePtr);
  ~Relation();
  void Select();
  void Project();
  void Rename();
  void AddFact(Predicate* predPtr);
  string ToString();
};
