#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "parser.hpp"

ClassFile* BytecodeParser::parse() {
  auto magic = read_u4();
  auto minor = read_u2();
  auto major = read_u2();
  auto cp = parse_constant_pool();
  auto flags = read_u2();
  auto thiss = read_u2();
  auto super = read_u2();
  auto interfaces = parse_interfaces();
  auto fields = parse_fields();
  auto methods = parse_methods();
  auto attributes = parse_attributes();

  return new ClassFile(major, minor, flags, thiss, super, cp, interfaces, fields, methods, attributes);
}

vector<ConstantPoolInfo*>* BytecodeParser::parse_constant_pool() {
  auto cp_count = read_u2();
  auto cp = new vector<ConstantPoolInfo*>();

  cp->reserve(cp_count);
  cp->push_back(new ConstantPoolInfo());

  for (int i=1; i<cp_count; i++) {
    u1 tag = read_u1();

    switch (tag) {
      case  1: cp->push_back(parse_utf8_info()); break;
      case  3: cp->push_back(parse_integer_info()); break;
      case  4: cp->push_back(parse_float_info()); break;
      case  5: cp->push_back(parse_long_info()); cp->push_back(new ConstantPoolInfo()); i++; break;
      case  6: cp->push_back(parse_double_info()); cp->push_back(new ConstantPoolInfo()); i++; break;
      case  7: cp->push_back(parse_class_info()); break;
      case  8: cp->push_back(parse_string_info()); break;
      case  9: cp->push_back(parse_fieldref_info()); break;
      case 10: cp->push_back(parse_methodref_info()); break;
      case 11: cp->push_back(parse_interface_methodref_info()); break;
      case 12: cp->push_back(parse_name_and_type_info()); break;
      case 15: cp->push_back(parse_method_handle_info()); break;
      case 16: cp->push_back(parse_method_type_info()); break;
      case 17: cp->push_back(parse_dynamic_info()); break;
      case 18: cp->push_back(parse_invoke_dynamic_info()); break;
      case 19: cp->push_back(parse_module_info()); break;
      case 20: cp->push_back(parse_package_info()); break;
    }
  }
  return cp;
}

vector<InterfaceInfo*>* BytecodeParser::parse_interfaces() {
  auto icount = read_u2();
  vector<InterfaceInfo*>* interfaces = new vector<InterfaceInfo*>();
  for (int i=0; i<icount; i++) {
    interfaces->push_back(new InterfaceInfo(read_u2()));
  }
  return interfaces;
}

vector<FieldInfo*>* BytecodeParser::parse_fields() {
  auto fcount = read_u2();
  vector<FieldInfo*>* fields = new vector<FieldInfo*>();
  for (int i=0; i<fcount; i++) {
    fields->push_back(parse_field_info());
  }
  return fields;
}

vector<MethodInfo*>* BytecodeParser::parse_methods() {
  auto mcount = read_u2();
  vector<MethodInfo*>* methods = new vector<MethodInfo*>();
  for (int i=0; i<mcount; i++) {
    methods->push_back(parse_method_info());
  }
  return methods;
}

CPUtf8* BytecodeParser::parse_utf8_info() {
  u2 length = read_u2();

  char* bytes = new char[length+1];
  for (int i=0; i<length; i++) {
    bytes[i] = read_u1();
  }
  bytes[length] = '\0';

  return new CPUtf8(bytes);
}

CPInteger* BytecodeParser::parse_integer_info() {
  return new CPInteger(read_u4());
}

CPFloat* BytecodeParser::parse_float_info() {
  return new CPFloat(read_u4());
}

CPLong* BytecodeParser::parse_long_info() {
  return new CPLong(read_u4(), read_u4());
}

CPDouble* BytecodeParser::parse_double_info() {
  return new CPDouble(read_u4(), read_u4());
}

CPClass* BytecodeParser::parse_class_info() {
  return new CPClass(read_u2());
}

CPString* BytecodeParser::parse_string_info() {
  return new CPString(read_u2());
}

CPFieldref* BytecodeParser::parse_fieldref_info() {
  return new CPFieldref(read_u2(), read_u2());
}

CPMethodref* BytecodeParser::parse_methodref_info() {
  return new CPMethodref(read_u2(), read_u2());
}

CPInterfaceMethodref* BytecodeParser::parse_interface_methodref_info() {
  return new CPInterfaceMethodref(read_u2(), read_u2());
}

CPNameAndType* BytecodeParser::parse_name_and_type_info() {
  return new CPNameAndType(read_u2(), read_u2());
}

CPMethodHandle* BytecodeParser::parse_method_handle_info() {
  u1 reference_kind = read_u1();
  u2 reference_index = read_u2();
  return new CPMethodHandle(reference_kind, reference_index);
}

CPMethodType* BytecodeParser::parse_method_type_info() {
  u2 descriptor_index = read_u2();
  return new CPMethodType(descriptor_index);
}

CPDynamic* BytecodeParser::parse_dynamic_info() {
  u2 bootstrap_method_attr_index = read_u2();
  u2 name_and_type_index = read_u2();
  return new CPDynamic(bootstrap_method_attr_index, name_and_type_index);
}

CPInvokeDynamic* BytecodeParser::parse_invoke_dynamic_info() {
  return new CPInvokeDynamic(read_u2(), read_u2());
}

CPModule* BytecodeParser::parse_module_info() {
  return new CPModule(read_u2());
}

CPPackage* BytecodeParser::parse_package_info() {
  return new CPPackage(read_u2());
}

FieldInfo* BytecodeParser::parse_field_info() {
  auto access_flags = read_u2(); 
  auto name_index = read_u2();
  auto descriptor_index = read_u2();
  auto attributes = parse_attributes();
  return new FieldInfo(access_flags, name_index, descriptor_index, attributes);
}

MethodInfo* BytecodeParser::parse_method_info() {
  u2 flags = read_u2();
  u2 name = read_u2();
  u2 descriptor = read_u2();
  vector<AttributeInfo*>* attributes = parse_attributes();
  return new MethodInfo(flags, name, descriptor, attributes);
}

vector<AttributeInfo*>* BytecodeParser::parse_attributes() {
  u2 acount = read_u2();
  vector<AttributeInfo*>* attributes = new vector<AttributeInfo*>();
  attributes->reserve(acount);

  for (int i=0; i<acount; i++) {
    u2 name = read_u2();
    u4 length = read_u4();
    vector<u1>* value = new vector<u1>(length);

    for (int i=0; i<length; i++) {
      value->push_back(read_u1());
    }

    attributes->push_back(new AttributeInfo(name, value));
  }

  return attributes;
}