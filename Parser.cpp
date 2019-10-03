#include <iostream>
#include <vector>
using namespace std;

#include "Parser.h"
#include "Tokens.h"

Parser::Parser(vector<Tokens> tkns) {
  for (unsigned int i = 0; i < tkns.size(); i++) {
    Tokens curTkn = tkns.at(i);
    if (curTkn->type != Comment) {
      this->tokens.push(curTkn);
    }
  }
  this->tknStack.push_back(EndFile);
  this->tknStack.push_back(queryList);
  this->tknStack.push_back(query);
  this->tknStack.push_back(Colon);
  this->tknStack.push_back(Queries);
  this->tknStack.push_back(ruleList);
  this->tknStack.push_back(Colon);
  this->tknStack.push_back(Rules);
  this->tknStack.push_back(factList);
  this->tknStack.push_back(Colon);
  this->tknStack.push_back(Facts);
  this->tknStack.push_back(schemeList);
  this->tknStack.push_back(scheme);
  this->tknStack.push_back(Colon);
  this->tknStack.push_back(Schemes);
}

Parser::~Parser(){}

void Parser::Parse() {
  this->ParseDatalogProgram();
  catch (Tokens thrown) {
    cout << "Failure!" << endl << "\t" << thrown->ToString() << endl;
  }
}

void Parser::ParseDatalogProgram() {
  while (tknStack.top() != EndFile) {
    if (tknStack.top() == tokens.front()->type) {
      tknStack.pop();
      tokens.pop();
    }
    else {
      switch (tknStack.top()) {
        case scheme: this->Parsescheme(); break;
        case schemeList: this->ParseschemeList(); break;
        case factList: this->ParsefactList(); break;
        case ruleList: this->ParseruleList(); break;
        case query: this->Parsequery(); break;
        case queryList: this->ParsequeryList(); break;
        default:
          try{ throw tokens.front();} break;
      }
    }
  }
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    try{ throw tokens.front(); }
  }
}

void Parser::ParseschemeList() {

}

void Parser::ParsefactList() {

}

void Parser::ParseruleList() {

}

void Parser::ParsequeryList() {

}

void Parser::Parsescheme() {
  tknStack.pop();
  tknStack.push(RigPar);
  tknStack.push(idList);
  tknStack.push(ID);
  tknStack.push(LeftPar);
  tknStack.push(ID);
  while (tknStack.top() != EndFile) {
    if (tknStack.top() == tokens.front()->type) {
      tknStack.pop();
      tokens.pop();
    }
    else {
      switch (tknStack.top()) {
        case idList: this->ParseidList(); break;
        default:
          try{ throw tokens.front();} break;
      }
    }
  }
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    try{ throw tokens.front(); }
  }
}

void Parser::Parsefact() {
  if (tknStack.top()->type != ID) {
    try{throw 1;}
  }
}

void Parser::Parserule() {

}

void Parser::Parsequery() {

}

void Parser::ParseheadPredicate() {

}

void Parser::Parsepredicate() {

}

void Parser::ParsepredicateList() {

}

void Parser::ParseparameterList() {

}

void Parser::ParsestringList() {

}

void Parser::ParseidList() {

}

void Parser::Parseparameter() {

}

void Parser::Parseexpression() {

}

void Parser::Parseoperator() {

}
