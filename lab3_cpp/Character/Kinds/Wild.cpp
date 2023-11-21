//
// Created by vadim on 16.10.2023.
//

#include "Wild.h"





int Wild::getDamage() {
    if (isHit(accuracy)) return rand() % (getMaxDamage() - getMinDamage() + 1) + getMinDamage();
}

//std::ostream &operator<<(std::ostream &c, Wild &wild) {
//    c << "Class: Wild; Name: " << wild.getName();
//    if (wild.getCharacteristics().currentHealth == 0) return c << "\nIt's Dead";
//    c << "; Point: y = " << wild.getY() << " x = " << wild.getX();
//    c << "\nCharacteristics: Health = " << wild.getCharacteristics().currentHealth << "/" << wild.getCharacteristics().maxHealth
//      << " Time = " << wild.getTime() << "/" << wild.getMaxTime() << "\n";
//    return c;
//}
//
//std::ostream &Wild::print(std::ostream &c) {
//    return c << *this;
//}

void Wild::Dead() {
    setCell(nullptr);
}



bool Wild::canAttackToCell(Cell *cell, std::vector<Cell *> points) {
    if (cell == nullptr) return false;
    return way(getCell(), cell) <= 1 && cell->canMove();
}

bool Wild::canAttack() {return true;}

Character &Wild::move1(Matrix<Cell> &matr, std::vector<Character *> iSeeEnemies) {
    std::vector<Cell *> points = iSee(matr);
    bool flag = false;
    if (!iSeeEnemies.empty()) {
        for (auto j: iSeeEnemies) {
            if (canAttackToCell(j->getCell(), points)) {
                attack(j, matr);
                flag = true;
                break;
            }
        }
        if (!flag) {
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

    } else {
        std::vector<Cell *> closerForGoing;
        for (auto i = points.begin(); i != points.end(); i++) {
            int cntOfCells = way(getCell(), *i);
            if (cntOfCells * getCharacteristics().pointsForStep <= getCharacteristics().currentTime && cntOfCells == 1 && (*i)->canMove()) {
                closerForGoing.push_back(*i);
            }
        }
        changeTime(getCharacteristics().pointsForStep, -1);
        setCell(closerForGoing[rand() % closerForGoing.size()]);
    }
}

void Wild::attack(Character *enemy, Matrix<Cell> &matr) {
    if (canAttackToCell(enemy->getCell(), iSee(matr))) {
        enemy->changeHealth(getDamage(), -1);
        changeTime(getPointsForStep(), -1);
    }
}


// character



