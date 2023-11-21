//
// Created by vadim on 16.10.2023.
//

#include "Character.h"

Character &Character::changeHealth(int healthOut, int operation) {
    if (characteristics.currentHealth + operation * healthOut < 0) {
        characteristics.currentHealth = 0;
        Dead();
        return *this;
    } else if (characteristics.currentHealth + operation * healthOut > characteristics.maxHealth) {
        characteristics.currentHealth = characteristics.maxHealth;
        return *this;
    }
    characteristics.currentHealth += operation * healthOut;
    return *this;
}

Character &Character::changeTime(int time, int operation) {
    if (characteristics.currentTime + operation * time < 0) {
        characteristics.currentTime = 0;
        return *this;
    } else if (characteristics.currentTime + operation * time > characteristics.maxTime) {
        characteristics.currentTime = characteristics.maxTime;
        return *this;
    }
    characteristics.currentTime += operation * time;
    return *this;
}

//std::ostream &operator<<(std::ostream &c, Character *character) {
////        c << "Health = " << character->getCharacteristics().currentHealth << "/" << character->getCharacteristics().maxHealth << "\n";
////        c << *character;
//    return c;
//}

std::vector<Cell *> Character::iSee(Matrix<Cell> &matr) {
    int x = getX();
    int y = getY();
    int rad = getRadius();
    std::vector<Cell *> cells;
    std::function comp = [y, x, rad, &matr](int index) {
        return index % matr.getCols() >= x - rad && index % matr.getCols() <= x + rad && (int)(index / matr.getCols()) >= y - rad && (int)(index / matr.getCols()) <= y + rad;
    };
    int max_index = (y + rad) * matr.getCols() + x + rad;
    int min_index;
    if (y - rad < 0 && x - rad < 0) min_index = 0;
    else if (y - rad < 0) min_index = x - rad;
    else if (x - rad < 0) min_index = (y - rad) * matr.getCols();
    else min_index = (y - rad) * matr.getCols() + x - rad;
    for (auto i = matr.beginSpecial(comp); i != matr.endSpecial(comp); ++i) {
        if (i.getIndex() <= max_index && i.getIndex() >= min_index) {
            cells.push_back(&(*i));
        }
    }
    return cells;
}


int Character::way(Cell *from, Cell *to) {
    return abs(from->getPoint().x - to->getPoint().x) + abs(from->getPoint().y - to->getPoint().y);
}



//Character &Character::move1(std::vector<Cell *> points, Matrix<Cell> matr) {
//
//}


//    bool Character::isSeeSmb(level::Cell &cl) {
//        if (cl.isCharacter()) return true;
//        return false;
//    } // character


////
//// Created by vadim on 16.10.2023.
////
//
//#include "Character.h"
//
//Character &Character::changeHealth(int healthOut, int operation) {
//    if (characteristics.currentHealth + operation * healthOut < 0) {
//        characteristics.currentHealth = 0;
//        Dead();
//        return *this;
//    } else if (characteristics.currentHealth + operation * healthOut > characteristics.maxHealth) {
//        characteristics.currentHealth = characteristics.maxHealth;
//        return *this;
//    }
//    characteristics.currentHealth += operation * healthOut;
//    return *this;
//}
//
//Character &Character::changeTime(int time, int operation) {
//    if (characteristics.currentTime + operation * time < 0) {
//        characteristics.currentTime = 0;
//        return *this;
//    } else if (characteristics.currentTime + operation * time > characteristics.maxTime) {
//        characteristics.currentTime = characteristics.maxTime;
//        return *this;
//    }
//    characteristics.currentTime += operation * time;
//    return *this;
//}
//
//std::ostream &operator<<(std::ostream &c, Character *character) {
////        c << "Health = " << character->getCharacteristics().currentHealth << "/" << character->getCharacteristics().maxHealth << "\n";
////        c << *character;
//    return c;
//}
//
//int Character::way(Cell *from, Cell *to) {
//    return abs(from->getPoint().x - to->getPoint().x) + abs(from->getPoint().y - to->getPoint().y);
//}
//
//void Character::findPath(Cell *to, std::vector<Cell *> points, int &length, Cell *target) {
//    int shortestWay = 1e9;
//    for (auto i = points.begin(); i != points.end(); i++) {
//        int cntOfCells = way(getCell(), *i);
//        if (cntOfCells * getCharacteristics().pointsForStep <= getCharacteristics().currentTime) {
//            if (shortestWay > way(*i, to)) {
//                shortestWay = way(*i, to);
//                target = *i;
//                length = cntOfCells;
//                if (shortestWay == 0) break;
//            }
//        }
//    }
//}
//
//
////    bool Character::isSeeSmb(level::Cell &cl) {
////        if (cl.isCharacter()) return true;
////        return false;
////    } // character