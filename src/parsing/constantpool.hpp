#ifndef __CONSTANTPOOL_HPP__
#define __CONSTANTPOOL_HPP__

#include <vector>
#include "types.hpp"
using namespace std;

class ConstantPoolInfo { };

class CPUtf8 : public ConstantPoolInfo {
private:
  vector<u1>* bytes; 
public:
  CPUtf8(vector<u1>* bytes) {
    this->bytes = bytes;
  }
};

class CPInteger : public ConstantPoolInfo {
private: 
  u4 bytes;
public:
  CPInteger(u4 bytes) {
    this->bytes = bytes;
  }
};

class CPFloat : public ConstantPoolInfo{
private: 
  u4 bytes;
public:
  CPFloat(u4 bytes) {
    this->bytes = bytes;
  }
};

class CPLong : public ConstantPoolInfo{
private: 
  u4 high_bytes;
  u4 low_bytes;
public:
  CPLong(u4 high_bytes, u4 low_bytes) {
    this->high_bytes = high_bytes;
    this->low_bytes = low_bytes;
  }
};

class CPDouble : public ConstantPoolInfo{
private: 
  u4 high_bytes;
  u4 low_bytes;
public:
  CPDouble(u4 high_bytes, u4 low_bytes) {
    this->high_bytes = high_bytes;
    this->low_bytes = low_bytes;
  }
};

class CPClass : public ConstantPoolInfo{
private: 
  u2 name_index;
public:
  CPClass(u2 name_index) {
    this->name_index = name_index;
  }
};

class CPString : public ConstantPoolInfo{
private: 
  u2 string_index;  
public:
  CPString(u2 string_index) {
    this->string_index = string_index;
  }
};

class CPFieldref : public ConstantPoolInfo{
private: 
  u2 class_index;
  u2 name_and_type_index;  
public:
  CPFieldref(u2 class_index, u2 name_and_type_index) {
    this->class_index = class_index;
    this->name_and_type_index = name_and_type_index;
  }
};

class CPMethodref : public ConstantPoolInfo{
private: 
  u2 class_index;
  u2 name_and_type_index; 
public:
  CPMethodref(u2 class_index, u2 name_and_type_index) {
    this->class_index = class_index;
    this->name_and_type_index = name_and_type_index;
  }
};

class CPInterfaceMethodref : public ConstantPoolInfo{
private: 
  u2 class_index;
  u2 name_and_type_index; 
public:
  CPInterfaceMethodref(u2 class_index, u2 name_and_type_index) {
    this->class_index = class_index;
    this->name_and_type_index = name_and_type_index;
  }
};

class CPNameAndType : public ConstantPoolInfo{
private: 
  u2 name_index;
  u2 descriptor_index; 
public:
  CPNameAndType(u2 name_index, u2 descriptor_index) {
    this->name_index = name_index;
    this->descriptor_index = descriptor_index;
  }
};

class CPMethodHandle : public ConstantPoolInfo{
private: 
  u1 reference_kind;
  u2 reference_index;  
public:
  CPMethodHandle(u1 reference_kind, u2 reference_index) {
    this->reference_kind = reference_kind;
    this->reference_index = reference_index;
  }
};

class CPMethodType : public ConstantPoolInfo{
private: 
  u2 descriptor_index;  
public:
  CPMethodType(u2 descriptor_index) {
    this->descriptor_index = descriptor_index;
  }
};

class CPDynamic : public ConstantPoolInfo{
private: 
  u2 bootstrap_method_attr_index;
  u2 name_and_type_index;  
public:
  CPDynamic(u2 bootstrap_method_attr_index, u2 name_and_type_index) {
    this->bootstrap_method_attr_index = bootstrap_method_attr_index;
    this->name_and_type_index = name_and_type_index;
  }
};

class CPInvokeDynamic : public ConstantPoolInfo{
private: 
  u2 bootstrap_method_attr_index;
  u2 name_and_type_index;  
public:
  CPInvokeDynamic(u2 bootstrap_method_attr_index, u2 name_and_type_index) {
    this->bootstrap_method_attr_index = bootstrap_method_attr_index;
    this->name_and_type_index = name_and_type_index;
  }
};

class CPModule : public ConstantPoolInfo{
private: 
  u2 name_index; 
public:
  CPModule(u2 name_index) {
    this->name_index = name_index;
  }
};

class CPPackage : public ConstantPoolInfo{
private: 
  u2 name_index; 
public:
  CPPackage(u2 name_index) {
    this->name_index = name_index;
  }
};

#endif // __CONSTANTPOOL_HPP__