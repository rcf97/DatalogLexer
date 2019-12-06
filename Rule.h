#pragma once
#include <iostream>
#include <vector>
using namespace std;

#include "Predicate.h"

class Rule {
protected:
  Predicate* head;
  vector<Predicate*> predlist;
  friend class Database;
  friend class Graph;
public:
  Rule(Predicate* head);
  void addPred(Predicate* add);
  string ToString();
};
