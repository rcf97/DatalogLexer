#include <iostream>
#include <string>
using namespace std;

#include "DatalogProgram.h"

int main(int argc, char* argv[]) {
	string fileName = argv[1];

	DatalogProgram* program;
	program = new DatalogProgram(fileName);
	delete program;

	return 0;
}
