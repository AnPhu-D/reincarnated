#include "consumableItem.h"
#include <string>
using std::string;

ConsumableItem::ConsumableItem(string name, string description, int[] buffs) : InventoryItem(name, description) {
    this->buffs = buffs;
}