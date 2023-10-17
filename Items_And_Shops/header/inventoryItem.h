#ifndef __INVENTORY_ITEM_H__
#define __INVENTORY_ITEM_H__


#include <string>

using std::string;

class InventoryItem {
    private:
        string name;
        string description;
    public:
        InventoryItem(string name, string description) : name(name), description(description) {}
        string getItemName() {
            return name;
        }
        string getItemDescription() {
            return description;
        }
};

#endif