#include <iostream>
#include "stats.hpp"

std::list<Report*> BytecodeStats::analyze(std::list<ClassFile*>& classes) {
  std::list<Report*> reports;

  for (auto c : classes) {
    cout << "class " << c->name(); 

    if (c->interfaces()->size() > 0) {
      cout << " implements";
      for (auto i : *c->interfaces()) {
        cout << " " << i->name();
      }
    }
    cout << " { " << endl;

    if (c->fields()->size() > 0) {
      for (auto f : *c->fields()) {
        cout << "  " << f->descriptor() << " " << f->name() << ";" << endl;
        for (auto a : *f->attributes()) {
          cout << "    " << a->name() << " : " << endl;
        }
      }
      cout << endl;
    }

    for (auto m : *c->methods()) {
      cout << "  " << m->ret() << " " << m->name() << m->params() << " {" << endl;
      for (auto a : *m->attributes()) {
        cout << "    " << a->name() << " --> " << endl;
      }
      cout << "  }" << endl << endl;
    }


    cout << "} " << endl;
  }

  return reports;
}