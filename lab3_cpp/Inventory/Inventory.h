//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_INVENTORY_H
#define LAB3_CPP_INVENTORY_H

#include "iostream"
#include "Items/Item.h"
#include <vector>

/**
 * @brief class which contains all information about inventory which creatures have
 */

class Inventory {
private:
    int weight;
    int countOfItems;
    std::vector<Item *> items;
public:
    /**
     * @brief Default constructor
     */
    Inventory() : weight(0), countOfItems(0), items(std::vector<Item *>()) {}

    ~Inventory() {
//        for (auto i: items) {
//            delete[] i;
//        }
    }

    /**
     * @brief getter of Items
     * @return vector of pointers to Items
     */

    [[nodiscard]] std::vector<Item *> getItems() const { return items; }
/**
 * @brief getter of current weight of all of the inventory
 * @return current weight of inventory
 */
    [[nodiscard]] int getCurrentWeight() const { return weight; }
/**
 * @brief setter of current weight of inventory
 * @param nweight - new weight of inventory
 * @return changed inventory
 */
    Inventory &setCurrentWeight(int nweight) {
        weight = nweight;
        return *this;
    };
/**
 * @brief getter of count of items which the inventory contains
 * @return count of items in the inventory
 */
    [[nodiscard]] int getCountOfItems() const { return countOfItems; }
/**
 * @brief setter of count of items in inventory
 * @param count new count if items
 * @return changed inventory
 */
    Inventory &setCountOfItems(int count) {
        countOfItems = count;
        return *this;
    }
/**
 * @brief add Item to inventory
 * @param item pointer to item which we want to add to inventory
 * @return changed inventory
 */
    Inventory &addItem(Item *item);
/**
 * @brief delete item from inventory
 * @param index - index of the item which we want to delete from inventory
 * @return
 */
    Item *deleteItem(int index);
/**
 * @brief overloaded operator []
 * @param index - index of item which we want to get
 * @return item which we wanted to get
 */
    Item &operator[](int index);


    friend std::ostream &operator<<(std::ostream &c, Inventory &inventory);
};


#endif //LAB3_CPP_INVENTORY_H
