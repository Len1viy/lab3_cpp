//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_INVENTORY_H
#define LAB3_CPP_INVENTORY_H

#include "iostream"
#include "Items/Item.h"
#include <vector>

class Inventory {
private:
    int weight;
    int countOfItems;
    std::vector<Item *> items;
public:
    Inventory() : weight(0), countOfItems(0), items(std::vector<Item *>()) {}

    ~Inventory() {
//        for (auto i: items) {
//            delete[] i;
//        }
    }

    [[nodiscard]] std::vector<Item *> getItems() const { return items; }

    [[nodiscard]] int getCurrentWeight() const { return weight; }

    Inventory &setCurrentWeight(int nweight) {
        weight = nweight;
        return *this;
    };

    [[nodiscard]] int getCountOfItems() const { return countOfItems; }

    Inventory &setCountOfItems(int count) {
        countOfItems = count;
        return *this;
    }

    Inventory &addItem(Item *item);

    Item *deleteItem(int index);

    Item &operator[](int index);


    friend std::ostream &operator<<(std::ostream &c, Inventory &inventory);
};


#endif //LAB3_CPP_INVENTORY_H
