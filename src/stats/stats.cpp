#include <iostream>
#include "stats.hpp"

std::list<Report*> BytecodeStats::analyze(std::list<ClassFile*>& classes) {
  std::list<Report*> reports;

  std::cout << "Classes " << classes.size() << std::endl;

  int max = 0;
  ClassFile* cls = nullptr;
  for (auto c : classes) {
    if (c->fields()->size() > max) {
      max = c->fields()->size();
      cls = c;
    }
  }

  if (cls) {
    std::cout << "Class with most fields: " << max << std::endl;
  }

  return reports;
}