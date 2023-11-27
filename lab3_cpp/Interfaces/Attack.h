//
// Created by vadim on 24.10.2023.
//

#ifndef LAB3_CPP_ATTACK_H
#define LAB3_CPP_ATTACK_H

#include "iostream"
#include "../Level/Matrix.h"
class Character;

/**
 * @brief Interface of attack; It allows characters to attack
 */

class Attack {
public:
    /**
     * @brief Function which calculate the posibility of apply damage
     * @param acc - accuracy of character
     * @return bool - True: character has hitted. False: character hasn't hitted
     */

    virtual bool isHit(int acc) {
        int check = rand() % 100;
        if (check < acc) return true;
        return false;
    }

    /**
     * @brief pure virtual function of getting damage from character which attacks someone
     * @return int amount of damage which creature deals
     */
    virtual int getDamage() = 0;

    /**
     * @brief pure virtual function to attack someone
     * @param enemy - Character which is the target of attack
     * @param matr - Map of level
     */
    virtual void attack(Character *enemy, Matrix<Cell> &matr) = 0;
    /*
     * @brief Function which defines: can Operative attack the sell or not
     * @return True if he can, False if he can't
     */
    virtual bool canAttackToCell(Cell *cell, std::vector<Cell *> points) = 0;

};


#endif //LAB3_CPP_ATTACK_H
