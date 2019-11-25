#pragma once
#include <iostream>
#include <string>
#include <set>
using namespace std;

#include "Tuple.h"
#include "Scheme.h"
#include "Predicate.h"

class Relation {
protected:
  string name;
  Scheme relScheme;
  set<Tuple> tuples;
  friend class Database;
public:
  Relation();
  Relation(Scheme* schemePtr);
  ~Relation();
  void Select(int pos, string val);
  void Select(int pos1, int pos2);
  void Project(vector<int> pos);
  void Rename(vector<string> var);
  void Join(Relation* rel1);
  void Unite(Relation* relPtr);
  void AddFact(Predicate* predPtr);
  string ToString() const;
};
