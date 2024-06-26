#ifndef __STATS_HPP__
#define __STATS_HPP__

#include <list>
#include "report.hpp"
#include "../parsing/classfile.hpp"

class BytecodeStats  {
public:
  static std::list<Report*> analyze(std::list<ClassFile*>& classes);
};

#endif // __STATS_H__