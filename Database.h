#pragma once
#include <iostream>
#include <map>
using namespace std;

#include "Predicate.h"
#include "Relation.h"

class Database {
private:
  map<string, Relation*> data;
public:
  Database();
  ~Database();
  void AddScheme(Predicate* predPtr);
  void AddFact(Predicate* predPtr);
  void ToString();
};
