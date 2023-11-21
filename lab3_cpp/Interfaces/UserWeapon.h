//
// Created by vadim on 24.10.2023.
//

#ifndef LAB3_CPP_USERWEAPON_H
#define LAB3_CPP_USERWEAPON_H
#include "../Inventory/Items/Weapon.h"
    class UserWeapon {
        virtual void throwWeapon() = 0;
        virtual void takeWeapon(Weapon *weapon1) = 0;
    };



#endif //LAB3_CPP_USERWEAPON_H
