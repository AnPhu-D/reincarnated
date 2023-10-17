#ifndef __CONSUMABLE_ITEM_H__
#define __CONSUMABLE_ITEM_H__


#include "InventoryItem.h"
#include <string>
using std::string;

class ConsumableItem : public InventoryItem  {
    private:
        int[] buffs;
    public:
        ConsumableItem(string name, string description, int[] buffs);
};

#endif
