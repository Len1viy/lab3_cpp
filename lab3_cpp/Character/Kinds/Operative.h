//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_OPERATIVE_H
#define LAB3_CPP_OPERATIVE_H

#include "iostream"
#include "../Character.h"
#include "../../Inventory/Items/MedKit.h"

//class MedKit;

/**
 * @brief class of playable characters by which player plays in the game
 */
class Operative : public Character, public UserWeapon, public InventoryUser, public Attack {
private:
    int strength;
    int accuracy;
    Inventory inventory;
    Weapon *activeWeapon;
public:
    /**
     * Function of getting damage which will applied
     * @return count of damage
     */
    int getDamage() override;
/**
 * @brief default constructor of object of class operative which contains standart accuracy, strangth and pistol in hands
 */
    Operative() : Character(), strength(100), accuracy(100), inventory(), activeWeapon(Weapon::createPistol()) {};
    /**
     * @brief Constructor
     * @param nm operative's name
     * @param c operative's characteristics
     * @param ncell operative's cell on which he will stay
     * @param acc operative's accuracy
     * @param stth operative's strength
     * @param weapon operative's start weapon
     */
    Operative(std::string nm, Characteristics c, Cell *ncell, int acc, int stth, Weapon *weapon) :
            Character(std::move(nm), c, ncell, TypeOfCreature::operative, Side::player),
            strength(stth),
            accuracy(acc),
            inventory(),
            activeWeapon(weapon)
    {};

    /**
     * @brief Constructor
     * @param nm operative's name
     * @param c operative's characteristics
     * @param ncell operative's cell on which he will stay
     * @param acc operative's accuracy
     * @param stth operative's strength
     */
    Operative(std::string nm, Characteristics c, Cell *ncell, int acc, int stth) :
            Character(std::move(nm), c, ncell, TypeOfCreature::operative, Side::player),
            strength(stth),
            accuracy(acc),
            inventory(),
            activeWeapon(Weapon::createPistol())
    {};
    /**
     * @brief getter of strength
     * @return strength
     */

    [[nodiscard]] int getStrength() const { return strength; };
    /**
     * @brief getter of accuracy
     * @return accuracy
     */
    [[nodiscard]] int getAccuracy() const { return accuracy; };
    /**
     * @brief getter of active weapon
     * @return weapon which operative keep in hand
     */
    [[nodiscard]] Weapon *getActiveWeapon() const { return activeWeapon; }
    /**
 * @brief setter of strength
 * @param nstrength new strength which we want to set
 * @return changed operative
 */
    Operative &setStrength(const int nstrength) {
        strength = nstrength;
        return *this;
    }
    /**
     * @brief setter of accuracy
     * @param naccuracy new accuracy which we want to set
     * @return changed operative
     */
    Operative &setAccuracy(const int naccuracy) {
        accuracy = naccuracy;
        return *this;
    }

    [[nodiscard]] Inventory getInventory() const {return inventory;}
    /**
     * @brief method of using item
     * @param item item which will be use
     */
    void useItem(Item *item);

    /**
     * @brief method of using item
     * @param index index of item which will be use
     */
    void useItem(int index);

/**
 * @brief setter of active weapon
 * @param weapon weapon which we want to take in the hands
 * @return changed operative
 */
    Operative &setActiveWeapon(Weapon *weapon) {
//        delete activeWeapon;
//        activeWeapon = new Weapon();
        activeWeapon = weapon;
        return *this;
    };

    /**
     * @brief overrided function of taking items
     * @param nItem item which Forager will take
     */

    void takeItem(Item *nItem) override;
    /**
     * @brief overrided function to drop item to cell
     * @param index index of item which Forager will drop
     */

    void dropItem(int index) override;

    /**
     * @brief function of throwing weapon on cell
     */

    void throwWeapon() override;

    /**
     * function of taking weapon from cell to hands
     * @param weapon1 Weapon which we take
     */

    void takeWeapon(Weapon *weapon1) override;

    [[nodiscard]] int getCurrentWeight() const { return inventory.getCurrentWeight(); };

    /**
     * @brief operative is realoading his weapon
     */
    void reload();
//    friend std::ostream &operator<<(std::ostream &c, Operative &oper);

    void Dead() override;


    bool canAttackToCell(Cell *cell, std::vector<Cell *> points) override;
//    Character &move1(Matrix<Cell> &matr, std::vector<Character *> iSeeEnemies) override;


    void attack(Character *enemy, Matrix<Cell> &matr) override;

    /**
     * @brief overrided function for moving
     * @param direction 1 - to left on 1 point; 2 - to up on 1 point; 3 - to right on 1 point; 4 - to down on 1 point
     * @param matr Map of level
     */
    void move(Direction direction, Matrix<Cell> &matr);

    /**
     * Delete item from inventory by index
     * @param index - index of item which we want to delete
     */
    void deleteFromInventory(int index);

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
