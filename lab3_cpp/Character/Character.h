//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_CHARACTER_H
#define LAB3_CPP_CHARACTER_H


#include <utility>

#include "iostream"
#include "../Level/Point.h"
#include "../Level/Cell.h"
#include "../Interfaces/Attack.h"
#include "../Interfaces/UserInventory.h"
#include "../Interfaces/UserWeapon.h"
#include "../Level/Matrix.h"

typedef enum TypeOfCreature {
    operative,
    forager,
    reasonable,
    wild,
} TypeOfCreature;

class Characteristics {
public:
    int currentHealth;
    int maxHealth;
    int currentTime;
    int maxTime;
    int pointsForStep;
    int radius;

    Characteristics(int nCurrentHealth, int nMaxHealth, int nCurrentTime, int nMaxTime, int nPointsForStep,
                    int nRadius) :
            currentHealth(nCurrentHealth),
            maxHealth(nMaxHealth),
            currentTime(nCurrentTime),
            maxTime(nMaxTime),
            pointsForStep(nPointsForStep),
            radius(nRadius) {};

    Characteristics() : currentHealth(100), maxHealth(100), currentTime(50), maxTime(50), pointsForStep(10),
                        radius(5) {};

    Characteristics(Characteristics &c) {
        currentHealth = c.currentHealth;
        maxHealth = c.maxHealth;
        currentTime = c.currentTime;
        maxTime = c.maxTime;
        pointsForStep = c.pointsForStep;
        radius = c.radius;
    }

    bool operator==(const Characteristics &c) const {
        if (c.currentHealth == currentHealth && c.maxHealth == maxHealth && c.currentTime == currentTime &&
            c.maxTime == maxTime &&
            c.pointsForStep == pointsForStep && c.radius == radius
                )
            return true;
        return false;
    }
};

class Character {
private:
    TypeOfCreature type;
    std::string name;
    Characteristics characteristics;
    Side side;
    Cell *cell;
public:
    Character() : type(TypeOfCreature::operative), name(), characteristics(), side(Side::player),
                  cell(nullptr) {};
    Character(TypeOfCreature type) : type(type), name(), characteristics(), side(Side::player),
                  cell(nullptr) {};

    Character(std::string nm, Characteristics c, Cell *ncell) :
            type(TypeOfCreature::operative),
            name(std::move(nm)),
            characteristics(c),
            side(Side::player),
            cell(ncell) {};

    Character(std::string nm, Characteristics c, Cell *ncell, TypeOfCreature t, Side s) :
            type(t),
            name(std::move(nm)),
            characteristics(c),
            side(s),
            cell(ncell) {};

    [[nodiscard]] TypeOfCreature getType() const { return type; };

    [[nodiscard]] Side getSide() const { return side; }

    Character &setType(const TypeOfCreature t) {
        type = t;
        return *this;
    }


    [[nodiscard]] Cell *getCell() const { return cell; }

    Character &setCell(Cell *c) {
//        if (cell != nullptr) {
//            cell->changeStatus();
//        }
//        c->changeStatus();
        cell = c;
        return *this;
    }

    [[nodiscard]] std::string getName() const { return name; }

    Character &setName(std::string nname) {
        name = std::move(nname);
        return *this;
    }

    Characteristics getCharacteristics() { return characteristics; };

    [[nodiscard]] int getHealth() const { return characteristics.currentHealth; }

    Character &setHealth(const int health) {
        characteristics.currentHealth = health;
        return *this;
    }

    [[nodiscard]] int getMaxHealth() const { return characteristics.maxHealth; }

    Character &setMaxHealth(const int health) {
        characteristics.maxHealth = health;
        return *this;
    }

    [[nodiscard]] int getPointsForStep() const { return characteristics.pointsForStep; };

    Character &setPointsForStep(const int points) {
        characteristics.pointsForStep = points;
        return *this;
    }

    [[nodiscard]] int getMaxTime() const { return characteristics.maxTime; }

    [[nodiscard]] int getTime() const { return characteristics.currentTime; }

    Character &setTime(const int time) {
        characteristics.currentTime = time;
        return *this;
    }

    Character &setMaxTime(const int time) {
        characteristics.maxTime = time;
        return *this;
    }

    [[nodiscard]] int getRadius() const { return characteristics.radius; };

    Character &setRadius(const int nrad) {
        characteristics.radius = nrad;
        return *this;
    }


    Character &changeHealth(int healthOut, int operation);

    Character &changeTime(int time, int operation);

//    virtual Character &move(std::vector<Cell *> points) = 0;


    int way(Cell *from, Cell *to);

    [[nodiscard]] bool isDead() const {
        if (characteristics.currentHealth == 0) return true;
        return false;
    }

    [[nodiscard]] int getX() const {
        return getCell()->getPoint().x;
    }

    [[nodiscard]] int getY() const {
        return getCell()->getPoint().y;
    }


    friend std::ostream &operator<<(std::ostream &c, Character *character);

    virtual bool canAttackToCell(Cell *cell, std::vector<Cell *> points) { return false; }

    virtual bool canAttack() { return false; }

    virtual void Dead() = 0;


//        static bool isSeeSmb(level::Cell &cl);



    std::vector<Cell *> iSee(Matrix<Cell> &matr);
};

// character

#endif //LAB3_CPP_CHARACTER_H



////
//// Created by vadim on 16.10.2023.
////
//
//#ifndef LAB3_CPP_CHARACTER_H
//#define LAB3_CPP_CHARACTER_H
//
//
//#include <utility>
//
//#include "iostream"
//#include "../Level/Point.h"
//#include "../Level/Cell.h"
//#include "../Interfaces/Attack.h"
//#include "../Interfaces/UserInventory.h"
//#include "../Interfaces/UserWeapon.h"
//#include "../Level/Matrix.h"
//
//typedef enum TypeOfCreature {
//    operative,
//    forager,
//    reasonable,
//    wild,
//} TypeOfCreature;
//
//class Characteristics {
//public:
//    int currentHealth;
//    int maxHealth;
//    int currentTime;
//    int maxTime;
//    int pointsForStep;
//    int radius;
//
//    Characteristics(int nCurrentHealth, int nMaxHealth, int nCurrentTime, int nMaxTime, int nPointsForStep,
//                    int nRadius) :
//            currentHealth(nCurrentHealth),
//            maxHealth(nMaxHealth),
//            currentTime(nCurrentTime),
//            maxTime(nMaxTime),
//            pointsForStep(nPointsForStep),
//            radius(nRadius) {};
//
//    Characteristics() : currentHealth(100), maxHealth(100), currentTime(50), maxTime(50), pointsForStep(10),
//                        radius(5) {};
//
//    Characteristics(Characteristics &c) {
//        currentHealth = c.currentHealth;
//        maxHealth = c.maxHealth;
//        currentTime = c.currentTime;
//        maxTime = c.maxTime;
//        pointsForStep = c.pointsForStep;
//        radius = c.radius;
//    }
//
//    bool operator==(const Characteristics &c) const {
//        if (c.currentHealth == currentHealth && c.maxHealth == maxHealth && c.currentTime == currentTime &&
//            c.maxTime == maxTime &&
//            c.pointsForStep == pointsForStep && c.radius == radius
//                )
//            return true;
//        return false;
//    }
//};
//
//class Character {
//private:
//    TypeOfCreature type;
//    std::string name;
//    Characteristics characteristics;
//    Side side;
//    Cell *cell;
//public:
//    Character() : type(TypeOfCreature::operative), name(), characteristics(), side(Side::player),
//                  cell(nullptr) {};
//
//    Character(std::string nm, Characteristics c, Cell *ncell) :
//            type(TypeOfCreature::operative),
//            name(std::move(nm)),
//            characteristics(c),
//            side(Side::player),
//            cell(ncell) {};
//
//    Character(std::string nm, Characteristics c, Cell *ncell, TypeOfCreature t, Side s) :
//            type(t),
//            name(std::move(nm)),
//            characteristics(c),
//            side(s),
//            cell(ncell) {};
//
//    [[nodiscard]] TypeOfCreature getType() const { return type; };
//
//    [[nodiscard]] Side getSide() const { return side; }
//
//    Character &setType(const TypeOfCreature t) {
//        type = t;
//        return *this;
//    }
//
//
//    [[nodiscard]] Cell *getCell() const { return cell; }
//
//    Character &setCell(Cell *c) {
//        cell = c;
//        return *this;
//    }
//
//    [[nodiscard]] std::string getName() const { return name; }
//
//    Character &setName(std::string nname) {
//        name = std::move(nname);
//        return *this;
//    }
//
//    Characteristics getCharacteristics() { return characteristics; };
//
//    [[nodiscard]] int getHealth() const { return characteristics.currentHealth; }
//
//    Character &setHealth(const int health) {
//        characteristics.currentHealth = health;
//        return *this;
//    }
//
//    [[nodiscard]] int getMaxHealth() const { return characteristics.maxHealth; }
//
//    Character &setMaxHealth(const int health) {
//        characteristics.maxHealth = health;
//        return *this;
//    }
//
//    [[nodiscard]] int getPointsForStep() const { return characteristics.pointsForStep; };
//
//    Character &setPointsForStep(const int points) {
//        characteristics.pointsForStep = points;
//        return *this;
//    }
//
//    [[nodiscard]] int getMaxTime() const { return characteristics.maxTime; }
//
//    [[nodiscard]] int getTime() const { return characteristics.currentTime; }
//
//    Character &setTime(const int time) {
//        characteristics.currentTime = time;
//        return *this;
//    }
//
//    Character &setMaxTime(const int time) {
//        characteristics.maxTime = time;
//        return *this;
//    }
//
//    [[nodiscard]] int getRadius() const { return characteristics.radius; };
//
//    Character &setRadius(const int nrad) {
//        characteristics.radius = nrad;
//        return *this;
//    }
//
//
//    Character &changeHealth(int healthOut, int operation);
//
//    Character &changeTime(int time, int operation);
//
//    virtual Character &move(std::vector<Cell *> points, Matrix<Cell> matr) = 0;
//
//    int way(Cell *from, Cell *to);
//
//    [[nodiscard]] bool isDead() const {
//        if (characteristics.currentHealth == 0) return true;
//        return false;
//    }
//
//    [[nodiscard]] int getX() const {
//        return getCell()->getPoint().x;
//    }
//
//    [[nodiscard]] int getY() const {
//        return getCell()->getPoint().y;
//    }
//
//
//    friend std::ostream &operator<<(std::ostream &c, Character *character);
//
//    virtual bool canAttackToCell(Cell *cell, std::vector<Cell *> points) { return false; }
//
//    virtual bool canAttack() { return false; }
//
//    virtual void Dead() = 0;
//
//
////        static bool isSeeSmb(level::Cell &cl);
//
//
//    void findPath(Cell *to, std::vector<Cell *> points, int &length, Cell *target);
//};
//
//// character
//
//#endif //LAB3_CPP_CHARACTER_H
