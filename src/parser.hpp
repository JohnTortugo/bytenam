#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <string>
#include <fstream>
#include "types.hpp"
#include "classfile.hpp"

using std::string;

class BytecodeParser {
private:
  std::ifstream* _input;

  u1 read_u1() const { u1 holder = 0; _input->read((char*)&holder, sizeof(u1)); return holder; }
  u2 read_u2() const { return (read_u1() <<  8) | read_u1(); }
  u4 read_u4() const { return (read_u2() << 16) | read_u2(); }

  void parse_utf8_info();
  void parse_integer_info();
  void parse_float_info();
  void parse_long_info();
  void parse_double_info();
  void parse_class_info();
  void parse_string_info();
  void parse_fieldref_info();
  void parse_methodref_info();
  void parse_interface_methodref_info();
  void parse_name_and_type_info();
  void parse_method_handle_info();
  void parse_method_type_info();
  void parse_dynamic_info();
  void parse_invoke_dynamic_info();
  void parse_module_info();
  void parse_package_info();
  void parse_field_info();
  void parse_method_info();
  void parse_attribute_info();

public:
  BytecodeParser(std::ifstream* input) {
    this->_input = input;
  }

  ClassFile* parse();
};

#endif