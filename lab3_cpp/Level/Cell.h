//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_CELL_H
#define LAB3_CPP_CELL_H

#include "iostream"
#include "Point.h"
//#include "../Character/Character.h"
#include "../Inventory/Items/Item.h"
#include <vector>

typedef enum TypeOfPoint {

    tile,
    wall,
    glass,
    partition,
    stock,
} TypeOfPoint;

typedef enum Status {
    notOpen,
    open,
} Status;


class Cell {
private:
    TypeOfPoint type;
    std::vector<Item *> items;
    Point p;
    Status status;
public:
    Cell(TypeOfPoint t) : type(t), items(std::vector<Item *>()), status(Status::open) {}
    Cell(Point point) : type(TypeOfPoint::tile), items(std::vector<Item *>()), p(point), status(Status::open) {};
    Cell(int y, int x) : type(TypeOfPoint::tile), items(std::vector<Item *>()), p(Point(x, y)), status(Status::open) {};

    Cell() : type(TypeOfPoint::tile), items(std::vector<Item *>()), status(Status::open) {};

    [[nodiscard]] Status getStatus() const { return status; }

    void changeStatus() {
        if (status == Status::open) status = Status::notOpen;
        else status = Status::open;
    }

    [[nodiscard]] TypeOfPoint getType() const { return type; };

//        [[nodiscard]] character::Character *getCharacter() const {return character;};
//        Cell &setCharacter(character::Character *c) {
//            character = c;
//            return *this;
//        }
    std::vector<Item *> getItems() { return items; };

    Cell &setType(TypeOfPoint ntype) {
        type = ntype;
        return *this;
    };

    Cell &setItems(std::vector<Item *> nitems) {
        std::vector<Item *> temp(nitems.begin(), nitems.end());
        items = temp;
        return *this;
    }

    [[nodiscard]] Point getPoint() const {
        return p;
    }

    Cell &setPoint(const int y, const int x) {
        p.x = x;
        p.y = y;
        return *this;
    }

    bool isWeapon();

//        bool isCharacter() {
//            if (character != nullptr) return true;
//            return false;
//        }

    Cell &addItem(Item *nitem);

    Cell &delItem(Item *nitem);

    Cell &changeTypeOfCell(TypeOfPoint p);

    bool canMove();

    void destroy();

    Cell &operator=(const Cell &other);

    bool operator==(const Cell &other) const;

    friend std::ostream &operator<<(std::ostream &, Cell &);
};


#endif //LAB3_CPP_CELL_H
