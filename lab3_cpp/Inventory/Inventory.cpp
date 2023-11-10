//
// Created by vadim on 16.10.2023.
//

#include "Inventory.h"

namespace inventory {

    Item &Inventory::operator[](int index) {
        return *items[index];
    }

    Inventory &Inventory::addItem(Item *item) {
        weight += item->getWeight();
        countOfItems++;
        items.push_back(item);
        return *this;
    }

    Inventory &Inventory::deleteItem(int index) {
        weight -= items[index]->getWeight();
        items.erase(items.begin() + index);
        return *this;
    }
} // lab3