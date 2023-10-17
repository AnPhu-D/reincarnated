#ifndef STORE_H
#define STORE_H

#include "InventoryItem.h"

using namespace std;

class Store
{
private:
    vector<InventoryItem *> items;
    vector<int> prices;
    vector<int> stock;

public:
    void addItem(InventoryItem *item, int price, int numInStock);
    int getPrice(InventoryItem *item);
    void setPrice(InventoryItem *item, int price);
    int buyItem(InventoryItem *item, int quantity);
    void removeItem(InventoryItem *item);
    void removeItem(string itemName);
    string printStore();
    bool hasItem(InventoryItem *item);
    bool hasItem(string itemName);
    InventoryItem *getItem(string itemName);
    int getNumItems();
    int getNumItems(string itemName);
    vector<InventoryItem *> getItems();
    vector<int> getPrices();
    vector<int> getStock();
};

#endif