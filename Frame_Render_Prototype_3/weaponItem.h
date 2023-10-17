#ifndef WEAPON_ITEM_H
#define WEAPON_ITEM_H

#include "inventoryItem.h"
#include <string>

using std::string;

class WeaponItem : public InventoryItem
{
private:
    int damage;
    string weaponType;

public:
    WeaponItem(string name, string description, string weaponType, int damage);
    int getDamage();
    string getWeaponType();
};

#endif
