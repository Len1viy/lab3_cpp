
//
// Created by vadim on 08.11.2023.
//

#include "Reasonable.h"
#include <algorithm>
//    void Reasonable::attack(character::Character *enemy) {
//        if (enemy->getType() != Side::enemy) {
//            enemy->changeHealth(getDamage(), -1);
//            return;
//        }
//    }

void Reasonable::throwWeapon() {
    if (*(activeWeapon) != Weapon()) {
        Weapon *ans = activeWeapon;
        delete activeWeapon;
        activeWeapon = new Weapon();
        getCell()->addItem(ans);
    }
}

void Reasonable::takeWeapon(Weapon *weapon1) {
    throwWeapon();
    getCell()->delItem(weapon1);
    activeWeapon = weapon1;
}

int Reasonable::getDamage() {
    if ((*activeWeapon) == Weapon()) {
        int damage = 5;
        changeTime(getPointsForStep(), -1);
        if (isHit(accuracy)) return damage;
        return 0;
    } else {
        if (activeWeapon->getCurrentCountOfBuillet() == 0) return 0;
        int damage = activeWeapon->getDamage();
        changeTime(activeWeapon->getPointsForShoot(), -1);
        if (isHit(accuracy)) return damage;
        return 0;
    }

}

//std::ostream &operator<<(std::ostream &c, Reasonable &reasonable) {
//    c << "Class: Reasonable; Name: " << reasonable.getName();
//    if (reasonable.getCharacteristics().currentHealth == 0) return c << "\nIt's Dead";
//    c << "; Point: y = " << reasonable.getY() << " x = " << reasonable.getX();
//    c << "\nCharacteristics: Health = " << reasonable.getCharacteristics().currentHealth << "/"
//      << reasonable.getCharacteristics().maxHealth
//      << " Time = " << reasonable.getTime() << "/" << reasonable.getMaxTime() << "\nWeapon: "
//      << reasonable.getActiveWeapon() << "\nInventory:\n";
//    return c;
//}
//
//std::ostream &Reasonable::print(std::ostream &c) {
//    return c << *this;
//}


void Reasonable::Dead() {
    throwWeapon();
    setCell(nullptr);
}

// сделать возможность брать самое крутое оружие
Weapon *Reasonable::findWeapon() {
    for (auto &i: getCell()->getItems()) {
        if (i->getName() == TypeOfItem::weapon) {
            auto *weapon = (Weapon *) i;
            getCell()->delItem(i);
            return weapon;
        }

    }
}


bool Reasonable::canAttack() { return true; }

bool Reasonable::canAttackToCell(Cell *cell, std::vector<Cell *> points) {
    if (cell == nullptr) return false;
    if (*activeWeapon == Weapon()) {
        return way(getCell(), cell) <= 1 && cell->canMove();
    }
    Cell *start = getCell();
    int index;
    for (int i = 0; i < points.size(); i++) {
        if (start == points[i]) {
            index = i;
            break;
        }
    }
    int radius = getRadius() * 2 + 1;
    Point p{index % radius, (int) (index / radius)};
    if (cell->getPoint().x == start->getPoint().x) {
        if (cell->getPoint().y > start->getPoint().y) {
            for (int i = 0; i < abs(cell->getPoint().y - start->getPoint().y); i++) {
                if (!(points[(p.y + i) * radius + p.x]->canMove())) {
                    if (points[(p.y + i) * radius + p.x]->getType() == TypeOfPoint::glass) points[(p.y + i) * radius + p.x]->destroy();
                    return false;
                }
            }
        } else if (cell->getPoint().y < start->getPoint().y) {
            for (int i = 0; i < abs(cell->getPoint().y - start->getPoint().y); i++) {
                if (!(points[(p.y - i) * radius + p.x]->canMove())) {
                    if (points[(p.y - i) * radius + p.x]->getType() == TypeOfPoint::glass) points[(p.y - i) * radius + p.x]->destroy();
                    return false;
                }
            }
        }
    } else if (cell->getPoint().y == start->getPoint().y) {
        if (cell->getPoint().x > start->getPoint().x) {
            for (int i = 0; i < abs(cell->getPoint().x - start->getPoint().x); i++) {
                if (!(points[p.y * radius + p.x + i]->canMove())) {
                    if (points[p.y * radius + p.x + i]->getType() == TypeOfPoint::glass) points[p.y * radius + p.x + i]->destroy();
                    return false;
                }
            }
        } else if (cell->getPoint().x < start->getPoint().x) {
            for (int i = 0; i < abs(cell->getPoint().x - start->getPoint().x); i++) {
                if (!(points[p.y * radius + p.x - i]->canMove())) {
                    if (points[p.y * radius + p.x - i]->getType() == TypeOfPoint::glass) points[p.y * radius + p.x - i]->destroy();
                    return false;
                }
            }
        }
    } else return false;
    return true;
}

Character &Reasonable::move1(Matrix<Cell> &matr, std::vector<Character *> iSeeEnemies) {
    std::vector<Cell *> points = iSee(matr);
    bool flag = false;
    if (!iSeeEnemies.empty()) {
        for (auto &j: iSeeEnemies) {
            if (canAttackToCell(j->getCell(), points)) {
                attack(j, matr);
                flag = true;
                break;
            }
        } if (!flag) {
            std::vector<Cell *> ways = lee(matr, iSeeEnemies[0]->getCell());
            Cell *goTo;
            if (ways.size() >= 2) goTo = lee(matr, iSeeEnemies[0]->getCell())[1];
            if (goTo != nullptr) {
                changeTime(getCharacteristics().pointsForStep, -1);
                setCell(goTo);
            } else {
                return *this;
            }
        }
    }
    else {
        if (*activeWeapon == Weapon() && getCell()->isWeapon()) {
            setActiveWeapon(findWeapon());
        } else if (*activeWeapon == Weapon()) {
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
            int shortestWay2 = 1e9;
            Cell *closerWithGun = nullptr;
            for (auto i = points.begin(); i != points.end(); i++) {
                int cntOfCells = way(getCell(), *i);
                if ((*i)->isWeapon() && shortestWay2 > cntOfCells) {
                    shortestWay2 = cntOfCells;
                    closerWithGun = *i;
                }
            }
            Cell *target = nullptr;
            if (shortestWay1 > shortestWay2) target = closerWithGun;
            else target = closerStock;
            if (target == nullptr) {
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
            }
            else {
                Cell *goTo = lee(matr, target)[1];
                if (goTo != nullptr) setCell(goTo);
                else {
                    goTo = target;
                    setCell(goTo);
                }
                if (goTo == closerStock) {
                    if (visitedStocks.size() == stocks.size()) visitedStocks.clear();
                    visitedStocks.push_back(goTo);
                }
            }
            changeTime(getCharacteristics().pointsForStep, -1);
        } else {
            if (activeWeapon->getCurrentCountOfBuillet() == 0) {
                throwWeapon();
            } else {
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
            }
        }
    }
    return *this;
}

void Reasonable::attack(Character *enemy, Matrix<Cell> &matr) {
    if (canAttackToCell(enemy->getCell(), iSee(matr)))
        enemy->changeHealth(getDamage(), -1);


}



