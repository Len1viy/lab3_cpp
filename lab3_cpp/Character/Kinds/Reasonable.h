
//
// Created by vadim on 08.11.2023.
//

#ifndef LAB3_CPP_REASONABLE_H
#define LAB3_CPP_REASONABLE_H

#include <iostream>
#include "Enemy.h"
#include <vector>


class Reasonable : public Enemy, public UserWeapon, public Attack {
private:
    Weapon *activeWeapon;
    int accuracy;
    std::vector<Cell *> stocks;
    std::vector<Cell *> visitedStocks;

public:
    Reasonable() : Enemy(TypeOfCreature::reasonable), activeWeapon(new Weapon()), accuracy(100), stocks(), visitedStocks() {};
    Reasonable(std::string nm, Characteristics c, Cell *ncell, int acc, std::vector<Cell *> st) :
            Enemy(std::move(nm), c, ncell, TypeOfCreature::reasonable, Side::enemy),
            activeWeapon(new Weapon()),
            accuracy(acc),
            stocks(std::move(st)),
            visitedStocks()
    {};
    Reasonable(std::string nm, Characteristics c, Cell *ncell, int acc) : Enemy(std::move(nm), c, ncell, TypeOfCreature::reasonable, Side::enemy), accuracy(acc), activeWeapon(new Weapon()) {};
    Reasonable(std::string nm, Characteristics c, Cell *ncell, int acc, Weapon *weapon,  std::vector<Cell *> st) :
            Enemy(std::move(nm), c, ncell, TypeOfCreature::reasonable, Side::enemy), activeWeapon(weapon), accuracy(acc), stocks(std::move(st)), visitedStocks() {};


    Reasonable &setStocks(std::vector <Cell *> nstocks) {
        stocks = nstocks;
        return *this;
    }

    [[nodiscard]] int getAccuracy() const { return accuracy; }

    Reasonable &setAccuracy(const int naccuracy) {
        accuracy = naccuracy;
        return *this;
    }

    Reasonable &setActiveWeapon(Weapon *weapon) {
        activeWeapon = new Weapon();
        *activeWeapon = *weapon;
        return *this;
    }

    void throwWeapon() override;

    void takeWeapon(Weapon *weapon1) override;

    int getDamage() override;
//    std::ostream &print(std::ostream &c) override;
    [[nodiscard]] Weapon *getActiveWeapon() const {return activeWeapon;}

    void Dead() override;

//    friend std::ostream &operator<<(std::ostream &c, Reasonable &reasonable);

    Weapon *findWeapon();

    bool canAttack() override;
    bool canAttackToCell(Cell *cell, std::vector<Cell *> points) override;
    Character &move1(Matrix<Cell> &matr, std::vector<Character *> iSeeEnemies) override;
    void attack(Character *enemy, Matrix<Cell> &matr) override;


};


#endif //LAB3_CPP_REASONABLE_H






////
//// Created by vadim on 08.11.2023.
////
//
//#ifndef LAB3_CPP_REASONABLE_H
//#define LAB3_CPP_REASONABLE_H
//
//#include <iostream>
//#include "Enemy.h"
//#include <vector>
//
//
//    class Reasonable : public Enemy, public UserWeapon, public Attack {
//    private:
//        Weapon *activeWeapon;
//        int accuracy;
//        std::vector<Cell *> stocks;
//        std::vector<Cell *> visitedStocks;
//
//    public:
//        Reasonable() : Enemy(), activeWeapon(), accuracy(15), stocks(), visitedStocks() {};
//        Reasonable(std::string nm, Characteristics c, Cell *ncell, int acc, std::vector<Cell *> st) :
//            Enemy(std::move(nm), c, ncell, TypeOfCreature::reasonable, Side::enemy),
//            activeWeapon(new Weapon()),
//            accuracy(acc),
//            stocks(std::move(st)),
//            visitedStocks()
//        {};
//        Reasonable(std::string nm, Characteristics c, Cell *ncell, int acc) : Enemy(std::move(nm), c, ncell, TypeOfCreature::reasonable, Side::enemy), accuracy(acc) {};
//        Reasonable(std::string nm, Characteristics c, Cell *ncell, int acc, Weapon *weapon,  std::vector<Cell *> st) :
//        Enemy(std::move(nm), c, ncell, TypeOfCreature::reasonable, Side::enemy), activeWeapon(weapon), accuracy(acc), stocks(std::move(st)), visitedStocks() {};
//
//
//
//        [[nodiscard]] int getAccuracy() const { return accuracy; }
//
//        Reasonable &setAccuracy(const int naccuracy) {
//            accuracy = naccuracy;
//            return *this;
//        }
//
//        Reasonable &setActiveWeapon(Weapon *weapon) {
//            activeWeapon = weapon;
//            return *this;
//        }
//
//        void throwWeapon() override;
//
//        void takeWeapon(Weapon &weapon1) override;
//
//        int getDamage() override;
//        std::ostream &print(std::ostream &c) override;
//        [[nodiscard]] Weapon *getActiveWeapon() const {return activeWeapon;}
//
//        void Dead() override;
//
//        friend std::ostream &operator<<(std::ostream &c, Reasonable &reasonable);
//
//        Weapon *findWeapon();
//
//        bool canAttack() override;
//        bool canAttackToCell(Cell *cell, std::vector<Cell *> points) override;
//
//        Character &move(std::vector<Cell *> points, Matrix<Cell> matr) override;
//    };
//
//
//#endif //LAB3_CPP_REASONABLE_H
