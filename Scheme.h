#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "Predicate.h"

class Scheme {
protected:
  string name;
  vector<string> attributes;
  friend class Relation;
  friend class Database;
public:
  Scheme();
  Scheme(Predicate* predPtr);
  Scheme(string name, vector<string> att);
  ~Scheme();
  string getName();
  string ToString() const;
};
