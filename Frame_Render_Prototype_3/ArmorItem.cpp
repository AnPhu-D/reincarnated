#include "armorItem.h"
#include <string>

using std::string;

ArmorItem::ArmorItem(string name, string description, string armorType, int defense)
    : InventoryItem(name, description) {
  this->defense = defense;
  this->armorType = armorType;
}

int ArmorItem::getDefense() {
  return defense;
}

string ArmorItem::getArmorType() {
  return armorType;
}
