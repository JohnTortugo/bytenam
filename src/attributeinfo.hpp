#ifndef __ATTRIBUTEINFO_HPP__
#define __ATTRIBUTEINFO_HPP__

#include "types.hpp"

class AttributeInfo {
private:
  u2     attribute_name_index;
  u4     attribute_length;
  u1*    info;
};

#endif // __ATTRIBUTEINFO_HPP__;