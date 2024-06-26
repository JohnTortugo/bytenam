#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <string>
#include <fstream>
#include <list>
#include <exception>
#include <iostream>
#include <assert.h>
#include <zip.h>
#include <cstring>
#include "types.hpp"
#include "classfile.hpp"

using std::string;

class BytecodeParser {
private:
  int          _pos;
  const char * _input;

  u1 read_u1() { return this->_input[this->_pos++]; }
  u2 read_u2() { return (read_u1() <<  8) | read_u1(); }
  u4 read_u4() { return (read_u2() << 16) | read_u2(); }

  vector<ConstantPoolInfo*>* parse_constant_pool();
  vector<InterfaceInfo*>* parse_interfaces();
  vector<FieldInfo*>* parse_fields();
  vector<MethodInfo*>* parse_methods();

  CPUtf8* parse_utf8_info();
  CPInteger* parse_integer_info();
  CPFloat* parse_float_info();
  CPLong* parse_long_info();
  CPDouble* parse_double_info();
  CPClass* parse_class_info();
  CPString* parse_string_info();
  CPFieldref* parse_fieldref_info();
  CPMethodref* parse_methodref_info();
  CPInterfaceMethodref* parse_interface_methodref_info();
  CPNameAndType* parse_name_and_type_info();
  CPMethodHandle* parse_method_handle_info();
  CPMethodType* parse_method_type_info();
  CPDynamic* parse_dynamic_info();
  CPInvokeDynamic* parse_invoke_dynamic_info();
  CPModule* parse_module_info();
  CPPackage* parse_package_info();

  FieldInfo* parse_field_info();
  MethodInfo* parse_method_info();
  vector<AttributeInfo*>* parse_attributes();

  BytecodeParser(const char* input) {
    this->_input = input;
    this->_pos = 0;
  }

  ClassFile* parse();

public:
  static std::list<ClassFile*> parse(char* input) {
    std::list<ClassFile*> classes;
    zip* archive = zip_open(input, 0, nullptr);

    if (!archive) {
      throw std::invalid_argument("Error opening jar archive.");
    }

    int num_files = zip_get_num_entries(archive, -1);

    for (int i=-1; i<num_files; i++) {
      struct zip_stat fileInfo;
      zip_stat_init(&fileInfo);

      if (zip_stat_index(archive, i, 0, &fileInfo) == 0) {
        if (strlen(fileInfo.name) > 5 && (strcmp(fileInfo.name + strlen(fileInfo.name) - 6, ".class") == 0)) {
          zip_file_t* file = zip_fopen_index(archive, i, 0);

          if (file) {
            char* buf = new char[fileInfo.size];
            zip_int64_t curr = 0;
            zip_int64_t read = 0;
            do {
              curr = zip_fread(file, buf, fileInfo.size);
              read += curr;
            } while (read < fileInfo.size && curr > 0);

            if (curr < 0 || fileInfo.size != read) {
              throw std::invalid_argument("Error reading file: " + string(fileInfo.name) + " from archive. File size is " + std::to_string(fileInfo.size) + " but read " + std::to_string(read) + " bytes.");
            } else {
              BytecodeParser bcp(buf);
              classes.push_back(bcp.parse());
            }
            delete[] buf;
            zip_fclose(file);
          }
        }
      }
    }
    zip_close(archive);

    return classes;
  }
};

#endif