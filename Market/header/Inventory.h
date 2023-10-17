#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>

#include "InventoryItem.h"

using namespace std;

class Inventory
{
private:
    vector<InventoryItem *> items;
    int gold = 0;
    void sortItems();

public:
    Inventory() {}
    void addItem(InventoryItem *item);
    void removeItem(InventoryItem *item);
    void removeItem(string itemName);
    string printInventory();
    bool hasItem(InventoryItem *item);
    bool hasItem(string itemName);
    InventoryItem *getItem(string itemName);
    int getNumItems();
    int getNumItems(string itemName);
    vector<InventoryItem *> getItems();
    int getGold();
    void setGold(int gold);
    void addGold(int gold);
    void removeGold(int gold);
};

#endif