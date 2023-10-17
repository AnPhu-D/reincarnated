#include "../header/Market.h"
#include "../header/Inventory.h"
#include "../header/Store.h"
#include "../header/InventoryItem.h"
#include <iostream>

using namespace std;

void Market::buyItem(InventoryItem *item, int quantity, Inventory &inventory)
{
    int price = store.getPrice(item);
    int stock = store.getNumItems(item->getItemName());
    if (price == -1)
    {
        cout << "Item not found in store" << endl;
    }
    else if (stock < quantity)
    {
        cout << "Not enough items in stock" << endl;
    }
    else if (inventory.getGold() < price * quantity)
    {
        cout << "Not enough money" << endl;
    }
    else
    {
        for (int i = 0; i < quantity; i++)
        {
            inventory.addItem(item);
        }
        inventory.removeGold(price * quantity);
        store.buyItem(item, quantity);
    }
}

void Market::sellItem(InventoryItem *item, int quantity, Inventory &inventory)
{
    int price = store.getPrice(item);
    int stock = store.getNumItems(item->getItemName());
    if (price == -1)
    {
        cout << "Item not found in store" << endl;
    }
    else if (inventory.getNumItems(item->getItemName()) < quantity)
    {
        cout << "Not enough items in inventory" << endl;
    }
    else
    {
        for (int i = 0; i < quantity; i++)
        {
            inventory.removeItem(item);
        }
        inventory.addGold(price * quantity);
        store.addItem(item, price, quantity);
    }
}

void Market::addItemToStore(InventoryItem *item, int price, int numInStock)
{
    store.addItem(item, price, numInStock);
}

void Market::removeItemFromStore(InventoryItem *item)
{
    store.removeItem(item);
}

void Market::setPrice(InventoryItem *item, int price)
{
    store.setPrice(item, price);
}

string Market::printStore()
{
    return store.printStore();
}

InventoryItem *Market::getItem(string itemName)
{
    return store.getItem(itemName);
}

string Market::printCompleteStore()
{
    vector<InventoryItem *> items = store.getItems();
    vector<int> prices = store.getPrices();
    vector<int> stock = store.getStock();
    string output = "Store:\n";
    for (int i = 0; i < items.size(); i++)
    {
        output += items[i]->getItemName() + " - " + to_string(prices[i]) + " gold - " + to_string(stock[i]) + " in stock\n";
    }
    return output;
}