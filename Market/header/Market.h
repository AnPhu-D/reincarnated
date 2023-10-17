#include "Inventory.h"
#include "Store.h"
#include "InventoryItem.h"

using namespace std;

class Market
{
private:
    Store store;

public:
    void buyItem(InventoryItem *item, int quantity, Inventory &inventory);
    void sellItem(InventoryItem *item, int quantity, Inventory &inventory);
    void addItemToStore(InventoryItem *item, int price, int numInStock);
    void removeItemFromStore(InventoryItem *item);
    void setPrice(InventoryItem *item, int price);
    InventoryItem *getItem(string itemName);
    string printStore();
    string printCompleteStore();
};