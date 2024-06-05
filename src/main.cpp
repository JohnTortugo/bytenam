#include <iostream>
#include "parser.hpp"
using namespace std;

int main(int argc, char* argv[]) {
  BytecodeParser parser(new ifstream(argv[1], ios::binary));

  ClassFile* cls = parser.parse();

  return 0;
}