#ifndef __FIELDINFO_HPP__
#define __FIELDINFO_HPP__

#include "types.hpp"
#include "attributeinfo.hpp"

class FieldInfo {
private:
  u2                 access_flags;
  u2                 name_index;
  u2                 descriptor_index;
  u2                 attributes_count;
  AttributeInfo*     attributes;
};

#endif // __FIELDINFO_HPP__