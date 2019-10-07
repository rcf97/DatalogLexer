#include <iostream>
#include <ostream>
#include <vector>
using namespace std;

#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(string fileName) {
  this->scnPtr = new Scanner(fileName);
  this->tokens = this->scnPtr->Read();
  this->parsePtr = new Parser(this->tokens);
  this->parsePtr->Parse();
  this->V = this->parsePtr->V;
  this->ToString();
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

void DatalogProgram::ToString() {
  cout << "Schemes(" << this->V.at(0).size() << "):" << endl;
  for (unsigned int i = 0; i < this->V.at(0).size(); i++) {
    cout << "  " << this->V.at(0).at(i)->ToString() << endl;
  }
  cout << "Facts(" << this->V.at(1).size() << "):" << endl;
  for (unsigned int i = 0; i < this->V.at(1).size(); i++) {
    cout << "  " << this->V.at(1).at(i)->ToString() << endl;
  }
  cout << "Queries(" << this->V.at(2).size() << "):" << endl;
  for (unsigned int i = 0; i < this->V.at(2).size(); i++) {
    cout << "  " << this->V.at(2).at(i)->ToString() << endl;
  }

}
