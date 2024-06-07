#include <fstream>
#include <iostream>

#include "parser.hpp"

ClassFile* BytecodeParser::parse() {
  int cp_count = 0, icount = 0, mcount = 0, fcount = 0, acount = 0;

  std::cout << "Bytes are: ";
  std::cout << "magic: "   << std::hex << read_u4() << std::endl;
  std::cout << "minor: "   << std::hex << read_u2() << std::endl;
  std::cout << "major:"    << std::hex << read_u2() << std::endl;
  std::cout << "cp_count:" << std::hex << (cp_count = read_u2()) << std::endl;

  for (int i=1; i<cp_count; i++) {
    u1 tag = read_u1();
    std::cout << "tag: '" << (int) tag << "'" << std::endl;

    switch (tag) {
      case  1: parse_utf8_info(); break;
      case  3: parse_integer_info(); break;
      case  4: parse_float_info(); break;
      case  5: parse_long_info(); i++; break;
      case  6: parse_double_info(); i++; break;
      case  7: parse_class_info(); break;
      case  8: parse_string_info(); break;
      case  9: parse_fieldref_info(); break;
      case 10: parse_methodref_info(); break;
      case 11: parse_interface_methodref_info(); break;
      case 12: parse_name_and_type_info(); break;
      case 15: parse_method_handle_info(); break;
      case 16: parse_method_type_info(); break;
      case 17: parse_dynamic_info(); break;
      case 18: parse_invoke_dynamic_info(); break;
      case 19: parse_module_info(); break;
      case 20: parse_package_info(); break;
    }
  }

  std::cout << "flags:"   << std::hex << read_u2() << std::endl;
  std::cout << "this:"    << std::hex << read_u2() << std::endl;
  std::cout << "super:"   << std::hex << read_u2() << std::endl;
  std::cout << "icount:"  << std::hex << (icount = read_u2()) << std::endl;

  for (int i=0; i<icount; i++) {
    read_u2();
  }


  std::cout << "fcount:"  << std::hex << (fcount = read_u2()) << std::endl;
  for (int i=0; i<fcount; i++) {
    parse_field_info();
  }

  std::cout << "mcount:"  << std::hex << (mcount = read_u2()) << std::endl;
  for (int i=0; i<mcount; i++) {
    parse_method_info();
  }

  std::cout << "acount:"  << std::hex << (acount = read_u2()) << std::endl;
  for (int i=0; i<acount; i++) {
    parse_attribute_info();
  }

  return nullptr;
}

void BytecodeParser::parse_utf8_info() {
  u2 length = read_u2();
  for (int i=0; i<length; i++) {
    read_u1();
  }
}

void BytecodeParser::parse_integer_info() {
  read_u4();
}

void BytecodeParser::parse_float_info() {
  read_u4();
}

void BytecodeParser::parse_long_info() {
  read_u4();
  read_u4();
}

void BytecodeParser::parse_double_info() {
  read_u4();
  read_u4();
}

void BytecodeParser::parse_class_info() {
  u2 name_index = read_u2();
}

void BytecodeParser::parse_string_info() {
  u2 string_index = read_u2();
}

void BytecodeParser::parse_fieldref_info() {
  u2 class_index = read_u2();
  u2 name_and_type_index = read_u2();
}

void BytecodeParser::parse_methodref_info() {
  u2 class_index = read_u2();
  u2 name_and_type_index = read_u2();
}

void BytecodeParser::parse_interface_methodref_info() {
  u2 class_index = read_u2();
  u2 name_and_type_index = read_u2();
}

void BytecodeParser::parse_name_and_type_info() {
  u2 name_index = read_u2();
  u2 descriptor_index = read_u2();
}

void BytecodeParser::parse_method_handle_info() {
  u1 reference_kind = read_u1();
  u2 reference_index = read_u2();
}

void BytecodeParser::parse_method_type_info() {
  u2 descriptor_index = read_u2();
}

void BytecodeParser::parse_dynamic_info() {
  u2 bootstrap_method_attr_index = read_u2();
  u2 name_and_type_index = read_u2();
}

void BytecodeParser::parse_invoke_dynamic_info() {
  u2 bootstrap_method_attr_index = read_u2();
  u2 name_and_type_index = read_u2();
}

void BytecodeParser::parse_module_info() {
  u2 name_index = read_u2();
}

void BytecodeParser::parse_package_info() {
  u2 name_index = read_u2();
}

void BytecodeParser::parse_field_info() {
  u2 flags = read_u2();
  u2 name = read_u2();
  u2 descriptor = read_u2();
  u2 acount = read_u2();

  for (int i=0; i<acount; i++) {
    parse_attribute_info();
  }
}

void BytecodeParser::parse_method_info() {
  u2 flags = read_u2();
  u2 name = read_u2();
  u2 descriptor = read_u2();
  u2 acount = read_u2();

  for (int i=0; i<acount; i++) {
    parse_attribute_info();
  }
}

void BytecodeParser::parse_attribute_info() {
  u2 name = read_u2();
  u4 length = read_u4();

  for (int i=0; i<length; i++) {
    read_u1();
  }
}