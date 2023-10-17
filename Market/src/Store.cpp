#include "../header/Inventory.h"
#include "../header/InventoryItem.h"
#include "../header/Store.h"

#include <stdexcept>

using namespace std;

void Store::addItem(InventoryItem *item, int price, int numInStock)
{
    if (hasItem(item))
    {
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i]->getItemName() == item->getItemName())
            {
                stock[i] += numInStock;
            }
        }
        return;
    }
    else
    {
        items.push_back(item);
        prices.push_back(price);
        stock.push_back(numInStock);
    }
}

int Store::getPrice(InventoryItem *item)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i] == item)
        {
            return prices[i];
        }
    }
    return -1;
}

void Store::setPrice(InventoryItem *item, int price)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->getItemName() == item->getItemName())
        {
            prices[i] = price;
        }
    }
}

int Store::buyItem(InventoryItem *item, int quantity)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->getItemName() == item->getItemName())
        {
            if (stock[i] > quantity)
            {
                stock[i] -= quantity;
                return prices[i] * quantity;
            }
            else if (stock[i] == quantity)
            {
                removeItem(item);
                return prices[i] * quantity;
            }
            else
            {
                return -1;
            }
        }
    }
    return -1;
}

void Store::removeItem(InventoryItem *item)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->getItemName() == item->getItemName())
        {
            items.erase(items.begin() + i);
            prices.erase(prices.begin() + i);
            stock.erase(stock.begin() + i);
        }
    }
}

void Store::removeItem(string itemName)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->getItemName() == itemName)
        {
            items.erase(items.begin() + i);
            prices.erase(prices.begin() + i);
            stock.erase(stock.begin() + i);
        }
    }
}

string Store::printStore()
{
    string output = "Store:\n";
    for (int i = 0; i < items.size(); i++)
    {
        output += items[i]->getItemName() + " - " + to_string(prices[i]) + " gold\n";
    }
    return output;
}

bool Store::hasItem(InventoryItem *item)
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

bool Store::hasItem(string itemName)
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

InventoryItem *Store::getItem(string itemName)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->getItemName() == itemName)
        {
            return items[i];
        }
    }
    throw invalid_argument("Item not found");
}

int Store::getNumItems()
{
    return items.size();
}

int Store::getNumItems(string itemName)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->getItemName() == itemName)
        {
            return stock[i];
        }
    }
    return -1;
}

vector<InventoryItem *> Store::getItems()
{
    return items;
}

vector<int> Store::getPrices()
{
    return prices;
}

vector<int> Store::getStock()
{
    return stock;
}
