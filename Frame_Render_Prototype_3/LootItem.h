#ifndef __LOOT_ITEM_H__
#define __LOOT_ITEM_H__

#include <string>
#include "inventoryItem.h"

using std::string;

class LootItem : public InventoryItem {
 private:
  int quantity;

 public:
  LootItem(string name, string description, int quantity);
  int getQuantity();
  void setQuantity(int quantity);
};

#endif
