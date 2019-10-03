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
    return
  }
  cout << "Success!" << endl;
}

void Parser::ParseDatalogProgram() {
  do {
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
  } while (tknStack.top() != EndFile);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    try{ throw tokens.front(); }
  }
}

void Parser::ParseschemeList() {
  tknStack.pop();
  switch (tokens.front()) {
    case ID:
      tknStack.push(schemeList);
      tknStack.push(scheme);
      this->Parsescheme();
      this->ParseschemeList();
      break;
    case Facts:
      return;
      break;
    default:
      try{ throw tokens.front();}
      break;
    }
}

void Parser::ParsefactList() {
  tknStack.pop();
  switch (tokens.front()) {
    case ID:
      tknStack.push(factList);
      tknStack.push(fact);
      this->Parsefact();
      this->ParsefactList();
      break;
    case Rules:
      return;
      break;
    default:
      try{ throw tokens.front(); break;}
  }
}

void Parser::ParseruleList() {
  tknStack.pop();
  switch (tokens.front()) {
    case ID:
      tknStack.push(ruleList);
      tknStack.push(rule);
      this->Parserule();
      this->ParseruleList();
      break;
    case Queries:
      return;
      break;
    default:
      try{ throw tokens.front(); break;}
  }
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
  do {
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
  } while (tknStack.top() != RigPar);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    try{ throw tokens.front(); }
  }
}

void Parser::Parsefact() {
  tknStack.pop();
  tknStack.push(Period);
  tknStack.push(RigPar);
  tknStack.push(stringList);
  tknStack.push(String);
  tknStack.push(LeftPar);
  tknStack.push(ID);
  do {
    if (tknStack.top() == tokens.front()->type) {
      tknStack.pop();
      tokens.pop();
    }
    else {
      switch (tknStack.top()) {
        case idList: this->ParsestringList(); break;
        default:
          try{ throw tokens.front();} break;
      }
    }
  } while (tknStack.top() != Period);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    try{ throw tokens.front(); }
  }
}

void Parser::Parserule() {
  tknStack.pop();
  tknStack.push(Period);
  tknStack.push(predicateList);
  tknStack.push(predicate);
  tknStack.push(ColonDash);
  tknStack.push(headPredicate);
  do {
    if (tknStack.top() == tokens.front()->type) {
      tknStack.pop();
      tokens.pop();
    }
    else {
      switch (tknStack.top()) {
        case headPredicate:
          this->ParseheadPredicate();
          break;
        case predicate:
          this->Parsepredicate();
          break;
        case predicateList:
          this->ParsepredicateList();
          break;
        default:
          try{ throw tokens.front();} break;
      }
    }
  } while (tknStack.top() != Period);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    try{ throw tokens.front(); }
  }
}

void Parser::Parsequery() {
  tknStack.pop();
  tknStack.push(QMark);
  tknStack.push(predicate);
  do {
    if (tknStack.top() == tokens.front()->type) {
      tknStack.pop();
      tokens.pop();
    }
    else {
      switch (tknStack.top()) {
        case predicate: this->Parsepredicate(); break;
        default:
          try{ throw tokens.front();} break;
      }
    }
  } while (tknStack.top() != QMark);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    try{ throw tokens.front(); }
  }
}

void Parser::ParseheadPredicate() {
  tknStack.pop();
  tknStack.push(RigPar);
  tknStack.push(idList);
  tknStack.push(ID);
  tknStack.push(LeftPar);
  tknStack.push(ID);
  do {
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
  } while (tknStack.top() != RigPar);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    try{ throw tokens.front(); }
  }
}

void Parser::Parsepredicate() {
  tknStack.pop();
  tknStack.push(RigPar);
  tknStack.push(parameterList);
  tknStack.push(parameter);
  tknStack.push(LeftPar);
  tknStack.push(ID);
  do {
    if (tknStack.top() == tokens.front()->type) {
      tknStack.pop();
      tokens.pop();
    }
    else {
      switch (tknStack.top()) {
        case parameter: this->Parseparameter(); break;
        case parameterList: this->ParseparameterList(); break;
        default:
          try{ throw tokens.front();} break;
      }
    }
  } while (tknStack.top() != RigPar);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    try{ throw tokens.front(); }
  }
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
