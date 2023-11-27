//
// Created by vadim on 24.10.2023.
//

#ifndef LAB3_CPP_USERWEAPON_H
#define LAB3_CPP_USERWEAPON_H

#include "../Inventory/Items/Weapon.h"

/**
    * @brief Interface of using Weapons
    */
class UserWeapon {
public:
    /**
     * @brief function of throwing weapon on cell
     */
    virtual void throwWeapon() = 0;

    /**
     * function of taking weapon from cell to hands
     * @param weapon1 Weapon which we take
     */
    virtual void takeWeapon(Weapon *weapon1) = 0;
};


#endif //LAB3_CPP_USERWEAPON_H
