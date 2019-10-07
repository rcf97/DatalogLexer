#include <iostream>
using namespace std;

#include "Parameter.h"

Parameter::Parameter() {}

string Parameter::ToString() {
  return this->value;
}

Expression::Expression(Parameter* lhs, Tokens* op, Parameter* rhs) {
  this->lhs = lhs;
  this->op = op;
  this->rhs = rhs;
}

string Expression::ToString() {
  string out;
  out += this->lhs->ToString();
  out += this->op->value;
  out += this->rhs->ToString();
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
