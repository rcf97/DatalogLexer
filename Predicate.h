#pragma once
#include <iostream>
#include <vector>
using namespace std;

#include "Parameter.h"

class Predicate {
protected:
  string ident;
  vector<Parameter*> paramlist;
  friend class Parser;
public:
  Predicate(string ident);
  string ToString();
};
