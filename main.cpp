#include <iostream>
#include <string>
using namespace std;

#include "Tokens.h"
#include "Scanner.h"

int main(int argc, char* argv[]) {
	string fileName = argv[1];

	DatalogProgram* program = new DatalogProgram(fileName);

	return 0;
}
