#ifndef __FIELDINFO_HPP__
#define __FIELDINFO_HPP__

#include <vector>
#include "types.hpp"
#include "attributeinfo.hpp"
using namespace std;

class FieldInfo {
private:
  u2 _access_flags;
  u2 _name_index;
  u2 _descriptor_index;
  vector<AttributeInfo*>* _attributes;

public:
  FieldInfo(u2 access_flags, u2 name_index, u2 descriptor_index, vector<AttributeInfo*>* attributes) {
    this->_access_flags = access_flags;
    this->_name_index = name_index;
    this->_descriptor_index = descriptor_index;
    this->_attributes = attributes;
  }

  u2 access_flags() { return _access_flags; }
  u2 name_index() { return _name_index; }
  u2 descriptor_index() { return _descriptor_index; }
  vector<AttributeInfo*>* attributes() { return _attributes; }
};

#endif // __FIELDINFO_HPP__