#ifndef __CLASSFILE_HPP__
#define __CLASSFILE_HPP__

#include "types.hpp"
#include "fieldinfo.hpp"
#include "methodinfo.hpp"
#include "attributeinfo.hpp"
#include "constantpool.hpp"

class ClassFile {
private:
  u4                  magic;
  u2                  minor_version;
  u2                  major_version;
  u2                  constant_pool_count;
  ConstantPoolInfo*   constant_pool;
  u2                  access_flags;
  u2                  this_class;
  u2                  super_class;
  u2                  interfaces_count;
  u2*                 interfaces;
  u2                  fields_count;
  FieldInfo*          fields;
  u2                  methods_count;
  MethodInfo*         methods;
  u2                  attributes_count;
  AttributeInfo*      attributes;
};



#endif // __CLASSFILE_HPP__