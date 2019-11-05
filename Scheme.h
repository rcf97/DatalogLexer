#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "Predicate.h"

class Scheme {
private:
  string name;
  vector<string> attributes;
public:
  Scheme(Predicate* predPtr);
  ~Scheme();
  string getName();
};
