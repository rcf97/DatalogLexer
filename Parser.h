#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <set>
using namespace std;

#include "Tokens.h"
#include "Predicate.h"

class Parser {
private:
  queue<Tokens> tokens;
  stack<TokenType> tknStack;
  vector<vector<Predicate*>> V;
  vector<Predicate*> schemesV;
  vector<Predicate*> factsV;
  vector<Predicate*> queriesV;
  set<string> domain;
  friend class DatalogProgram;
public:
  Parser(vector<Tokens> tkns);
  ~Parser();
  bool Parse();
  void ParseDatalogProgram();
  void ParseschemeList();
  void ParsefactList();
  void ParseruleList();
  void ParsequeryList();
  void Parsescheme();
  void Parsefact();
  void Parserule();
  void Parsequery();
  void ParseheadPredicate();
  void Parsepredicate();
  void ParsepredicateList();
  void ParseparameterList();
  void ParsestringList();
  void ParseidList();
  Parameter* Parseparameter();
  Expression* Parseexpression();
  string Parseoperator();
};
