#include <sstream>
#include <algorithm>

#include "../header/Inventory.h"

using namespace std;

void Inventory::addItem(InventoryItem *item)
{
    items.push_back(item);
    sortItems();
}

void Inventory::removeItem(InventoryItem *item)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->getItemName() == item->getItemName())
        {
            items.erase(items.begin() + i);
            break;
        }
    }
}

void Inventory::removeItem(string itemName)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->getItemName() == itemName)
        {
            items.erase(items.begin() + i);
            break;
        }
    }
}

string Inventory::printInventory()
{
    string output = "Inventory:\n";
    for (int i = 0; i < items.size(); i++)
    {
        output += items[i]->getItemName() + "\n";
    }
    return output;
}

bool Inventory::hasItem(InventoryItem *item)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->getItemName() == item->getItemName())
        {
            return true;
        }
    }
    return false;
}

bool Inventory::hasItem(string itemName)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->getItemName() == itemName)
        {
            return true;
        }
    }
    return false;
}

InventoryItem *Inventory::getItem(string itemName)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->getItemName() == itemName)
        {
            return items[i];
        }
    }
    return new InventoryItem("NULL", "NULL");
}

int Inventory::getNumItems()
{
    return items.size();
}

int Inventory::getNumItems(string itemName)
{
    int count = 0;
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->getItemName() == itemName)
        {
            count++;
        }
    }
    return count;
}

vector<InventoryItem *> Inventory::getItems()
{
    return items;
}

void Inventory::sortItems()
{
    sort(items.begin(), items.end(), [](InventoryItem *a, InventoryItem *b)
         { return a->getItemName() < b->getItemName(); });
}

int Inventory::getGold()
{
    return gold;
}

void Inventory::setGold(int gold)
{
    this->gold = gold;
}

void Inventory::addGold(int gold)
{
    this->gold += gold;
}

void Inventory::removeGold(int gold)
{
    this->gold -= gold;
}