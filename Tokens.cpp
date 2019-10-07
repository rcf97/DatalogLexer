#include <string>
#include <iostream>
#include "Tokens.h"
using namespace std;

Tokens::Tokens(string value, int line, TokenType type) {     //Constructor
  this->value = value;
  this->line = line;
  this->type = type;
}

string Tokens::ToString() {
  string out = "";
  out.reserve(100);
  out += "(";
  switch(this->type) {
    case ID: out += "ID"; break;
    case Comma: out += "COMMA"; break;
    case Period: out += "PERIOD"; break;
    case Qmark: out += "Q_MARK"; break;
    case LeftPar: out += "LEFT_PAREN"; break;
    case RigPar: out += "RIGHT_PAREN"; break;
    case Colon: out += "COLON"; break;
    case ColonDash: out += "COLON_DASH"; break;
    case Mult: out += "MULTIPLY"; break;
    case Add: out += "ADD"; break;
    case Schemes: out += "SCHEMES"; break;
    case Facts: out += "FACTS"; break;
    case Rules: out += "RULES"; break;
    case Queries: out += "QUERIES"; break;
    case String: out += "STRING"; break;
    case Comment: out += "COMMENT"; break;
    case Undefined: out += "UNDEFINED"; break;
    case EndFile: out += "EOF"; break;
    default: break;
  }
  out += ",\"";
  out += this->value;
  out += "\",";
  out += to_string(this->line);
  out += ")";
  return out;
}
