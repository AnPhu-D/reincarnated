#ifndef __BACKPACK_ITEM_H__
#define __BACKPACK_ITEM_H__


#include "InventoryItem.h"
#include <string>
using std::string;

class BackpackItem : public InventoryItem  {
    private:
        int storageCapacity;
    public:
        BackpackItem(string name, string description, int storageCapacity);
        int getCapacity();
};

#endif

