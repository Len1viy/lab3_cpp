//
// Created by vadim on 16.10.2023.
//

#include "Forager.h"

namespace character {
    void Forager::takeItem(int index) {
        cell->getItems()[index]->setOwner(*this);
        inventory.addItem(cell->getItems()[index]);
        cell->delItem(index);
    }

    void Forager::dropItem(int index) {
        cell->addItem(&inventory[index]);
        inventory[index].setOwner(nullptr);
        inventory.deleteItem(index);
    }

    Character &Forager::move(Point npoint) {
        point = npoint;
        return *this;
    }
} // character