//
// Created by vadim on 24.10.2023.
//

#ifndef LAB3_CPP_ATTACK_H
#define LAB3_CPP_ATTACK_H

#include "iostream"
#include "../Level/Matrix.h"
class Character;
class Attack {
public:
    virtual bool isHit(int acc) {
        int check = rand() % 100;
        if (check < acc) return true;
        return false;
    }

    virtual int getDamage() = 0;
    virtual void attack(Character *enemy, Matrix<Cell> &matr) = 0;
};


#endif //LAB3_CPP_ATTACK_H
