#pragma once
#include <iostream>
#include <vector>
using namespace std;

#include "Tokens.h"
#include "Scanner.h"
#include "Parser.h"
#include "Predicate.h"
#include "Rule.h"
#include "Database.h"
#include "Graph.h"

class DatalogProgram {
private:
  vector<Tokens> tokens;
  Scanner* scnPtr;
  Parser* parsePtr;
  vector<vector<Predicate*>> V;
  vector<Predicate*> schemesV;
  vector<Predicate*> factsV;
  vector<Rule*> rulesV;
  vector<Predicate*> queriesV;
  set<string> domain;
  Database* databasePtr;
  Graph* ruleGraphPtr;
  friend class Parser;
public:
  DatalogProgram(string fileName);
  ~DatalogProgram();
  void FixRules();
  void ToString();
  void ToDatabase();
  void EvalRule();
  void EvalQuery();
  void FixedPoint(set<int> scc, bool flag);
};
