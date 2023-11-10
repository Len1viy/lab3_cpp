//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_INVENTORY_H
#define LAB3_CPP_INVENTORY_H
#include "iostream"
#include "Items/Item.h"
#include "../Matrix.h"
#include <map>

namespace inventory {

    class Inventory {
    private:
        int weight;
        int countOfItems;
        std::vector<Item *> items;
    public:
        Inventory() : weight(0), countOfItems(0), items(std::vector<Item *>()){}
        int getCurrentWeight() const { return weight; }
        Inventory &setCurrentWeight(int nweight) {
            weight = nweight;
            return *this;
        };
        int getCountOfItems() const { return countOfItems; }
        Inventory &setCountOfItems(int count) {
            countOfItems = count;
            return *this;
        }

        Inventory &addItem(Item *item);
        Inventory &deleteItem(int index);

        Item &operator[](int index);

    };

} // lab3

#endif //LAB3_CPP_INVENTORY_H
