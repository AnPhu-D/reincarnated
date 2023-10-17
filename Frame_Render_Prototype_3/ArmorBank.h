#ifndef ARMOR_BANK
#define ARMOR_BANK

#include <iostream>
#include <string>
#include <vector>
#include "armorItem.h"

class ArmorBank {
 public:
  static ArmorBank* getArmorBank() {
    if (_ArmorBank == nullptr) {
      _ArmorBank = new ArmorBank;
    }
    return _ArmorBank;
  }
  ArmorItem* getArmor(unsigned i) {
    return (armors.at(i % armors.size()));
  }

  static void deleteBank() {
    delete _ArmorBank;
  }

 private:
  static ArmorBank*
      _ArmorBank;

  ArmorBank() {
    _ArmorBank = this;
  }
  ~ArmorBank() {
    for (unsigned i = 0; i < armors.size(); ++i) {
      delete armors.at(i);
    }
  }
  std::vector<ArmorItem*> armors = {
      new ArmorItem("armor 1", "this is armor 1", "type 1", 1),
      new ArmorItem("armor 2", "this is armor 2", "type 2", 2),
      new ArmorItem("armor 3", "this is armor 3", "type 3", 3),
      new ArmorItem("armor 4", "this is armor 4", "type 4", 4),
      new ArmorItem("armor 5", "this is armor 5", "type 5", 5),
      new ArmorItem("armor 6", "this is armor 6", "type 6", 6),
      new ArmorItem("armor 7", "this is armor 7", "type 7", 7),
  };
};

ArmorBank* ArmorBank::_ArmorBank = nullptr;

#endif