#include "weaponItem.h"
#include <string>

using std::string;

WeaponItem::WeaponItem(string name, string description, string weaponType, int damage)
    : InventoryItem(name, description) {
  this->weaponType = weaponType;
  this->damage = damage;
}

int WeaponItem::getDamage() {
  return damage;
}

string WeaponItem::getWeaponType() {
  return weaponType;
}
