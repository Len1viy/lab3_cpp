//
// Created by vadim on 24.10.2023.
//

#ifndef LAB3_CPP_ENEMY_H
#define LAB3_CPP_ENEMY_H

#include <utility>
#include "../Character.h"

class Enemy : public Character {
public:
    Enemy(TypeOfCreature type) : Character(type) {};

    Enemy(std::string nm, Characteristics c, Cell *ncell, TypeOfCreature t, Side s) :
            Character(std::move(nm), c, ncell, t, s) {};

//    virtual std::ostream &print(std::ostream &) = 0;

//    friend std::ostream &operator<<(std::ostream &c, Enemy &enemy);

    std::vector<Cell*> lee(Matrix<Cell> &matr, Cell *to);

    virtual Character &move1(Matrix<Cell> &matr, std::vector<Character *> iSeeEnemies) = 0;

};


#endif //LAB3_CPP_ENEMY_H
