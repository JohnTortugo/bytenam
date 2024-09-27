#ifndef __CLASSFILE_HPP__
#define __CLASSFILE_HPP__

#include <vector>
using namespace std;

#include "types.hpp"
#include "fieldinfo.hpp"
#include "methodinfo.hpp"
#include "attributeinfo.hpp"
#include "constantpool.hpp"
#include "interfaceinfo.hpp"

class ClassFile {
private:
  u2 _minor_version;
  u2 _major_version;
  u2 _access_flags;
  u2 _this_class;
  u2 _super_class;

  vector<ConstantPoolInfo*>* _constant_pool;
  vector<InterfaceInfo*>* _interfaces;
  vector<FieldInfo*>* _fields;
  vector<MethodInfo*>* _methods;
  vector<AttributeInfo*>* _attributes;

  // This will populate the objects with a copy of their actual data
  // based on the index that they point to in the constant pool.
  void relocate() {
    for (auto entry : *_constant_pool) entry->relocate(this->_constant_pool);
    for (auto entry : *_interfaces) entry->relocate(this->_constant_pool);
    for (auto entry : *_fields) entry->relocate(this->_constant_pool);
    for (auto entry : *_methods) entry->relocate(this->_constant_pool);
    for (auto entry : *_attributes) entry->relocate(this->_constant_pool);
  }

public:
  ClassFile(u2 major, u2 minor, u2 flags, u2 tclass, u2 sclass, 
            vector<ConstantPoolInfo*>* cp, vector<InterfaceInfo*>* interfaces,
            vector<FieldInfo*>* fields, vector<MethodInfo*>* methods,
            vector<AttributeInfo*>* attributes) {

    this->_major_version = major;
    this->_minor_version = minor;
    this->_access_flags = flags;
    this->_this_class = tclass;
    this->_super_class = sclass;
    this->_constant_pool = cp;
    this->_interfaces = interfaces;
    this->_fields = fields;
    this->_methods = methods;
    this->_attributes = attributes;

    relocate();
  }

  const string& name() {
    auto cinfo = (CPClass*)_constant_pool->at(_this_class);
    return cinfo->name();
  }

  vector<FieldInfo*>* fields() { return _fields; }
  vector<MethodInfo*>* methods() { return _methods; }
  vector<InterfaceInfo*>* interfaces() { return _interfaces; }
};

#endif // __CLASSFILE_HPP__