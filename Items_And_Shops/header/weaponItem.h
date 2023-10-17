#ifndef WEAPON_ITEM_H
#define WEAPON_ITEM_H

#include "InventoryItem.h"
#include <string>

using std::string;

class WeaponItem : public InventoryItem {
    private:
        int damage;
        string weaponType;

    public:
        WeaponItem(string name, description, string weaponType, int damage);
        int getDamage();
        int getWeaponType();

};

#endif
