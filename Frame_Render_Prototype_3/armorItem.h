#ifndef __ARMORITEM_H__
#define __ARMORITEM_H__

#include <string>
#include "inventoryItem.h"
using namespace std;

class ArmorItem : public InventoryItem {
 private:
  int defense;
  string armorType;

 public:
  ArmorItem(string name, string description, string armorType, int defense);
  int getDefense();
  string getArmorType();
};

#endif
