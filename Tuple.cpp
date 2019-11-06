#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include "Tuple.h"

Tuple::Tuple(vector<string> elements) {
  this->elements = elements;
}

Tuple::~Tuple() {}

string Tuple::ToString() {
  stringstream ss;
  ss << "(";
  for (unsigned int i = 0; i < this->elements.size(); i++) {
    ss << this->elements.at(i);
    if (i != this->elements.size() - 1) {
    	ss << ",";
    }
  }
  ss << ")";
  string output = ss.str();
  return output;
}

bool Tuple::operator< (const Tuple& tpl) const {
  string rightStr = "";
  for (unsigned int i = 0; i < tpl.elements.size(); i++) {
    rightStr += tpl.elements.at(i);
  }
  string leftStr = "";
  for (unsigned int i = 0; i < this->elements.size(); i++) {
    leftStr += this->elements.at(i);
  }
  return (leftStr < rightStr);
}
