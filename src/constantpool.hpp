#ifndef __CONSTANTPOOL_HPP__
#define __CONSTANTPOOL_HPP__

#include "types.hpp"

class ConstantPoolInfo {
protected:
  u1 tag;
};

class CPUtf8 : public ConstantPoolInfo {
private:
  u1 tag;
  u2 length;
  u1* bytes;  
};

class CPInteger : public ConstantPoolInfo {
private: 
  u1 tag;
  u4 bytes;
};

class CPFloat : public ConstantPoolInfo{
private: 
  u1 tag;
  u4 bytes;
};

class CPLong : public ConstantPoolInfo{
private: 
  u1 tag;
  u4 high_bytes;
  u4 low_bytes;
};

class CPDouble : public ConstantPoolInfo{
private: 
  u1 tag;
  u4 high_bytes;
  u4 low_bytes;
};

class CPClass : public ConstantPoolInfo{
private: 
  u1 tag;
  u2 name_index;
};

class CPString : public ConstantPoolInfo{
private: 
  u1 tag;
  u2 string_index;  
};

class CPFieldref : public ConstantPoolInfo{
private: 
  u1 tag;
  u2 class_index;
  u2 name_and_type_index;  
};

class CPMethodref : public ConstantPoolInfo{
private: 
  u1 tag;
  u2 class_index;
  u2 name_and_type_index; 
};

class CPInterfaceMethodref : public ConstantPoolInfo{
private: 
  u1 tag;
  u2 class_index;
  u2 name_and_type_index; 
};

class CPNameAndType : public ConstantPoolInfo{
private: 
  u1 tag;
  u2 name_index;
  u2 descriptor_index; 
};

class CPMethodHandle : public ConstantPoolInfo{
private: 
  u1 tag;
  u1 reference_kind;
  u2 reference_index;  
};

class CPMethodType : public ConstantPoolInfo{
private: 
  u1 tag;
  u2 descriptor_index;  
};

class CPDynamic : public ConstantPoolInfo{
private: 
  u1 tag;
  u2 bootstrap_method_attr_index;
  u2 name_and_type_index;  
};

class CPInvokeDynamic : public ConstantPoolInfo{
private: 
  u1 tag;
  u2 bootstrap_method_attr_index;
  u2 name_and_type_index;  
};

class CPModule : public ConstantPoolInfo{
private: 
  u1 tag;
  u2 name_index; 
};

class CPPackage : public ConstantPoolInfo{
private: 
  u1 tag;
  u2 name_index; 
};

#endif // __CONSTANTPOOL_HPP__