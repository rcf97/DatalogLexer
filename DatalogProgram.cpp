#include <iostream>
#include <ostream>
#include <vector>
using namespace std;

#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(string fileName) {
  this->scnPtr = new Scanner(fileName);
  this->tokens = this->scnPtr->Read();
  this->parsePtr = new Parser(this->tokens);
  this->scnPtr->Print();
  this->parsePtr->Parse();
}

DatalogProgram::~DatalogProgram() {
  Scanner* scanner;
  scanner = this->scnPtr;
  this->scnPtr = nullptr;
  delete scanner;
  this->tokens.clear();
  Parser* parserPtr;
  parserPtr = this->parsePtr;
  this->parsePtr = nullptr;
  delete parserPtr;
}
