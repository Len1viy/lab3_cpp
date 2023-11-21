//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_OPERATIVE_H
#define LAB3_CPP_OPERATIVE_H

#include "iostream"
#include "../Character.h"
#include "../../Inventory/Items/MedKit.h"

//class MedKit;


class Operative : public Character, public UserWeapon, public InventoryUser, public Attack {
private:
    int strength;
    int accuracy;
    Inventory inventory;
    Weapon *activeWeapon;
public:
    int getDamage() override;

    Operative() : Character(), strength(100), accuracy(100), inventory(), activeWeapon(Weapon::createPistol()) {};
    Operative(std::string nm, Characteristics c, Cell *ncell, int acc, int stth, Weapon *weapon) :
            Character(std::move(nm), c, ncell, TypeOfCreature::operative, Side::player),
            strength(stth),
            accuracy(acc),
            inventory(),
            activeWeapon(weapon)
    {};

    Operative(std::string nm, Characteristics c, Cell *ncell, int acc, int stth) :
            Character(std::move(nm), c, ncell, TypeOfCreature::operative, Side::player),
            strength(stth),
            accuracy(acc),
            inventory(),
            activeWeapon(Weapon::createPistol())
    {};

    [[nodiscard]] int getStrength() const { return strength; };
    [[nodiscard]] int getAccuracy() const { return accuracy; };
    [[nodiscard]] Weapon *getActiveWeapon() const { return activeWeapon; }
    Operative &setStrength(const int nstrength) {
        strength = nstrength;
        return *this;
    }
    Operative &setAccuracy(const int nstrength) {
        strength = nstrength;
        return *this;
    }

    [[nodiscard]] Inventory getInventory() const {return inventory;}

    void useItem(Item *item);
    void useItem(int index);
    Operative &setActiveWeapon(const Weapon *weapon) {
        activeWeapon = new Weapon();
        *activeWeapon = *weapon;
        return *this;
    };
    void takeItem(Item *nItem) override;
    void dropItem(int index) override;
    void throwWeapon() override;
    void takeWeapon(Weapon *weapon1) override;

    [[nodiscard]] int getCurrentWeight() const { return inventory.getCurrentWeight(); };
    void reload();
//    friend std::ostream &operator<<(std::ostream &c, Operative &oper);
    void Dead() override;

    bool canAttack() override;

    bool canAttackToCell(Cell *cell, std::vector<Cell *> points) override;
//    Character &move1(Matrix<Cell> &matr, std::vector<Character *> iSeeEnemies) override;

    void deleteFromInventory(int index);

    void attack(Character *enemy, Matrix<Cell> &matr) override;


//    void move(int direction, Matrix<Cell> &matr);
    void move(int direction, Matrix<Cell> &matr);
};


#endif //LAB3_CPP_OPERATIVE_H



////
//// Created by vadim on 16.10.2023.
////
//
//#ifndef LAB3_CPP_OPERATIVE_H
//#define LAB3_CPP_OPERATIVE_H
//
//#include "iostream"
//#include "../Character.h"
//
//
//class Operative : public Character, public UserWeapon, public InventoryUser, public Attack {
//private:
//    int strength;
//    int accuracy;
//    Inventory inventory;
//    Weapon *activeWeapon;
//public:
//    int getDamage() override;
//
//    Operative() : Character(), strength(100), accuracy(80), inventory(), activeWeapon(new Weapon()) {};
//
//    Operative(std::string nm, Characteristics c, Cell *ncell, int acc, int stth, Weapon *weapon) :
//            Character(std::move(nm), c, ncell, TypeOfCreature::operative, Side::player),
//            strength(stth),
//            accuracy(acc),
//            inventory(),
//            activeWeapon(weapon) {};
//
//    Operative(std::string nm, Characteristics c, Cell *ncell, int acc, int stth) :
//            Character(std::move(nm), c, ncell, TypeOfCreature::operative, Side::player),
//            strength(stth),
//            accuracy(acc),
//            inventory(),
//            activeWeapon(new Weapon()) {};
//
//    [[nodiscard]] int getStrength() const { return strength; };
//
//    [[nodiscard]] int getAccuracy() const { return accuracy; };
//
//    [[nodiscard]] Weapon *getActiveWeapon() const { return activeWeapon; }
//
//    Operative &setStrength(const int nstrength) {
//        strength = nstrength;
//        return *this;
//    }
//
//    Operative &setAccuracy(const int nstrength) {
//        strength = nstrength;
//        return *this;
//    }
//
//    [[nodiscard]] Inventory getInventory() const { return inventory; }
//
//    int useItem(Item *item);
//
//    Operative &setActiveWeapon(const Weapon *weapon) {
//        *activeWeapon = *weapon;
//        return *this;
//    };
//
//    void takeItem(Item *nItem) override;
//
//    void dropItem(int index) override;
//
//    void throwWeapon() override;
//
//    void takeWeapon(Weapon &weapon1) override;
//
//    [[nodiscard]] int getCurrentWeight() const { return inventory.getCurrentWeight(); };
//
//    Character &move(std::vector<Cell *> points, Matrix<Cell> matr) override;
//
//    void reload();
//
//    friend std::ostream &operator<<(std::ostream &c, Operative &oper);
//
//    void Dead() override;
//
//    bool canAttack() override;
//
//    bool canAttackToCell(Cell *cell, std::vector<Cell *> points) override;
//};
//
//
//#endif //LAB3_CPP_OPERATIVE_H
