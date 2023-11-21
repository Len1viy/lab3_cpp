//
// Created by vadim on 24.10.2023.
//

#ifndef LAB3_CPP_USERINVENTORY_H
#define LAB3_CPP_USERINVENTORY_H
#include "../Inventory/Inventory.h"
    class InventoryUser {
        virtual void takeItem(Item *nItem) = 0;
        virtual void dropItem(int index) = 0;
    };



#endif //LAB3_CPP_USERINVENTORY_H
