#include <iostream>
#include <ostream>
#include <vector>
using namespace std;

#include "DatalogProgram.h"
#include "Rule.h"

DatalogProgram::DatalogProgram(string fileName) {
  this->scnPtr = new Scanner(fileName);
  this->tokens = this->scnPtr->Read();
  this->parsePtr = new Parser(this->tokens);
  this->parsePtr->Parse();
  this->V = this->parsePtr->V;
  this->domainV = this->parsePtr->domainV;
  this->FixRules();
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

void DatalogProgram::FixRules() {
  this->schemesV = this->V.at(0);
  this->factsV = this->V.at(1);
  Rule* rulePtr = nullptr;
  unsigned int k = 0;
  for (unsigned int i = 1; i < this->V.size() - 1; i++) {
    rulePtr = new Rule(V.at(i).at(0));
    for (unsigned int j = 1; j < V.at(i).size(); j++) {
      rulePtr->addPred(this->V.at(i).at(j));
    }
    this->rulesV.push_back(rulePtr);
    k = i;
  }
  this->queriesV = this->V.at(k + 1);
}

void DatalogProgram::ToString() {
  cout << "Schemes(" << this->schemesV.size() << "):" << endl;
  for (unsigned int i = 0; i < this->schemesV.size(); i++) {
    cout << "  " << this->schemesV.at(i)->ToString() << endl;
  }
  cout << "Facts(" << this->factsV.size() << "):" << endl;
  for (unsigned int i = 0; i < this->factsV.size(); i++) {
    cout << "  " << this->factsV.at(i)->ToString() << "." << endl;
  }
  cout << "Rules(" << this->rulesV.size() << "):" << endl;
  for (unsigned int i = 1; i < this->rulesV.size(); i++) {
    cout << "  " << this->rulesV.at(i)->ToString() << endl;
  }
  cout << "Queries(" << this->queriesV.size() << "):" << endl;
  for (unsigned int i = 0; i < this->queriesV.size(); i++) {
    cout << "  " << this->queriesV.at(i)->ToString() << "?" << endl;
  }
  cout << "Domain(" << this->domainV.size() << "):" << endl;
  for (unsigned int i = 0; i < this->domainV.size(); i++) {
    cout << "  " << this->domainV.at(i) << endl;
  }
}
