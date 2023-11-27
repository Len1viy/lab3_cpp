
//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_WILDCREATURE_H
#define LAB3_CPP_WILDCREATURE_H

#include <iostream>
#include "Enemy.h"

/**
 * @brief class of enemy with type Wild. wild creatures have mission - attack and chase operatives
 */
class Wild : public Enemy, public Attack {
private:
    int accuracy;
    int minDamage;
    int maxDamage;
public:
    /**
     * @brief default constructor with standard characteristics
     */
    Wild() : Enemy(TypeOfCreature::wild), accuracy(100), minDamage(1), maxDamage(3) {};

/**
 * constructor
 * @param nm creature's name
 * @param c creature's characteristics
 * @param ncell creature's cell on which he will stay
 * @param acc creature's accuracy
 * @param minD creature's minimal damage
 * @param maxD creature's maximum damage
 */
    Wild(const std::string &nm, Characteristics c, Cell *ncell, int acc, int minD, int maxD) :
            Enemy(nm, c, ncell, TypeOfCreature::wild, Side::enemy),
            accuracy(acc),
            minDamage(minD),
            maxDamage(maxD) {};

    [[nodiscard]] int getAccuracy() const { return accuracy; };

/// \brief setter of accuracy
/// \param naccuracy new accuracy
/// \return changed accuracy
    Wild &setAccuracy(int naccuracy) {
        accuracy = naccuracy;
        return *this;
    };

    /**
     * @brief getter of maximum damage of wild
     * @return maximum damage which wild can deal
     */
    [[nodiscard]] int getMaxDamage() const { return maxDamage; };

/**
 * @brief setter of maximum damage
 * @param nMaxDamage new maximum damage
 * @return changed wild
 */
    Wild &setMaxDamage(int nMaxDamage) {
        maxDamage = nMaxDamage;
        return *this;
    }

    /**
     * @brief getter of minimal damage of wild
     * @return minimal damage which wild can deal
     */

    [[nodiscard]] int getMinDamage() const { return minDamage; };

/**
 * @brief setter of minimal damage
 * @param nMinDamage new minimal damage
 * @return changed wild
 */
    Wild &setMinDamage(int nMinDamage) {
        minDamage = nMinDamage;
        return *this;
    };


    int getDamage() override;

//    std::ostream &print(std::ostream &c) override;
//
//    friend std::ostream &operator<<(std::ostream &c, Wild &wild);

    void Dead() override;


    bool canAttackToCell(Cell *cell, std::vector<Cell *> points) override;


    void attack(Character *enemy, Matrix<Cell> &matr) override;


    Character &move1(Matrix<Cell> &matr, std::vector<Character *> iSeeEnemies) override;
};

// character

#endif //LAB3_CPP_WILDCREATURE_H


////
//// Created by vadim on 16.10.2023.
////
//
//#ifndef LAB3_CPP_WILDCREATURE_H
//#define LAB3_CPP_WILDCREATURE_H
//
//#include <iostream>
//#include "Enemy.h"
//
//
//class Wild : public Enemy, public Attack {
//private:
//    int accuracy;
//    int minDamage;
//    int maxDamage;
//public:
//    Wild() : Enemy(), accuracy(50), minDamage(10), maxDamage(20) {};
//
//    Wild(const std::string &nm, Characteristics c, Cell *ncell, int acc, int minD, int maxD) :
//            Enemy(nm, c, ncell, TypeOfCreature::wild, Side::enemy),
//            accuracy(acc),
//            minDamage(minD),
//            maxDamage(maxD) {};
//
//    [[nodiscard]] int getAccuracy() const { return accuracy; };
//
//    Wild &setAccuracy(int naccuracy) {
//        accuracy = naccuracy;
//        return *this;
//    };
//
//    [[nodiscard]] int getMaxDamage() const { return maxDamage; };
//
//    Wild &setMaxDamage(int nMaxDamage) {
//        maxDamage = nMaxDamage;
//        return *this;
//    }
//
//    [[nodiscard]] int getMinDamage() const { return minDamage; };
//
//    Wild &setMinDamage(int nMinDamage) {
//        minDamage = nMinDamage;
//        return *this;
//    };
//
//
//    int getDamage() override;
//
//    std::ostream &print(std::ostream &c) override;
//
//    friend std::ostream &operator<<(std::ostream &c, Wild &wild);
//
//    void Dead() override;
//
//    Character &move(std::vector<Cell *> points, Matrix<Cell> matr) override;
//
//    bool canAttack() override;
//
//    bool canAttackToCell(Cell *cell, std::vector<Cell *> points) override;
//};
//
//// character
//
//#endif //LAB3_CPP_WILDCREATURE_H
