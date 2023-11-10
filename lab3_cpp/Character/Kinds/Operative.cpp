//
// Created by vadim on 16.10.2023.
//

#include "Operative.h"
#include "../../Inventory/Items/MedKit.h"

namespace character {
    void Operative::attack(character::Character *enemy) {
        if (enemy->getType() != level::Side::player) {
            enemy->changeHealth(getDamage(), -1);
            return;
        }
        return;
    }

    void Operative::takeItem(int index) {
        if (getCurrentWeight() + cell->getItems()[index]->getWeight() > getStrength()) return;
        inventory.addItem(cell->getItems()[index]);
        return;
    }
    void Operative::dropItem(int index){
        if (index > inventory.getCountOfItems()) return;
        cell->addItem(&inventory[index]);
        inventory.deleteItem(index);
    }
    void Operative::throwWeapon(){
        if (activeWeapon == nullptr) return;
        cell->addItem(dynamic_cast<inventory::Item*>(activeWeapon));
        activeWeapon = nullptr;
    }
    void Operative::takeWeapon(int index){
        if (activeWeapon != nullptr) {
            activeWeapon = nullptr;
            cell->addItem(dynamic_cast<inventory::Item*>(activeWeapon));
        }
        activeWeapon = dynamic_cast<inventory::Weapon*>(cell->getItems()[index]);
        cell->delItem(index);
    }

    int Operative::getDamage(){
        if (activeWeapon->isHit(accuracy)) return activeWeapon->getDamage();
    }

    int Operative::useItem(inventory::Item *item) {
        if (item->getName() == inventory::TypeOfItem::medKit) {
            changeHealth(dynamic_cast<inventory::MedKit*>(item)->getHealth(), 1);
        }
    }
    Character &Operative::move(Point npoint) {
        point = npoint;
        return *this;
    }
} // character