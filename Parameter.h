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
public:
  Parameter();
  virtual string ToString() = 0;
};

class Expression : public Parameter {
private:
  Parameter* lhs;
  string op;
  Parameter* rhs;
public:
  Expression(Parameter* lhs, string op, Parameter* rhs);
  string ToString();
};

class StringParam : public Parameter {
public:
  StringParam(string value);
  string ToString();
};

class IDParam : public Parameter {
public:
  IDParam(string value);
  string ToString();
};
