//
// Created by vadim on 16.10.2023.
//

#include "Cell.h"

namespace level {
    Cell &Cell::addItem(inventory::Item *nitem) {
        items.push_back(nitem);
        return *this;
    }
    Cell &Cell::delItem(int index) {
        items.erase(items.begin() + index);
        return *this;
    }
    Cell &Cell::changeTypeOfCell(TypeOfPoint p) {
        type = p;
        return *this;
    }
    bool Cell::canMove() {
        if (type == TypeOfPoint::floor || type == TypeOfPoint::stock) return true;
        return false;
    }
    void Cell::destroy() {
        if (type == TypeOfPoint::glass || type == TypeOfPoint::partition) type = TypeOfPoint::floor;
    }
} // level