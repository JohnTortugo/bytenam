#ifndef __METHODINFO_HPP__
#define __METHODINFO_HPP__

#include <vector>
using namespace std;

#include "attributeinfo.hpp"
#include "constantpool.hpp"

class MethodInfo {
private:
  friend class ClassFile;

  u2 _access_flags;
  u2 _name_index;
  u2 _descriptor_index;
  vector<AttributeInfo*>* _attributes;

  CPUtf8* _name;
  CPUtf8* _descriptor;

  void relocate(vector<ConstantPoolInfo*>* cp) {
    this->_name = (CPUtf8*) cp->at(_name_index);
    this->_descriptor = (CPUtf8*) cp->at(_descriptor_index);
    for (auto entry : *_attributes) entry->relocate(cp);
  }

public:
  MethodInfo(u2 access_flags, u2 name_index, u2 descriptor_index, vector<AttributeInfo*>* attributes) {
    this->_access_flags = access_flags;
    this->_name_index = name_index;
    this->_descriptor_index = descriptor_index;
    this->_attributes = attributes;
  }

  const string& name() {
    return _name->value();
  }

  const string& descriptor() {
    return _descriptor->value();
  }

  const string params() {
    auto beg = _descriptor->value().find('(');
    auto end = _descriptor->value().find(')');
    return _descriptor->value().substr(beg, end - beg + 1);
  }

  const string ret() {
    auto end = _descriptor->value().find(')');
    return _descriptor->value().substr(end+1);
  }

  const vector<AttributeInfo*>* attributes() {
    return _attributes;
  }
};

#endif // __METHODINFO_HPP__;