#include "role.h"

bool Role::armorValid(string armorType) const {
  auto it = std::find(validArmorTypes.begin(), validArmorTypes.end(), armorType);
  return it != validArmorTypes.end();
}

bool Role::weaponValid(string weaponType) const {
  auto it = std::find(validWeaponTypes.begin(), validWeaponTypes.end(), weaponType);
  return it != validWeaponTypes.end();
}