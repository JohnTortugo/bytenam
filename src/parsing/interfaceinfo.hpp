#ifndef __INTERFACEINFO_HPP__
#define __INTERFACEINFO_HPP__

#include <vector>
using namespace std;

#include "types.hpp"
#include "constantpool.hpp"

class InterfaceInfo {
private:
  u2 _interface_index;

  // Represents an interface that is a direct superinterface of the class or
  // interface type, in the left-to-right order given in the source for the
  // type.
  CPClass* _interface;

  void relocate(vector<ConstantPoolInfo*>* cp) {
    this->_interface = (CPClass*) cp->at(_interface_index);
  }

public:
  InterfaceInfo(u2 interface_index) {
    this->_interface_index = interface_index;
  }

  const string& name() {
    return _interface->name();
  }

  friend class ClassFile;
};

#endif // __INTERFACEINFO_HPP__;