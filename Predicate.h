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
  friend class Scheme;
  friend class Relation;
  friend class Database;
public:
  Predicate(string ident);
  string ToString();
  string getIdent();
};
