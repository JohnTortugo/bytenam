#ifndef __ATTRIBUTEINFO_HPP__
#define __ATTRIBUTEINFO_HPP__

#include <vector>
#include "types.hpp"
using namespace std;

class AttributeInfo {
private:
  u2 attribute_name_index;
  vector<u1>* info;

public:
  AttributeInfo(u2 name_index, vector<u1>* info) {
    this->attribute_name_index = name_index;
    this->info = info;
  }
};

#endif // __ATTRIBUTEINFO_HPP__;