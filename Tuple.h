#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Tuple {
protected:
  vector<string> elements;
  friend class Relation;
  friend class Database;
public:
  Tuple(vector<string> elements);
  ~Tuple();
  string ToString();
  bool operator< (const Tuple& tpl) const;
};
