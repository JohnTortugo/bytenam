#ifndef __METHODINFO_HPP__
#define __METHODINFO_HPP__

#include "attributeinfo.hpp"

class MethodInfo {
private:
  u2                 access_flags;
  u2                 name_index;
  u2                 descriptor_index;
  u2                 attributes_count;
  AttributeInfo*     attributes;
};

#endif // __METHODINFO_HPP__;