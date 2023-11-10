//
// Created by vadim on 24.10.2023.
//

#ifndef LAB3_CPP_USERINVENTORY_H
#define LAB3_CPP_USERINVENTORY_H
#include "../Inventory/Inventory.h"


namespace interface {
    class InventoryUser {
        virtual void takeItem(int index) = 0;
        virtual void dropItem(int index) = 0;
    };
}



#endif //LAB3_CPP_USERINVENTORY_H
