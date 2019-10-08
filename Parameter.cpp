#include <iostream>
using namespace std;

#include "Parameter.h"

Parameter::Parameter() {}

Expression::Expression(Parameter* lhs, string op, Parameter* rhs) {
  this->lhs = lhs;
  this->op = op;
  this->rhs = rhs;
}

string Expression::ToString() {
  string out;
  out += "(";
  out += this->lhs->ToString();
  out += this->op;
  out += this->rhs->ToString();
  out += ")";
  return out;
}

StringParam::StringParam(string value) {
  this->type = String;
  this->value = value;
}

IDParam::IDParam(string value) {
  this->value = value;
  this->type = ID;
}

string StringParam::ToString() {
  return this->value;
}

string IDParam::ToString() {
  return this->value;
}
