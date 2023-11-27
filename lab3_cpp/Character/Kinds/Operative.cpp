
//
// Created by vadim on 16.10.2023.
//

#include "Operative.h"
#include "../../Inventory/Items/ContainerForBullet.h"
#include "algorithm"

//    void Operative::attack(character::Character *enemy) {
//        if (enemy->getType() != Side::player) {
//            enemy->changeHealth(getDamage(), -1);
//            return;
//        }
//        return;
//    }

void Operative::takeItem(Item *nItem) {
    if (inventory.getCurrentWeight() + nItem->getWeight() <= getStrength()) {
        inventory.addItem(nItem);
        if (getCell() != nullptr) getCell()->delItem(nItem);
    } else throw std::invalid_argument("Too much items you want to take!");

}

void Operative::dropItem(int index) {
    Item *item = inventory.deleteItem(index);
    getCell()->addItem(item);
}

void Operative::throwWeapon() {
    if (*(activeWeapon) != Weapon()) {
        Weapon *ans = activeWeapon;
        activeWeapon = new Weapon();
        if (getCell() != nullptr) getCell()->addItem(ans);
    }

}


void Operative::takeWeapon(Weapon *weapon1) {
    if (getCell() == nullptr) {
        throwWeapon();
        (*activeWeapon) = (*weapon1);
    } else {
        throwWeapon();
        getCell()->delItem(weapon1);
        (*activeWeapon) = (*weapon1);
    }

}

void Operative::useItem(int index) {
    inventory.getItems()[index]->use(*this);
}


void Operative::useItem(Item *item) {
    changeTime(item->use(*this), -1);
}



int Operative::getDamage() {
    if (activeWeapon->getCurrentCountOfBuillet() == 0) return 0;
    int damage = activeWeapon->getDamage();
//    std::cout << damage << "\n";
    changeTime(activeWeapon->getPointsForShoot(), -1);
    if (isHit(accuracy)) return damage;
    return 0;
}



void Operative::reload() {
    if (activeWeapon->getCurrentCountOfBuillet() != activeWeapon->getMaxCountOfBullet() &&
        getTime() >= activeWeapon->getPointsForReload()) {
        for (auto &i: inventory.getItems()) {
            if (i->getName() == TypeOfItem::containerForBullets) {
                if (((ContainerForBullet *) i)->getBulletType() == activeWeapon->getBullet()) {
                    useItem(i);
                    activeWeapon->reload();
                    break;
                }
            }
        }
        changeTime(activeWeapon->getPointsForReload(), -1);
    } else if (getTime() < activeWeapon->getPointsForReload()) {
        changeTime(getTime(), -1);
    }
}

//std::ostream &operator<<(std::ostream &c, Operative &oper) {
//    Inventory inventory = oper.getInventory();
//    c << "Class: Operative; Name: " << oper.getName();
//    if (oper.getCharacteristics().currentHealth == 0) return c << "\nIt's Dead";
//    c << "; Point: y = " << oper.getY() << " x = " << oper.getX();
//    c << "\nCharacteristics: Health = " << oper.getCharacteristics().currentHealth << "/"
//      << oper.getCharacteristics().maxHealth;
//    c << " Time = " << oper.getTime() << "/" << oper.getMaxTime() << "\nWeapon: " << oper.getActiveWeapon() << "\nInventory:\n";
////    std::cout << inventory;
//    c << inventory << "\n";
//    return c;
//}

void Operative::Dead() {
    while (inventory.getItems().size() != 0) {
        dropItem(0);
    }
    if (*activeWeapon != Weapon()) {
        throwWeapon();
    }
    setCell(nullptr);
}


//Character &Operative::move(std::vector<Cell *> points) {
//    std::vector<Cell *> closerForGoing;
//    for (auto i = points.begin(); i != points.end(); i++) {
//        int cntOfCells = way(getCell(), *i);
//        if (cntOfCells * getCharacteristics().pointsForStep <= getCharacteristics().currentTime && cntOfCells == 1) {
//            closerForGoing.push_back(*i);
//        }
//    }
//    changeTime(getCharacteristics().pointsForStep, -1);
//    setCell(closerForGoing[rand() % closerForGoing.size()]);
//}

bool Operative::canAttackToCell(Cell *cell, std::vector<Cell *> points) {
    if (cell == nullptr) return false;
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

void Operative::deleteFromInventory(int index) {
    inventory.deleteItem(index);
}


void Operative::move(Direction direction, Matrix<Cell> &matr) {
    switch (direction) {
        case Direction::left:
            if (0 == getX() || !matr.getElementByAdress(getY(), getX() - 1)->canMove()) return;
            setCell(matr.getElementByAdress(getY(), getX() - 1));
            changeTime(getPointsForStep(), -1);
            break;
        case Direction::up:
            if (0 == getY() || !matr.getElementByAdress(getY() - 1, getX())->canMove()) return;
            setCell(matr.getElementByAdress(getY() - 1, getX()));
            changeTime(getPointsForStep(), -1);
            break;
        case Direction::right:
            if (matr.getCols() - 1 == getX() || !matr.getElementByAdress(getY(), getX() + 1)->canMove()) return;
            setCell(matr.getElementByAdress(getY(), getX() + 1));
            changeTime(getPointsForStep(), -1);
            break;
        case Direction::down:
            if (matr.getRows() == getY() || !matr.getElementByAdress(getY() + 1, getX())->canMove()) return;
            setCell(matr.getElementByAdress(getY() + 1, getX()));
            changeTime(getPointsForStep(), -1);
            break;
    }
}

//Character &Operative::move1(Matrix<Cell> &matr, std::vector<Character *> iSeeEnemies) {
//    std::vector<Cell *> points = iSee(matr);
//    std::vector<Cell *> closerForGoing;
//    for (auto i = points.begin(); i != points.end(); i++) {
//        int cntOfCells = way(getCell(), *i);
//        if (cntOfCells * getCharacteristics().pointsForStep <= getCharacteristics().currentTime && cntOfCells == 1 && (*i)->canMove()) {
//            closerForGoing.push_back(*i);
//        }
//    }
////    std::cout << getTime() << " " << getCell()->getPoint().x << " " << getCell()->getPoint().y << "\n";
//    changeTime(getCharacteristics().pointsForStep, -1);
//    setCell(closerForGoing[rand() % closerForGoing.size()]);
////    std::cout << getTime() << " " << getCell()->getPoint().x << " " << getCell()->getPoint().y << "\n";
//
//}

void Operative::attack(Character *enemy, Matrix<Cell> &matr) {
    if (canAttackToCell(enemy->getCell(), iSee(matr)))
        enemy->changeHealth(getDamage(), -1);
}











////
//// Created by vadim on 16.10.2023.
////
//
//#include "Operative.h"
//#include "../../Inventory/Items/ContainerForBullet.h"
//#include "algorithm"
//
////    void Operative::attack(character::Character *enemy) {
////        if (enemy->getType() != Side::player) {
////            enemy->changeHealth(getDamage(), -1);
////            return;
////        }
////        return;
////    }
//
//void Operative::takeItem(Item *nItem) {
//    inventory.addItem(nItem);
//}
//
//void Operative::dropItem(int index) {
//    inventory.deleteItem(index);
//}
//
//void Operative::throwWeapon() {
//    Weapon *ans = activeWeapon;
//    activeWeapon = new Weapon();
//    getCell()->addItem(ans);
//}
//
//
//void Operative::takeWeapon(Weapon &weapon1) {
//    throwWeapon();
//    getCell()->delItem(&weapon1);
//    (*activeWeapon) = weapon1;
//}
//
//int Operative::useItem(Item *item) {
////    item->use(this);
//    return 0;
//}
//
//int Operative::getDamage() {
//    if (activeWeapon->getCurrentCountOfBuillet() == 0) return 0;
//    int damage = activeWeapon->getDamage();
//    changeTime(activeWeapon->getPointsForShoot(), -1);
//    if (isHit(accuracy)) return damage;
//    return 0;
//}
//
//void Operative::reload() {
//    if (activeWeapon->getCurrentCountOfBuillet() != activeWeapon->getMaxCountOfBullet() &&
//        getTime() >= activeWeapon->getPointsForReload()) {
//        for (auto &i: inventory.getItems()) {
//            if (i->getName() == TypeOfItem::containerForBullets) {
//                if (((ContainerForBullet *) i)->getBulletType() == activeWeapon->getBullet()) {
//                    useItem(i);
//                    break;
//                }
//            }
//        }
//        activeWeapon->reload();
//        changeTime(activeWeapon->getPointsForReload(), -1);
//    }
//}
//
//std::ostream &operator<<(std::ostream &c, Operative &oper) {
//    c << "Class: Operative; Name: " << oper.getName();
//    if (oper.getCharacteristics().currentHealth == 0) return c << "\nIt's Dead";
//    c << "; Point: y = " << oper.getY() << " x = " << oper.getX();
//    c << "\nCharacteristics: Health = " << oper.getCharacteristics().currentHealth << "/"
//      << oper.getCharacteristics().maxHealth;
//    c << " Time = " << oper.getTime() << "/" << oper.getMaxTime() << "\nWeapon: " << oper.getActiveWeapon()
//      << "\nInventory:\n";
//    return c;
//}
//
//void Operative::Dead() {
//    for (auto &i: getInventory().getItems()) {
//        getCell()->addItem(i);
//    }
//    for (auto i = 0; i < getInventory().getItems().size(); i++) {
//        getInventory().deleteItem(i);
//    }
//    getCell()->addItem(activeWeapon);
//    activeWeapon = nullptr;
//    setCell(nullptr);
//}
//
//
//Character &Operative::move(std::vector<Cell *> points, Matrix<Cell> matr) {
//    std::vector<Cell *> closerForGoing;
//    for (auto i = points.begin(); i != points.end(); i++) {
//        int cntOfCells = way(getCell(), *i);
//        if (cntOfCells * getCharacteristics().pointsForStep <= getCharacteristics().currentTime && cntOfCells == 1) {
//            closerForGoing.push_back(*i);
//        }
//    }
//    changeTime(getCharacteristics().pointsForStep, -1);
//    setCell(closerForGoing[rand() % closerForGoing.size()]);
//}
//
//bool Operative::canAttackToCell(Cell *cell, std::vector<Cell *> points) {
//    Cell *start = getCell();
//    int index;
//    for (int i = 0; i < points.size(); i++) {
//        if (start == points[i]) {
//            index = i;
//            break;
//        }
//    }
//    int radius = getRadius() * 2 + 1;
//    Point p{index % radius, (int) (index / radius)};
//    if (cell->getPoint().x == start->getPoint().x) {
//        if (cell->getPoint().y > start->getPoint().y) {
//            for (int i = 0; i < abs(cell->getPoint().y - start->getPoint().y); i++) {
//                if (!(points[(p.y + i) * radius + p.x]->canMove())) return false;
//            }
//        } else if (cell->getPoint().y < start->getPoint().y) {
//            for (int i = 0; i < abs(cell->getPoint().y - start->getPoint().y); i++) {
//                if (!(points[(p.y - i) * radius + p.x]->canMove())) return false;
//            }
//        }
//    } else if (cell->getPoint().y == start->getPoint().y) {
//        if (cell->getPoint().x > start->getPoint().x) {
//            for (int i = 0; i < abs(cell->getPoint().x - start->getPoint().x); i++) {
//                if (!(points[p.y * radius + p.x + i]->canMove())) return false;
//            }
//        } else if (cell->getPoint().y < start->getPoint().y) {
//            for (int i = 0; i < abs(cell->getPoint().x - start->getPoint().x); i++) {
//                if (!(points[p.y * radius + p.x - i]->canMove())) return false;
//            }
//        }
//    } else return false;
//}
//
//bool Operative::canAttack() { return true; }
//
//
//
//
//
//
//
//
