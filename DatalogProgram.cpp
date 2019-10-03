#include <iostream>
#include <vector>
using namespace std;

DatalogProgram::DatalogProgram(string fileName) {
  this->scnPtr = new Scanner(filename);
  this->tokens = this->scnPtr->Read();
  this->parsePtr = new Parse(this->tokens);
}
