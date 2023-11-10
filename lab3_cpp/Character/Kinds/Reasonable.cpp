//
// Created by vadim on 08.11.2023.
//

#include "Reasonable.h"

namespace character {
    void Reasonable::attack(character::Character *enemy) {
        if (enemy->getType() != level::Side::enemy) {
            enemy->changeHealth(getDamage(), -1);
            return;
        }
        return;
    }

    void Reasonable::throwWeapon() {
        if (activeWeapon == nullptr) return;
        cell->addItem(dynamic_cast<inventory::Item*>(activeWeapon));
        activeWeapon = nullptr;
    }

    void Reasonable::takeWeapon(int index) {
        if (activeWeapon != nullptr) {
            activeWeapon = nullptr;
            cell->addItem(dynamic_cast<inventory::Item*>(activeWeapon));
        }
        activeWeapon = dynamic_cast<inventory::Weapon*>(cell->getItems()[index]);
        cell->delItem(index);
    }

    int Reasonable::getDamage() {
        if (activeWeapon->isHit(accuracy)) return activeWeapon->getDamage();
    }
// написать алгос передвижения
    Character &Reasonable::move(Point npoint) {
        point = npoint;
        return *this;
    }
} // character