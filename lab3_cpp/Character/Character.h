//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_CHARACTER_H
#define LAB3_CPP_CHARACTER_H

#include "iostream"
#include "../Level/Point.h"
#include "../Level/Level.h"
#include "../Interfaces/UserInventory.h"
#include "../Interfaces/UserWeapon.h"
#include "../Interfaces/Attack.h"

namespace character {

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
        Characteristics(int nCurrentHealth, int nMaxHealth, int nCurrentTime, int nMaxTime, int nPointsForStep, int nRadius) :
        currentHealth(nCurrentHealth),
        maxHealth(nMaxHealth),
        currentTime(nCurrentTime),
        maxTime(nMaxTime),
        pointsForStep(nPointsForStep),
        radius(nRadius) {};

        Characteristics(Characteristics &c) {
            currentHealth = c.currentHealth;
            maxHealth = c.maxHealth;
            currentTime = c.currentTime;
            maxTime = c.maxTime;
            pointsForStep = c.pointsForStep;
            radius = c.radius;
        }
    };

    class Character {
    private:
        TypeOfCreature type;
        std::string name;
        Characteristics characteristics;
        level::Side side;
    protected:
        Point point;
        level::Cell *cell;
    public:
        Character(std::string nm, Characteristics c, Point p) :
                name(nm),
                characteristics(c),
                point(p) {};
        Character(std::string nm, Characteristics c, Point p, TypeOfCreature t, level::Side s) :
                type(t),
                name(nm),
                characteristics(c),
                side(s),
                point(p)
        {};

        TypeOfCreature getType() const { return type; };

        Character &setType(const TypeOfCreature t) {
            type = t;
            return *this;
        }

        std::string getName() const { return name; }

        Character &setName(const std::string nname) {
            name = nname;
            return *this;
        }

        Characteristics getCharacteristics() { return characteristics; };

        int getHealth() const { return characteristics.currentHealth; }

        Character &setHealth(const int health) {
            characteristics.currentHealth = health;
            return *this;
        }

        int getMaxHealth() const { return characteristics.maxHealth; }

        Character &setMaxHealth(const int health) {
            characteristics.maxHealth = health;
            return *this;
        }

        int getPointsForStep() const { return characteristics.pointsForStep; };

        Character &setPointsForStep(const int points) {
            characteristics.pointsForStep = points;
            return *this;
        }

        int getMaxTime() const { return characteristics.maxTime; };

        Character &setMaxTime(const int time) {
            characteristics.maxTime = time;
            return *this;
        }

        int getRadius() const { return characteristics.radius; };

        Character &setRadius(const int nrad) {
            characteristics.radius = nrad;
            return *this;
        }

        level::Cell *getCell() const { return cell; };

        Character &setCell(level::Cell *cl) {
            cell = cl;
            return *this;
        };

        Character &changeHealth(int healthOut, int operation);

        Character &changeTime(int time, int operation);

        virtual Character &move(Point npoint) = 0;

        bool isSeeSmb(level::Cell &cl);

    };

} // character

#endif //LAB3_CPP_CHARACTER_H
