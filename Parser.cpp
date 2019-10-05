#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#include "Parser.h"
#include "Tokens.h"

Parser::Parser(vector<Tokens> tkns) {
  for (unsigned int i = 0; i < tkns.size(); i++) {
    Tokens curTkn = tkns.at(i);
    if (curTkn.type != Comment) {
      this->tokens.push(curTkn);
    }
  }
  this->tknStack.push(EndFile);
  this->tknStack.push(queryList);
  this->tknStack.push(query);
  this->tknStack.push(Colon);
  this->tknStack.push(Queries);
  this->tknStack.push(ruleList);
  this->tknStack.push(Colon);
  this->tknStack.push(Rules);
  this->tknStack.push(factList);
  this->tknStack.push(Colon);
  this->tknStack.push(Facts);
  this->tknStack.push(schemeList);
  this->tknStack.push(scheme);
  this->tknStack.push(Colon);
  this->tknStack.push(Schemes);
}

Parser::~Parser(){}

void Parser::Parse() {
  try{
    this->ParseDatalogProgram();
  }
  catch (Tokens thrown) {
    cout << "Failure!" << endl << "  " << thrown.ToString() << endl;
    return;
  }
  cout << "Success!" << endl;
}

void Parser::ParseDatalogProgram() {
  do {
    if (tknStack.top() == tokens.front().type) {
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
          throw tokens.front();
          break;
      }
    }
  } while (tknStack.top() != EndFile);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    throw tokens.front();
  }
}

void Parser::ParseschemeList() {
  tknStack.pop();
  switch (tokens.front().type) {
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
      throw tokens.front();
      break;
    }
}

void Parser::ParsefactList() {
  tknStack.pop();
  switch (tokens.front().type) {
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
      throw tokens.front();
  }
}

void Parser::ParseruleList() {
  tknStack.pop();
  switch (tokens.front().type) {
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
      throw tokens.front();
  }
}

void Parser::ParsequeryList() {
  tknStack.pop();
  switch (tokens.front().type) {
    case ID:
      tknStack.push(queryList);
      tknStack.push(query);
      this->Parsequery();
      this->ParsequeryList();
      break;
    case EndFile:
      return;
      break;
    default:
      throw tokens.front();
  }
}

void Parser::Parsescheme() {
  tknStack.pop();
  tknStack.push(RigPar);
  tknStack.push(idList);
  tknStack.push(ID);
  tknStack.push(LeftPar);
  tknStack.push(ID);
  do {
    if (tknStack.top() == tokens.front().type) {
      tknStack.pop();
      tokens.pop();
    }
    else {
      switch (tknStack.top()) {
        case idList:
          this->ParseidList();
          break;
        default:
          throw tokens.front();
          break;
      }
    }
  } while (tknStack.top() != RigPar);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    throw tokens.front();
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
    if (tknStack.top() == tokens.front().type) {
      tknStack.pop();
      tokens.pop();
    }
    else {
      switch (tknStack.top()) {
        case idList: this->ParsestringList(); break;
        default:
          throw tokens.front();
          break;
      }
    }
  } while (tknStack.top() != Period);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    throw tokens.front();
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
    if (tknStack.top() == tokens.front().type) {
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
          throw tokens.front();
          break;
      }
    }
  } while (tknStack.top() != Period);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    throw tokens.front();
  }
}

void Parser::Parsequery() {
  tknStack.pop();
  tknStack.push(Qmark);
  tknStack.push(predicate);
  do {
    if (tknStack.top() == tokens.front().type) {
      tknStack.pop();
      tokens.pop();
    }
    else {
      switch (tknStack.top()) {
        case predicate: this->Parsepredicate(); break;
        default:
          throw tokens.front();
          break;
      }
    }
  } while (tknStack.top() != Qmark);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    throw tokens.front();
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
    if (tknStack.top() == tokens.front().type) {
      tknStack.pop();
      tokens.pop();
    }
    else {
      switch (tknStack.top()) {
        case idList: this->ParseidList(); break;
        default:
          throw tokens.front();
          break;
      }
    }
  } while (tknStack.top() != RigPar);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    throw tokens.front();
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
    if (tknStack.top() == tokens.front().type) {
      tknStack.pop();
      tokens.pop();
    }
    else {
      switch (tknStack.top()) {
        case parameter: this->Parseparameter(); break;
        case parameterList: this->ParseparameterList(); break;
        default:
          throw tokens.front();
          break;
      }
    }
  } while (tknStack.top() != RigPar);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    throw tokens.front();
  }
}

void Parser::ParsepredicateList() {
  tknStack.pop();
  switch (tokens.front().type) {
    case Comma:
      tokens.pop();
      tknStack.push(predicateList);
      tknStack.push(predicate);
      this->Parsepredicate();
      this->ParsepredicateList();
      break;
    case Period:
      return;
      break;
    default:
      throw tokens.front();
      break;
  }
}

void Parser::ParseparameterList() {
  tknStack.pop();
  switch (tokens.front().type) {
    case Comma:
      tokens.pop();
      tknStack.push(parameterList);
      tknStack.push(parameter);
      this->Parseparameter();
      this->ParseparameterList();
      break;
    case RigPar:
      return;
      break;
    default:
      throw tokens.front();
      break;
  }
}

void Parser::ParsestringList() {
  tknStack.pop();
  switch (tokens.front().type) {
    case Comma:
      tokens.pop();
      tknStack.push(stringList);
      tknStack.push(String);
      if (tokens.front().type != tknStack.top()) {
        throw tokens.front();
      }
      else {
        tokens.pop();
        tknStack.pop();
      }
      this->ParsestringList();
      break;
    case RigPar:
      return;
      break;
    default:
      throw tokens.front();
      break;
  }
}

void Parser::ParseidList() {
  tknStack.pop();
  switch (tokens.front().type) {
    case Comma:
      tokens.pop();
      tknStack.push(idList);
      tknStack.push(ID);
      if (tokens.front().type != tknStack.top()) {
        throw tokens.front();
      }
      else {
        tokens.pop();
        tknStack.pop();
      }
      this->ParseidList();
      break;
    case RigPar:
      return;
      break;
    default:
      throw tokens.front();
      break;
  }
}

void Parser::Parseparameter() {
  tknStack.pop();
  switch(tokens.front().type) {
    case String:
      tokens.pop();
      break;
    case ID:
      tokens.pop();
      break;
    case LeftPar:
      tknStack.push(expression);
      this->Parseexpression();
      break;
    default:
      throw tokens.front();
      break;
  }
}

void Parser::Parseexpression() {
  tknStack.pop();
  tknStack.push(RigPar);
  tknStack.push(parameter);
  tknStack.push(op);
  tknStack.push(parameter);
  tknStack.push(LeftPar);
  do {
    if (tknStack.top() == tokens.front().type) {
      tknStack.pop();
      tokens.pop();
    }
    else {
      switch (tknStack.top()) {
        case parameter: this->Parseparameter(); break;
        case op: this->Parseoperator(); break;
        default:
          throw tokens.front();
          break;
      }
    }
  } while (tknStack.top() != RigPar);
  if (tknStack.top() == EndFile && tokens.empty()==false) {
    throw tokens.front();
  }
}

void Parser::Parseoperator() {
  tknStack.pop();
  switch (tokens.front().type) {
    case Add:
      tokens.pop();
      break;
    case Mult:
      tokens.pop();
      break;
    default:
      throw tokens.front();
      break;
  }
}
