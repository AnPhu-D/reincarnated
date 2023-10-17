#ifndef WEAPON_BANK
#define WEAPON_BANK

#include <iostream>
#include <string>
#include <vector>
#include "weaponItem.h"

class WeaponBank {
 public:
  static WeaponBank* getWeaponBank() {
    if (_WeaponBank == nullptr) {
      _WeaponBank = new WeaponBank;
    }
    return _WeaponBank;
  }
  WeaponItem* getWeapn(unsigned i) {
    return (weapons.at(i % weapons.size()));
  }

  static void deleteBank() {
    delete _WeaponBank;
  }

 private:
  static WeaponBank*
      _WeaponBank;

  WeaponBank() {
    _WeaponBank = this;
  }
  ~WeaponBank() {
    for (unsigned i = 0; i < weapons.size(); ++i) {
      delete weapons.at(i);
    }
  }
  std::vector<WeaponItem*> weapons = {
      new WeaponItem("weapon 1", "this is weapon 1", "type 1", 1),
      new WeaponItem("weapon 2", "this is weapon 2", "type 2", 2),
      new WeaponItem("weapon 3", "this is weapon 3", "type 3", 3),
      new WeaponItem("weapon 4", "this is weapon 4", "type 4", 4),
      new WeaponItem("weapon 5", "this is weapon 5", "type 5", 5),
      new WeaponItem("weapon 6", "this is weapon 6", "type 6", 6),
      new WeaponItem("weapon 7", "this is weapon 7", "type 7", 7),
  };
};

WeaponBank* WeaponBank::_WeaponBank = nullptr;

#endif