#include <iostream>
#include <vector>
#include "parsing/parser.hpp"
#include "stats/stats.hpp"
using namespace std;

int main(int argc, char* argv[]) {
  auto classes = BytecodeParser::parse(argv[1]);
  auto rep     = BytecodeStats::analyze(classes); 

  // Number of classes
  // Number of methods per class
  // Number of fields per class
  // Number of interfaces per class
  // Number of locals per class
  // Number of equals methods
  // Number of hashcode methods
  // Number of toString methods
  // Number of default constructors
  // Number of classes in the hierarchy
  // Bytecode histogram
  // Average number of methods throwing an exception

  return 0;
}