//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_CELL_H
#define LAB3_CPP_CELL_H

#include "iostream"
#include "../Inventory/Items/Item.h"
#include <vector>
namespace level {
    typedef enum TypeOfPoint {
        floor,
        wall,
        glass,
        partition,
        stock,
    } TypeOfPoint;


    class Cell  {
    private:
        TypeOfPoint type;
        character::Character *character;
        std::vector<inventory::Item*> items;
    public:
        Cell(TypeOfPoint t) : type(t), character(nullptr), items(std::vector<inventory::Item*>()) {}
        TypeOfPoint getType() const {return type;};
        character::Character *getCharacter() const {return character;};
        Cell &setCharacter(character::Character *c) {
            character = c;
            return *this;
        }
        std::vector<inventory::Item*> getItems() {return items;};
        Cell &setType(TypeOfPoint ntype) {
            type = ntype;
            return *this;
        };
        Cell &setItems(std::vector<inventory::Item*> nitems) {
            std::vector<inventory::Item*> temp(nitems.begin(), nitems.end());
            items = temp;
            return *this;
        }

        bool isCharacter() {
            if (character != nullptr) return true;
            return false;
        }

        Cell &addItem(inventory::Item *nitem);
        Cell &delItem(int index);
        Cell &changeTypeOfCell(TypeOfPoint p);
        bool canMove();
        void destroy();
    };

} // level

#endif //LAB3_CPP_CELL_H
