//
// Created by vadim on 16.10.2023.
//

#include "Inventory.h"


    Item &Inventory::operator[](int index) {
        return *items[index];
    }

    Inventory &Inventory::addItem(Item *item) {
        weight += item->getWeight();
        countOfItems++;
        items.push_back(item);
        return *this;
    }

    Item *Inventory::deleteItem(int index) {
        weight -= items[index]->getWeight();
        Item *ans = items[index];
        items.erase(items.begin() + index);
        countOfItems -= 1;
        return ans;
    }

//std::ostream &operator<<(std::ostream &c, Inventory &inventory) {
//    if (inventory.getItems().empty()) return c;
//    for (int i = 0; i < inventory.getItems().size(); i++) {
//        c << inventory[i];
//    }
//    return c;
//}
