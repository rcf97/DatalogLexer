#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "Scanner.h"
#include "Tokens.h"

Scanner::Scanner(string fileName) {
  this->fileName = fileName;
  this->file.open(this->fileName);
  this->curLine = 1;
}

Scanner::~Scanner() {
  this->tokens.clear();
}

vector<Tokens> Scanner::Read() {
  while (!file.eof()) {
    char next = file.peek();
    switch(next) {
      case '#':
        this->Comments();
        break;
      case '\'':
        this->Strings();
        break;
      default:
        if (isspace(next)) {
          if (next == '\n') {
            this->curLine++;
          }
          file.ignore();
        }
        else if (isalpha(next)) {
          this->KeyID();
        }
        else if (ispunct(next)) {
          this->Punct();
        }
        else if (isdigit(next)) {
          this->Undef(this->curLine);
          file.ignore();
        }
        else if (next == EOF) {
          Tokens* tknPtr;
          tknPtr = new Tokens("", this->curLine, EndFile);
          this->tokens.push_back(*tknPtr);
          return this->tokens;
        }
        else {
          this->Undef(this->curLine);
        }
        break;
    }
  }
  return this->tokens;
}

void Scanner::Comments() {
  int lineNum = this->curLine;
  string value = "";
  char next = file.get();
  value += next;
  if (file.peek() == '|') {
    next = file.get();
    value += next;
    while (file.peek() != EOF) {
      if (file.peek() == '|') {
        next = file.get();
        value += next;
        if (file.peek() == '#') {
          value += file.get();
          Tokens* tknPtr = new Tokens(value, lineNum, Comment);
          this->tokens.push_back(*tknPtr);
          return;
        }
      }
      if (file.peek() == '\n') {
        this->curLine++;
      }
      next = file.get();
      value += next;
    }
    if (file.peek() == EOF) {
      this->Undef(lineNum, value);
      Tokens* tknPtr = new Tokens("", this->curLine, EndFile);
      this->tokens.push_back(*tknPtr);
    }
  }
  else {
    while (file.peek() != EOF && file.peek() != '\n') {
      value += file.get();
    }
    Tokens* tknPtr = new Tokens(value, lineNum, Comment);
    this->tokens.push_back(*tknPtr);
  }
}

void Scanner::Punct() {
  char punc = file.peek();
  string punct(1,punc);
  Tokens* tknPtr;
  switch(punc) {
    case ',':
      tknPtr = new Tokens(punct, this->curLine, Comma);
      this->tokens.push_back(*tknPtr);
      break;
    case '.':
      tknPtr = new Tokens(punct, this->curLine, Period);
      this->tokens.push_back(*tknPtr);
      break;
    case '?':
      tknPtr = new Tokens(punct, this->curLine, Qmark);
      this->tokens.push_back(*tknPtr);
      break;
    case '(':
      tknPtr = new Tokens(punct, this->curLine, LeftPar);
      this->tokens.push_back(*tknPtr);
      break;
    case ')':
      tknPtr = new Tokens(punct, this->curLine, RigPar);
      this->tokens.push_back(*tknPtr);
      break;
    case ':':
      file.ignore();
      if (file.peek() == '-') {
        punct += file.peek();
        tknPtr = new Tokens(punct, this->curLine, ColonDash);
        this->tokens.push_back(*tknPtr);
      }
      else {
        tknPtr = new Tokens(punct, this->curLine, Colon);
        this->tokens.push_back(*tknPtr);
        file.unget();
      }
      break;
    case '*':
      tknPtr = new Tokens(punct, this->curLine, Mult);
      this->tokens.push_back(*tknPtr);
      break;
    case '+':
      tknPtr = new Tokens(punct, this->curLine, Add);
      this->tokens.push_back(*tknPtr);
      break;
    default:
      this->Undef(this->curLine);
  }
  file.ignore();
}

void Scanner::Undef(int lineNum, string value) {
  if (!value.empty()) {
    Tokens* tknPtr = new Tokens(value, lineNum, Undefined);
    this->tokens.push_back(*tknPtr);
    return;
  }

  value += file.get();
  Tokens* tknPtr = new Tokens(value, lineNum, Undefined);
  this->tokens.push_back(*tknPtr);
  file.unget();
  return;
}

void Scanner::KeyID() {
  string value = "";
  char next = file.peek();
  while (!isspace(next) && !ispunct(next) && !file.eof()) {
    next = file.get();
    value+=next;
    next = file.peek();
  }
  Tokens* tknPtr;
  if (value == "Queries") {
    tknPtr = new Tokens(value, this->curLine, Queries);
  }
  else if (value == "Schemes") {
    tknPtr = new Tokens(value, this->curLine, Schemes);
  }
  else if (value == "Rules") {
    tknPtr = new Tokens(value, this->curLine, Rules);
  }
  else if (value == "Facts") {
    tknPtr = new Tokens(value, this->curLine, Facts);
  }
  else {
    tknPtr = new Tokens(value, this->curLine, ID);
  }
  this->tokens.push_back(*tknPtr);
}

void Scanner::Strings() {
  int lineNum = this->curLine;
  string value = "";
  value += file.get();
  while (file.peek() != EOF) {
    if (file.peek() == '\'') {
      value += file.get();
      if (file.peek() != '\'') {
        Tokens* tknPtr = new Tokens(value, lineNum, String);
        this->tokens.push_back(*tknPtr);
        return;
      }
    }
    if (file.peek() == '\n') {
      this->curLine++;
    }
    value += file.get();
  }
  if (file.peek() == EOF) {
    this->Undef(lineNum, value);
    Tokens* tknPtr = new Tokens("", this->curLine, EndFile);
    this->tokens.push_back(*tknPtr);
  }
}

void Scanner::Print() {
  for (unsigned int i = 0; i < tokens.size(); i++) {
    cout << tokens.at(i).ToString() << endl;
  }
  cout << "Total Tokens = " << tokens.size() << endl;
}

vector<Tokens> Scanner::GetTokens() {
  return this->tokens;
}
