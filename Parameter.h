#pragma once
#include <iostream>
using namespace std;

#include "Tokens.h"

class Parameter {
protected:
  TokenType type;
  string value;
  friend class Parser;
public:
  Parameter();
  string ToString();
  TokenType is();
};

class Expression : public Parameter {
private:
  Parameter* lhs;
  Tokens* op;
  Parameter* rhs;
public:
  Expression(Parameter* lhs, Tokens* op, Parameter* rhs);
  string ToString();
};

class StringParam : public Parameter {
public:
  StringParam(string value);
};

class IDParam : public Parameter {
public:
  IDParam(string value);
};
