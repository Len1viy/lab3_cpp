//
// Created by vadim on 16.10.2023.
//

#include "Cell.h"
//#include "Level.h"
Cell &Cell::addItem(Item *nitem) {
    items.push_back(nitem);
    return *this;
}

Cell &Cell::delItem(Item *nitem) {
    int index = -1;
    for (int i = 0; i < items.size(); i++) {
        if (items[i] == nitem) {
            index = i;
            break;
        }
    }
    if (index != -1) items.erase(items.begin() + index);
    return *this;
}

Cell &Cell::changeTypeOfCell(TypeOfPoint p) {
    type = p;
    return *this;
}

bool Cell::canMove() {
    if (type == TypeOfPoint::tile || type == TypeOfPoint::stock) return true;
    return false;
}

void Cell::destroy() {
    if (type == TypeOfPoint::glass || type == TypeOfPoint::partition) type = TypeOfPoint::tile;
}

Cell &Cell::operator=(const Cell &other) {
    type = other.type;
//        character = other.character;
    items = other.items;
    return *this;
}

std::ostream &operator<<(std::ostream &c, Cell &cell) {
    if (cell.type == TypeOfPoint::tile) c << "floor";
//        c << cell.type;
    return c;
}

bool Cell::operator==(const Cell &other) const {
    return p.x == other.p.x && p.y == other.p.y;
}

bool Cell::isWeapon() {
    if (items.empty()) return false;
    for (auto &i: items) {
        if (i->getName() == TypeOfItem::weapon) return true;
        return false;
    }
}

Cell::Cell(Cell &nCell) {
    type = nCell.type;
    items = nCell.items;
    p = nCell.p;
    status = nCell.status;
}
