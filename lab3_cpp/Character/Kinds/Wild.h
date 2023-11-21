
//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_WILDCREATURE_H
#define LAB3_CPP_WILDCREATURE_H

#include <iostream>
#include "Enemy.h"


class Wild : public Enemy, public Attack {
private:
    int accuracy;
    int minDamage;
    int maxDamage;
public:
    Wild() : Enemy(TypeOfCreature::wild), accuracy(100), minDamage(1), maxDamage(3) {};

    Wild(const std::string &nm, Characteristics c, Cell *ncell, int acc, int minD, int maxD) :
            Enemy(nm, c, ncell, TypeOfCreature::wild, Side::enemy),
            accuracy(acc),
            minDamage(minD),
            maxDamage(maxD) {};

    [[nodiscard]] int getAccuracy() const { return accuracy; };

    Wild &setAccuracy(int naccuracy) {
        accuracy = naccuracy;
        return *this;
    };

    [[nodiscard]] int getMaxDamage() const { return maxDamage; };

    Wild &setMaxDamage(int nMaxDamage) {
        maxDamage = nMaxDamage;
        return *this;
    }

    [[nodiscard]] int getMinDamage() const { return minDamage; };

    Wild &setMinDamage(int nMinDamage) {
        minDamage = nMinDamage;
        return *this;
    };


    int getDamage() override;

//    std::ostream &print(std::ostream &c) override;
//
//    friend std::ostream &operator<<(std::ostream &c, Wild &wild);

    void Dead() override;


    bool canAttack() override;

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
