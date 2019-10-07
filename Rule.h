#pragma once
#include <iostream>
#include <vector>
using namespace std;

#include "Predicate.h"

class Rules : public Predicate {
  Predicate* head;
  vector<Predicate*> predlist;
public:
  Rules();
  string ToString();
};
