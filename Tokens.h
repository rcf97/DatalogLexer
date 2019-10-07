#pragma once
#include <string>
using namespace std;

enum TokenType { ID, EndFile, Comment, Comma, Period, Qmark, LeftPar,
	RigPar, Colon,  ColonDash, Mult, Add, Schemes, Facts, Rules,
	Queries, String, Undefined,
	scheme, schemeList, factList, fact, rule, ruleList, query,
	queryList, idList, stringList, headPredicate, predicate,
	predicateList, parameterList, parameter, expression, op};

class Tokens {
private:
	string value;
	int line;
	TokenType type;
	friend class Parser;
	friend class Parameter;
	friend class Expression;
public:
	Tokens(string value, int line, TokenType type);
	string ToString();
};
