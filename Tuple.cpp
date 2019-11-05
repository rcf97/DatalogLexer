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
    ss << ",";
  }
  ss << ")";
  string output = ss.str();
  return output;
}
