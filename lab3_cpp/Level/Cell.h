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

/**
 * @brief class which describes the position on the map
 */

class Cell {
private:
    TypeOfPoint type;
    std::vector<Item *> items;
    Point p;
    Status status;
public:
/**
 * @brief constructor
 * @param t type of point
 */
    Cell(TypeOfPoint t) : type(t), items(std::vector<Item *>()), status(Status::open) {}
/**
 * @brief constructor
 * @param point point of cell on the map with type tile
 */
    Cell(Point point) : type(TypeOfPoint::tile), items(std::vector<Item *>()), p(point), status(Status::open) {};
/**
 * @brief constructor
 * @param y y component of point
 * @param x x component of point
 */
    Cell(int y, int x) : type(TypeOfPoint::tile), items(std::vector<Item *>()), p(Point{x, y}), status(Status::open) {};
/**
 * @brief Default constructor
 */
    Cell() : type(TypeOfPoint::tile), items(std::vector<Item *>()), status(Status::open) {};
/**
 * @brief getting status
 * @return status of cell
 */
    [[nodiscard]] Status getStatus() const { return status; }
/**
 * @brief changing status of cell
 */
    void changeStatus() {
        if (status == Status::open) status = Status::notOpen;
        else status = Status::open;
    }
/**
 * @brief getter of type of point
 * @return type of point
 */
    [[nodiscard]] TypeOfPoint getType() const { return type; };

    /**
     * @brief getter of items which the cell contains
     * @return vector of pointers on items
     */
    std::vector<Item *> getItems() { return items; };
/// \brief setter of type of point
/// \param ntype new type of point which we want to set
/// \return changed cell
    Cell &setType(TypeOfPoint ntype) {
        type = ntype;
        return *this;
    };
/**
 * @brief setter of items
 * @param nitems vector of new items which will be on this cell
 * @return changed cell
 */
    Cell &setItems(std::vector<Item *> nitems) {
        std::vector<Item *> temp(nitems.begin(), nitems.end());
        items = temp;
        return *this;
    }
/**
 * @brief getter of point which describe the position of the cell on the map
 * @return point of the cell
 */
    [[nodiscard]] Point getPoint() const {
        return p;
    }
/**
 * @brief setter of point
 * @param y - y component of point
 * @param x - x component of point
 * @return changed cell
 */
    Cell &setPoint(const int y, const int x) {
        p.x = x;
        p.y = y;
        return *this;
    }
/**
 * @brief is weapon on the cell or not
 * @return true if there is weapon and false otherwise
 */
    bool isWeapon();

/**
 * @brief add item to cell
 * @param nitem pointer to item
 * @return changed cell
 */
    Cell &addItem(Item *nitem);
/**
 * @brief delete item from cell
 * @param nitem pointer to item
 * @return changed cell
 */
    Cell &delItem(Item *nitem);
/**
 * @brief change type of cell
 * @param p new type of cell
 * @return changed cell
 */
    Cell &changeTypeOfCell(TypeOfPoint p);
/**
 * @brief determines whether it is possible to be in a given cell or not
 * @return true if character can and false otherwise
 */
    bool canMove();
/**
 * @brief method of destroying the cell if it's type of cell is glass or partition
 */
    void destroy();
/**
 * @brief overloaded copy operator =
 * @param other other cell which we want to copy
 * @return copied cell
 */
    Cell &operator=(const Cell &other);
/**
 * @brief overloaded operator == which compare x and y components of cells
 * @param other the other cell with which we compare
 * @return true if components are equal and false otherwise
 */
    bool operator==(const Cell &other) const;

    friend std::ostream &operator<<(std::ostream &, Cell &);

    Cell(Cell &nCell);
};


#endif //LAB3_CPP_CELL_H
