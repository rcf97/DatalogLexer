#pragma once
#include <iostream>
#include <map>
using namespace std;

#include "Predicate.h"
#include "Relation.h"
#include "Rule.h"

class Database {
private:
  map<string, Relation*> data;
  friend class DatalogProgram;
public:
  Database();
  ~Database();
  void AddScheme(Predicate* predPtr);
  void AddFact(Predicate* predPtr);
  void ToString();
  void EvalRule(Rule* rulePtr);
  void EvalQuery(Predicate* predPtr);
};
