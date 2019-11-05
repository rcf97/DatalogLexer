#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Tuple {
private:
  vector<string> elements;
public:
  Tuple(vector<string> elements);
  ~Tuple();
  string ToString();
};
