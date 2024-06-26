#ifndef __METHODINFO_HPP__
#define __METHODINFO_HPP__

#include "attributeinfo.hpp"

class MethodInfo {
private:
  u2                 access_flags;
  u2                 name_index;
  u2                 descriptor_index;
  vector<AttributeInfo*>* attributes;
public:
  MethodInfo(u2 access_flags, u2 name_index, u2 descriptor_index, vector<AttributeInfo*>* attributes) {
    this->access_flags = access_flags;
    this->name_index = name_index;
    this->descriptor_index = descriptor_index;
    this->attributes = attributes;
  }
};

#endif // __METHODINFO_HPP__;