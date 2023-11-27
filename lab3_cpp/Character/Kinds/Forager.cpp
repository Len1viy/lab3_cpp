#include "Forager.h"
#include "algorithm"

void Forager::takeAllOfItems() {
    if (getCell()->getItems().empty()) return;
    while(!getCell()->getItems().empty()) {
        takeItem(getCell()->getItems()[0]);
    }
}


void Forager::takeItem(Item *nItem) {
    inventory.addItem(nItem);
    getCell()->delItem(nItem);
}

void Forager::dropItem(int index) {
    Item *item = inventory.deleteItem(index);
    getCell()->addItem(item);
}


//std::ostream &operator<<(std::ostream &c, Forager &forager) {
//    c << "Class: Forager; Name: " << forager.getName();
//    if (forager.getCharacteristics().currentHealth == 0) return c << "\nIt's Dead";
//    c << "; Point: y = " << forager.getY() << " x = " << forager.getX();
//    c << "\nCharacteristics: Health = " << forager.getCharacteristics().currentHealth << "/" << forager.getCharacteristics().maxHealth
//      << " Time = " << forager.getTime() << "/" << forager.getMaxTime() << "\nInventory:\n";
//    return c;
//}
//
//std::ostream &Forager::print(std::ostream &c) {
//    return c << *this;
//}

void Forager::Dead() {
    while (inventory.getItems().size() != 0) {
        dropItem(0);
    }
//    for (auto &i: getInventory().getItems()) {
//        getCell()->addItem(i);
//    }
//    for (auto i = 0; i < getInventory().getItems().size(); i++) {
//        inventory.deleteItem(i);
//    }
    setCell(nullptr);
}


Character &Forager::move1(Matrix<Cell> &matr, std::vector<Character *> iSeeEnemies) {
    std::vector<Cell *> points = iSee(matr);
    if (!(getCell()->getItems().empty()) && getCell()->getType() != TypeOfPoint::stock) {
        takeAllOfItems();
//        for (auto item: getCell()->getItems()) {
//            inventory.addItem(item);
//            getCell()->delItem(item);
//        }
    } else if (getCell()->getType() == TypeOfPoint::stock && !getInventory().getItems().empty()) {
        while (!inventory.getItems().empty()) {
            dropItem(0);
        }
//        inventory.getItems().clear();
//        inventory.setCountOfItems(0);
//        inventory.setCurrentWeight(0);
    }
    else {
        if (getInventory().getItems().empty()) {
            int shortestWay2 = 1e9;
            Cell *closerWithItems = nullptr;
            for (auto i = points.begin(); i != points.end(); i++) {
                int cntOfCells = way(getCell(), *i);
                if (!((*i)->getItems().empty()) && shortestWay2 > cntOfCells && (*i)->getType() != TypeOfPoint::stock) {
                    shortestWay2 = cntOfCells;
                    closerWithItems = *i;
                }
            }

            if (closerWithItems == nullptr) {
                std::vector<Cell *> closerForGoing;
                for (auto i = points.begin(); i != points.end(); i++) {
                    int cntOfCells = way(getCell(), *i);
                    if (cntOfCells * getCharacteristics().pointsForStep <= getCharacteristics().currentTime &&
                        cntOfCells == 1) {
                        closerForGoing.push_back(*i);
                    }
                }
                changeTime(getCharacteristics().pointsForStep, -1);
                setCell(closerForGoing[rand() % closerForGoing.size()]);
            } else {
                Cell *target;
                std::vector<Cell *> ans = lee(matr, closerWithItems);
                if (ans.size() > 1) {
                    target = ans[1];
                } else {
                    target = closerWithItems;
                }

                setCell(target);
                changeTime(getCharacteristics().pointsForStep, -1);
            }

        } else {
            int shortestWay1 = 1e9;
            Cell *closerStock = nullptr;
            for (auto i = stocks.begin(); i != stocks.end(); i++) {
                if (std::find(visitedStocks.begin(), visitedStocks.end(), *i) != visitedStocks.end()) continue;
                int cntOfCells = way(getCell(), *i);
                if (shortestWay1 > cntOfCells) {
                    shortestWay1 = cntOfCells;
                    closerStock = *i;
                }
            }
            std::vector<Cell *> answer = lee(matr, closerStock);
            Cell *target;
            if (answer.size() > 1) {
                target = answer[1];
            } else {
                target = closerStock;
            }
            setCell(target);
            if (target == closerStock) {
                if (visitedStocks.size() == stocks.size()) visitedStocks.clear();
                visitedStocks.push_back(target);
            }
            changeTime(getCharacteristics().pointsForStep, -1);
        }
    }
    return *this;
}







////
//// Created by vadim on 16.10.2023.
////
//
//#include "Forager.h"
//#include "algorithm"
//    void Forager::takeItem(Item *nItem) {
//        inventory.addItem(nItem);
//        getCell()->delItem(nItem);
//    }
//
//    void Forager::dropItem(int index) {
//        Item *item = inventory.deleteItem(index);
//        getCell()->addItem(item);
//    }
//
//
//    std::ostream &operator<<(std::ostream &c, Forager &forager) {
//        c << "Class: Forager; Name: " << forager.getName();
//        if (forager.getCharacteristics().currentHealth == 0) return c << "\nIt's Dead";
//        c << "; Point: y = " << forager.getY() << " x = " << forager.getX();
//        c << "\nCharacteristics: Health = " << forager.getCharacteristics().currentHealth << "/" << forager.getCharacteristics().maxHealth
//          << " Time = " << forager.getTime() << "/" << forager.getMaxTime() << "\nInventory:\n";
//        return c;
//    }
//
//    std::ostream &Forager::print(std::ostream &c) {
//        return c << *this;
//    }
//
//    void Forager::Dead() {
//        for (auto &i: getInventory().getItems()) {
//            getCell()->addItem(i);
//        }
//        for (auto i = 0; i < getInventory().getItems().size(); i++) {
//            getInventory().deleteItem(i);
//        }
//        setCell(nullptr);
//    }
//
//    Character &Forager::move(std::vector<Cell *> points, Matrix<Cell> matr) {
//        if (!(getCell()->getItems().empty()) && getCell()->getType() != TypeOfPoint::stock) {
//            for (auto item: getCell()->getItems()) {
//                inventory.addItem(item);
//                getCell()->delItem(item);
//            }
//        } else {
//            if (getInventory().getItems().empty()) {
//                int shortestWay2 = 1e9;
//                Cell *closerWithItems = nullptr;
//                for (auto i = points.begin(); i != points.end(); i++) {
//                    int cntOfCells = way(getCell(), *i);
//                    if (!((*i)->getItems().empty()) && shortestWay2 > cntOfCells) {
//                        shortestWay2 = cntOfCells;
//                        closerWithItems = *i;
//                    }
//                }
//
//                if (closerWithItems == nullptr) {
//                    std::vector<Cell *> closerForGoing;
//                    for (auto i = points.begin(); i != points.end(); i++) {
//                        int cntOfCells = way(getCell(), *i);
//                        if (cntOfCells * getCharacteristics().pointsForStep <= getCharacteristics().currentTime && cntOfCells == 1) {
//                            closerForGoing.push_back(*i);
//                        }
//                    }
//                    changeTime(getCharacteristics().pointsForStep, -1);
//                    setCell(closerForGoing[rand() % closerForGoing.size()]);
//                } else {
//                    Cell *target = nullptr;
//                    int length = 0;
//                    findPath(closerWithItems, points, length, target);
//                    changeTime(length * getCharacteristics().pointsForStep, -1);
//                    setCell(target);
//                }
//
//            } else {
//                int shortestWay1 = 1e9;
//                Cell *closerStock = nullptr;
//                for (auto i = stocks.begin(); i != stocks.end(); i++) {
//                    if (std::find(visitedStocks.begin(), visitedStocks.end(), *i) != visitedStocks.end()) continue;
//                    int cntOfCells = way(getCell(), *i);
//                    if (shortestWay1 > cntOfCells) {
//                        shortestWay1 = cntOfCells;
//                        closerStock = *i;
//                    }
//                }
//                Cell *target = nullptr;
//                int length = 0;
//                findPath(closerStock, points, length, target);
//                changeTime(length * getCharacteristics().pointsForStep, -1);
//                if (target == closerStock) {
//                    if (visitedStocks.size() == stocks.size()) visitedStocks.clear();
//                    visitedStocks.push_back(target);
//                }
//            }
//        }
//
//        return *this;
////        if (!(getCell()->getItems().empty()) && getCell()->getType() != TypeOfPoint::stock) {
////            for (auto item: getCell()->getItems()) {
////                inventory.addItem(item);
////                getCell()->delItem(item);
////            }
////        } else {
////            if (getInventory().getItems().empty()) {
////                int shortestWay2 = 1e9;
////                Cell *closerWithItems = nullptr;
////                for (auto i = points.begin(); i != points.end(); i++) {
////                    int cntOfCells = way(getCell(), *i);
////                    if (!((*i)->getItems().empty()) && shortestWay2 > cntOfCells) {
////                        shortestWay2 = cntOfCells;
////                        closerWithItems = *i;
////                    }
////                }
////
////                if (closerWithItems == nullptr) {
////                    std::vector<Cell *> closerForGoing;
////                    for (auto i = points.begin(); i != points.end(); i++) {
////                        int cntOfCells = way(getCell(), *i);
////                        if (cntOfCells * getCharacteristics().pointsForStep <= getCharacteristics().currentTime && cntOfCells == 1) {
////                            closerForGoing.push_back(*i);
////                        }
////                    }
////                    changeTime(getCharacteristics().pointsForStep, -1);
////                    setCell(closerForGoing[rand() % closerForGoing.size()]);
////                } else {
////                    Cell *target;
////                    target = lee(matr, closerWithItems)[0];
////                    changeTime(getCharacteristics().pointsForStep, -1);
////                    setCell(target);
////                }
////
////            } else {
////                int shortestWay1 = 1e9;
////                Cell *closerStock = nullptr;
////                for (auto i = stocks.begin(); i != stocks.end(); i++) {
////                    if (std::find(visitedStocks.begin(), visitedStocks.end(), *i) != visitedStocks.end()) continue;
////                    int cntOfCells = way(getCell(), *i);
////                    if (shortestWay1 > cntOfCells) {
////                        shortestWay1 = cntOfCells;
////                        closerStock = *i;
////                    }
////                }
////                Cell *target;
////                target = lee(matr, closerStock)[0];
////                changeTime(getCharacteristics().pointsForStep, -1);
////                setCell(target);
////                if (target == closerStock) {
////                    if (visitedStocks.size() == stocks.size()) visitedStocks.clear();
////                    visitedStocks.push_back(target);
////                }
////            }
////        }
////        return *this;
//    }
//
//
