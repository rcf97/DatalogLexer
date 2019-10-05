#pragma once
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

#include "Tokens.h"

class Parser {
private:
  queue<Tokens> tokens;
  stack<TokenType> tknStack;
public:
  Parser(vector<Tokens> tkns);
  ~Parser();
  void Parse();
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
  void Parseparameter();
  void Parseexpression();
  void Parseoperator();
};
