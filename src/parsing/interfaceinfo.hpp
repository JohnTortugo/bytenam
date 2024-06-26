#ifndef __INTERFACEINFO_HPP__
#define __INTERFACEINFO_HPP__

#include "types.hpp"

class InterfaceInfo {
private:
  u2     interface_index;
public:
  InterfaceInfo(u2 interface_index) {
    this->interface_index = interface_index;
  }
};

#endif // __INTERFACEINFO_HPP__;