#pragma once
#include <iostream>
#include <vector>
using namespace std;

#include "Tokens.h"

class DatalogProgram {
private:
  vector<Tokens> tokens;
  Scanner* scnPtr;
  Parser* parsePtr;
  vector<Predicate> schemesV;
  vector<Predicate> factsV;
  vector<Rule> rulesV;
  vector<Predicate> queriesV;
public:
  DatalogProgram(string fileName);
  ~DatalogProgram();
};
