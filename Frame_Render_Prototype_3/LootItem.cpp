#include "LootItem.h"
#include <string>

using std::string;

LootItem::LootItem(string name, string description, int quantity)
    : InventoryItem(name, description) {
  this->quantity = quantity;
}

int LootItem::getQuantity() {
  return quantity;
}

void LootItem::setQuantity(int quantity) {
  this->quantity = quantity;
}