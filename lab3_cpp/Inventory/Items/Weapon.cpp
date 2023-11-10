//
// Created by vadim on 16.10.2023.
//

#include "Weapon.h"

namespace inventory {
    int Weapon::getDamage() const {
        return rand() % (damageMax - damageMin) + damageMin;
    }

    bool Weapon::isHit(int acc) {
        int check = rand() % 100;
        if (check < acc) return false;
        return true;
    }

} // inventory