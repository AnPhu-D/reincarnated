#include "../header/backpackItem.h"
#include <string>
using std::string;

BackpackItem::BackpackItem(string name, string description, int storageCapacity) : InventoryItem(name, description) {
    this-> storageCapacity = storageCapacity;
}

int BackpackItem::getCapacity() {
    return this->storageCapacity;
}