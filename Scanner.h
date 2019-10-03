#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "Tokens.h"

class Scanner {
private:
  ifstream file;
  vector<Tokens> tokens;
  string fileName;
  int curLine;
public:
  Scanner(string fileName);
  ~Scanner();
  vector<Tokens> Read();
  void Comments();
  void Punct();
  void Undef(int lineNum, string value = "");
  void KeyID();
  void Strings();
  void Print();
  vector<Tokens> GetTokens();
};
