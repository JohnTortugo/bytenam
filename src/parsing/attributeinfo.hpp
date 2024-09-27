#ifndef __ATTRIBUTEINFO_HPP__
#define __ATTRIBUTEINFO_HPP__

#include <vector>
#include "types.hpp"
#include "constantpool.hpp"
using namespace std;

class AttributeInfo {
private:
  friend class ClassFile;
  friend class MethodInfo;
  friend class FieldInfo;

  u2 _attribute_name_index;
  vector<u1>* _info;
  CPUtf8* _name;

  void relocate(vector<ConstantPoolInfo*>* cp) {
    this->_name = (CPUtf8*) cp->at(_attribute_name_index);
  }

public:
  AttributeInfo(u2 name_index, vector<u1>* info) {
    this->_attribute_name_index = name_index;
    this->_info = info;
  }

  const string& name() {
    return _name->value();
  }
};

#endif // __ATTRIBUTEINFO_HPP__;