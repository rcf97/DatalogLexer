#pragma once
#include <iostream>
using namespace std;

#include "Tokens.h"

class Parameter {
protected:
  TokenType type;
  string value;
  friend class Parser;
  friend class DatalogProgram;
  friend class Database;
public:
  Parameter();
  virtual string ToString() = 0;
  virtual TokenType WhatIs() = 0;
};

class Expression : public Parameter {
private:
  Parameter* lhs;
  string op;
  Parameter* rhs;
public:
  Expression(Parameter* lhs, string op, Parameter* rhs);
  string ToString();
  TokenType WhatIs();
};

class StringParam : public Parameter {
public:
  StringParam(string value);
  string ToString();
  TokenType WhatIs();
};

class IDParam : public Parameter {
public:
  IDParam(string value);
  string ToString();
  TokenType WhatIs();
};
