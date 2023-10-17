#ifndef __ARMORITEM_H__
#define __ARMORITEM_H__


#include "InventoryItem.h"
#include <string>
using namspace std;

class ArmorItem : public InventoryItem {
    private:
        int defense;
        string armorType;
    public:
        ArmorItem(string name, string description, int defense, string armorType);
        int getDefense();
        string getArmorType();
};

#endif
