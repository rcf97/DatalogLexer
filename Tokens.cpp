#include <string>

#include "Tokens.h"
using namespace std;

Tokens::Tokens(string value, int line, TokenType type) {            //Constructor
  this->value = value;
  this->line = line;
  this->type = type;
}

string Tokens::ToString() {
  string value = "";
  value += "(";
  switch(this->type) {
    case ID: value += "ID"; break;
    case Comma: value += "COMMA"; break;
    case Period: value += "PERIOD"; break;
    case Qmark: value += "Q_MARK"; break;
    case LeftPar: value += "LEFT_PAREN"; break;
    case RigPar: value += "RIGHT_PAREN"; break;
    case Colon: value += "COLON"; break;
    case ColonDash: value += "COLON_DASH"; break;
    case Mult: value += "MULTIPLY"; break;
    case Add: value += "ADD"; break;
    case Schemes: value += "SCHEMES"; break;
    case Facts: value += "FACTS"; break;
    case Rules: value += "RULES"; break;
    case Queries: value += "QUERIES"; break;
    case String: value += "STRING"; break;
    case Comment: value += "COMMENT"; break;
    case Undefined: value += "UNDEFINED"; break;
    case EndFile: value += "EOF"; break;
    default: break;
  }
  value += ",\"";
  value += this->value;
  value += "\",";
  value += to_string(this->line);
  value += ")";
  return value;
}
