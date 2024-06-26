#ifndef __REPORT_H__
#define __REPORT_H__

#include <string>
#include <vector>
#include <utility>

using std::string;
using std::vector;
using std::pair;

class Report {
private:
  string _name;
  string _desc;
  vector<pair<string, string>> _results;

public:
  virtual void print() = 0;
};

#endif // __REPORT_H__