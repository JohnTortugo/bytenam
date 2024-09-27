#ifndef __CONSTANTPOOL_HPP__
#define __CONSTANTPOOL_HPP__

#include <vector>
#include <string>
#include "types.hpp"
using namespace std;

class ConstantPoolInfo { 
protected:
  friend class ClassFile;
  virtual void relocate(vector<ConstantPoolInfo*>* cp) { }
};

class CPUtf8 : public ConstantPoolInfo {
private:
  string val; 

public:
  CPUtf8(const char* bytes) {
    this->val = string(bytes);
  }

  const string& value() {
    return this->val;
  }
};

class CPInteger : public ConstantPoolInfo {
private: 
  u4 bytes;
public:
  CPInteger(u4 bytes) {
    this->bytes = bytes;
  }

  int value() {
    return bytes;
  }
};

class CPFloat : public ConstantPoolInfo{
private: 
  u4 bytes;
public:
  CPFloat(u4 bytes) {
    this->bytes = bytes;
  }

  float value() {
    return (float) bytes;
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

  long value() {
    return ((long) high_bytes << 32) | low_bytes;
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

  double value() {
    return (double) (((long) high_bytes << 32) | low_bytes);
  }
};

class CPClass : public ConstantPoolInfo{
private: 
  u2 name_index;
  CPUtf8* name_utf8 = nullptr;

  void relocate(vector<ConstantPoolInfo*>* cp) {
    this->name_utf8 = (CPUtf8*) cp->at(name_index);
  }
public:
  CPClass(u2 name_index) {
    this->name_index = name_index;
  }

  const string& name() {
    return this->name_utf8->value();
  }
};

class CPString : public ConstantPoolInfo {
private: 
  u2 string_index;
  CPUtf8* str = nullptr;

  void relocate(vector<ConstantPoolInfo*>* cp) {
    this->str = (CPUtf8*) cp->at(string_index);
  }

public:
  CPString(u2 string_index) {
    this->string_index = string_index;
  }

  const string& value() {
    return this->str->value();
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
  CPUtf8* name_utf8 = nullptr;
  CPUtf8* descriptor_utf8 = nullptr;

  void relocate(vector<ConstantPoolInfo*>* cp) {
    this->name_utf8 = (CPUtf8*) cp->at(name_index);
    this->descriptor_utf8 = (CPUtf8*) cp->at(descriptor_index);
  }
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
  CPUtf8* name_utf8 = nullptr;

  void relocate(vector<ConstantPoolInfo*>* cp) {
    this->name_utf8 = (CPUtf8*) cp->at(descriptor_index);
  }
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
  CPUtf8* name_utf8 = nullptr;

  void relocate(vector<ConstantPoolInfo*>* cp) {
    this->name_utf8 = (CPUtf8*) cp->at(name_index);
  }
public:
  CPModule(u2 name_index) {
    this->name_index = name_index;
  }
};

class CPPackage : public ConstantPoolInfo{
private: 
  u2 name_index; 
  CPUtf8* name_utf8 = nullptr;

  void relocate(vector<ConstantPoolInfo*>* cp) {
    this->name_utf8 = (CPUtf8*) cp->at(name_index);
  }
public:
  CPPackage(u2 name_index) {
    this->name_index = name_index;
  }
};

#endif // __CONSTANTPOOL_HPP__