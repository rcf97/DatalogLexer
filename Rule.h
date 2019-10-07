#pragma once
#include <iostream>
#include <vector>
using namespace std;

#include "Predicate.h"

class Rule {
  Predicate* head;
  vector<Predicate*> predlist;
public:
  Rule(Predicate* head);
  void addPred(Predicate* add);
  string ToString();
};
