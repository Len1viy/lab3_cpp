//
// Created by vadim on 16.10.2023.
//

#include "Wild.h"

namespace character {

    void Wild::attack(character::Character *enemy) {
        if (enemy->getType() != level::Side::enemy) {
            enemy->changeHealth(getDamage(), -1);
            return;
        }
        return;
    }

    Character &Wild::move(Point npoint) {
        point = npoint;
        return *this;
    }


    int Wild::getDamage() {
        return rand() % (getMaxDamage() - getMinDamage() + 1) + getMinDamage();
    }
} // character