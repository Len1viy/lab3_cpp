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

/**
 * @brief class which contains all of the information about characteristics
 */

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

    /*
     * @brief copy constructor
     * @param c Characteristics which we want to copy
     */
    Characteristics(Characteristics &c) {
        currentHealth = c.currentHealth;
        maxHealth = c.maxHealth;
        currentTime = c.currentTime;
        maxTime = c.maxTime;
        pointsForStep = c.pointsForStep;
        radius = c.radius;
    }


    bool operator==(const Characteristics &c) const {
        return c.currentHealth == currentHealth && c.maxHealth == maxHealth && c.currentTime == currentTime &&
               c.maxTime == maxTime &&
               c.pointsForStep == pointsForStep && c.radius == radius;
    }
};
/**
 * @brief base class of all of the alive creatures in the game
 */
class Character {
private:
    TypeOfCreature type;
    std::string name;
    Characteristics characteristics;
    Side side;
    Cell *cell;
public:
    /**
     * @brief Default constructor of character. Creates the Operative
     */
    Character() : type(TypeOfCreature::operative), name(), characteristics(), side(Side::player),
                  cell(nullptr) {};

    /**
     * @brief Constructor
     * @param type - type of character
     */
    Character(TypeOfCreature type) : type(type), name(), characteristics(), side(Side::player),
                                     cell(nullptr) {};

    /**
     * @brief Constructor
     * @param nm - name of character
     * @param c - characteristics of character
     * @param ncell - cell on which character will stay
     */
    Character(std::string nm, Characteristics c, Cell *ncell) :
            type(TypeOfCreature::operative),
            name(std::move(nm)),
            characteristics(c),
            side(Side::player),
            cell(ncell) {};

    /**
     * @brief Constructor
     * @param nm - name of character
     * @param c - characteristics of character
     * @param ncell  - cell on which character will stay
     * @param t - type of character
     * @param s - the side the character belongs to
     */
    Character(std::string nm, Characteristics c, Cell *ncell, TypeOfCreature t, Side s) :
            type(t),
            name(std::move(nm)),
            characteristics(c),
            side(s),
            cell(ncell) {};

    /**
     * @brief getter of type of character
     * @return the type of character
     */
    [[nodiscard]] TypeOfCreature getType() const { return type; };

    /**
     * @brief getter of side
     * @return the side the character belongs to
     */
    [[nodiscard]] Side getSide() const { return side; }

    /**
     * @brief setter of type of creature
     * @param t - type of creature
     * @return our changed character
     */
    Character &setType(const TypeOfCreature t) {
        type = t;
        return *this;
    }

    /**
     * @brief getter of cell
     * @return pointer of sell on which character stays
     */
    [[nodiscard]] Cell *getCell() const { return cell; }

    /**
     * @brief setter of cell
     * @param c - pointer of the cell which we want to set
     * @return our changed character
     */
    Character &setCell(Cell *c) {
        cell = c;
        return *this;
    }

    /**
     * @brief getter of name
     * @return name of the character
     */
    [[nodiscard]] std::string getName() const { return name; }

    /**
     * @brief setter of name
     * @param name - name which we want to set
     * @return our changed character
     */
    Character &setName(std::string nname) {
        name = std::move(nname);
        return *this;
    }

    /**
     * @brief Getter of characteristics
     * @return all of the characteristics
     */
    Characteristics getCharacteristics() { return characteristics; };

    /**
     * @brief Getter of health
     * @return health
     */
    [[nodiscard]] int getHealth() const { return characteristics.currentHealth; }

    /**
     * @brief setter of health
     * @param health - health which we want to set
     * @return our changed character
     */
    Character &setHealth(const int health) {
        characteristics.currentHealth = health;
        return *this;
    }

    /**
     * @brief Getter of max health
     * @return max health
     */

    [[nodiscard]] int getMaxHealth() const { return characteristics.maxHealth; }

    /**
     * @brief setter of max health
     * @param health - max health which we want to set
     * @return our changed character
     */
    Character &setMaxHealth(const int health) {
        characteristics.maxHealth = health;
        return *this;
    }

    /**
     * @brief Getter of points for step
     * @return points for step
     */
    [[nodiscard]] int getPointsForStep() const { return characteristics.pointsForStep; };

    /**
     * @brief setter of points of step
     * @param points - points which we want to set
     * @return our changed character
     */

    Character &setPointsForStep(const int points) {
        characteristics.pointsForStep = points;
        return *this;
    }


    /**
     * @brief Getter of maxTime
     * @return max time which we want to get
     */

    [[nodiscard]] int getMaxTime() const { return characteristics.maxTime; }

    /**
     * @brief Getter of time
     * @return time which we want to get
     */

    [[nodiscard]] int getTime() const { return characteristics.currentTime; }

    /**
     * @brief Setter of time
     * @param time - time which we want to set
     * @return our changed character
     */
    Character &setTime(const int time) {
        characteristics.currentTime = time;
        return *this;
    }

    /**
     * @brief Setter of maxTime
     * @param time max time which we want to set
     * @return our changed character
     */


    Character &setMaxTime(const int time) {
        characteristics.maxTime = time;
        return *this;
    }

    /**
     * @brief getter of radius
     */
    [[nodiscard]] int getRadius() const { return characteristics.radius; };

    /**
     * @brief Setter of radius
     * @param nrad radius which we want to set
     * @return our changed character
     */

    Character &setRadius(const int nrad) {
        characteristics.radius = nrad;
        return *this;
    }

    /**
     * @brief function which changes character's health
     * @param healthOut count of health which will add or diminish
     * @param operation sign of changing. -1 if health will diminish; 1 if health will add
     * @return our changed character
     */

    Character &changeHealth(int healthOut, int operation);

    /**
     * @brief function which changes character's health
     * @param time count of time which will add or diminish
     * @param operation sign of changing. -1 if health will diminish; 1 if health will add
     * @return our changed character
     */

    Character &changeTime(int time, int operation);


    /**
     * @brief function which finding the count of points from one Cell to the other
     * @param from Cell which define the start of the way
     * @param to Cell which define the end of the way
     */
    int way(Cell *from, Cell *to);

    [[nodiscard]] bool isDead() const {
        if (characteristics.currentHealth == 0) return true;
        return false;
    }

    /**
     * @brief getter of X component of position
     * @return X component of position
     */


    [[nodiscard]] int getX() const {
        return getCell()->getPoint().x;
    }

    /**
     * @brief getter of Y component of position
     * @return Y component of position
     */

    [[nodiscard]] int getY() const {
        return getCell()->getPoint().y;
    }


    friend std::ostream &operator<<(std::ostream &c, Character *character);

// по умолчанию удалить клетку под персонажем
// более подробное описание
    /**
     * @brief pure virtual function which describes the state of items after character's dead and delete the cell under character. For override function u need to describe all of the functional which u want to have after character's death
     */
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
