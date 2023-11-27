//
// Created by vadim on 24.10.2023.
//

#ifndef LAB3_CPP_USERINVENTORY_H
#define LAB3_CPP_USERINVENTORY_H

#include "../Inventory/Inventory.h"


/**
 * @brief Interface of using inventory
 */
class InventoryUser {
public:
    /**
     * @brief pure virtual function of taking Items to inventory
     * @param nItem - Item which we take from cell to inventory
     *
     */

    virtual void takeItem(Item *nItem) = 0;

    /**
        * @brief pure virtual function of drop Items to cell
        * @param index - index of Item which we drop to cell from inventory
        *
        */
    virtual void dropItem(int index) = 0;
};


#endif //LAB3_CPP_USERINVENTORY_H
