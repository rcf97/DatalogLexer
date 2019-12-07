#include <iostream>
#include <ostream>
#include <vector>
#include <set>
#include <iterator>
using namespace std;

#include "DatalogProgram.h"
#include "Rule.h"
#include "Database.h"
#include "Graph.h"

DatalogProgram::DatalogProgram(string fileName) {
  this->scnPtr = new Scanner(fileName);
  this->tokens = this->scnPtr->Read();
  this->parsePtr = new Parser(this->tokens);
  bool flag = this->parsePtr->Parse();
  if (flag) {
    this->V = this->parsePtr->V;
    this->domain = this->parsePtr->domain;
    this->FixRules();
    //this->ToString();
    this->ToDatabase();
    this->EvalRule();
    //this->databasePtr->ToString();
    this->EvalQuery();
  }
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
  for (unsigned int i = 1; i < this->V.size() - 1; i++) {
    if (this->V.at(i).empty()) {
      continue;
    }
    rulePtr = new Rule(V.at(i).at(0));
    for (unsigned int j = 1; j < V.at(i).size(); j++) {
      rulePtr->addPred(this->V.at(i).at(j));
    }
    this->rulesV.push_back(rulePtr);
  }
  this->queriesV = this->V.back();
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
  cout << "Rules(";
  if (this->rulesV.empty()) {
    cout << "0";
  }
  else {
    cout << this->rulesV.size() - 1;
  }
  cout << "):" << endl;
  for (unsigned int i = 1; i < this->rulesV.size(); i++) {
    cout << "  " << this->rulesV.at(i)->ToString() << endl;
  }
  cout << "Queries(" << this->queriesV.size() << "):" << endl;
  for (unsigned int i = 0; i < this->queriesV.size(); i++) {
    cout << "  " << this->queriesV.at(i)->ToString() << "?" << endl;
  }
  cout << "Domain(" << this->domain.size() << "):" << endl;
  set<string>::iterator it;
  for (it = domain.begin(); it != domain.end(); it++) {
    cout << *it << endl;
  }
}

void DatalogProgram::ToDatabase() {
  Database* databasePtr;
  databasePtr = new Database();
  this->databasePtr = databasePtr;
  unsigned int i;
  for (i = 0; i < this->schemesV.size(); i++) {
    this->databasePtr->AddScheme(this->schemesV.at(i));
  }
  for (i = 0; i < this->factsV.size(); i++) {
    this->databasePtr->AddFact(this->factsV.at(i));
  }
}

void DatalogProgram::EvalRule() {
  //Brute force algorithm
  /*unsigned int i;
  cout << "Rule Evaluation" << endl;
  int additions = 1;
  int precount = 0;
  int postcount = 0;
  int passes = 0;
  map<string, Relation*>::iterator it;
  while (additions != 0) {
    precount = 0;
    postcount = 0;
    for (it = this->databasePtr->data.begin(); it != this->databasePtr->data.end(); it++) {
      precount += it->second->tuples.size();
    }
    for (i = 1; i < this->rulesV.size(); i++) {
      this->databasePtr->EvalRule(this->rulesV.at(i));
    }
    for (it = this->databasePtr->data.begin(); it != this->databasePtr->data.end(); it++) {
      postcount += it->second->tuples.size();
    }
    passes++;
    additions = postcount - precount;
  }
  cout << endl << "Schemes populated after " << passes << " passes through the Rules." << endl << endl;*/

  //Efficient algorithm - Strongly Connected Components
  Graph* graphPtr;
  graphPtr = new Graph(this->rulesV);
  this->ruleGraphPtr = graphPtr;
  cout << this->ruleGraphPtr->ToString() << endl;
}

void DatalogProgram::EvalQuery() {
  unsigned int i;
  cout << "Query Evaluation" << endl;
  for (i = 0; i < this->queriesV.size(); i++) {
    this->databasePtr->EvalQuery(this->queriesV.at(i));
  }
}
