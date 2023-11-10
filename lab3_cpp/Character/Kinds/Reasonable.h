//
// Created by vadim on 08.11.2023.
//

#ifndef LAB3_CPP_REASONABLE_H
#define LAB3_CPP_REASONABLE_H

#include <iostream>
#include "Enemy.h"

namespace character {

    class Reasonable : public Enemy, public interface::UserWeapon, public interface::Attack {
    private:
        inventory::Weapon *activeWeapon;
        int accuracy;
        std::vector<Point> stocks;

    public:
        Reasonable(std::string nm, Characteristics c, Point p, int acc, std::vector<Point> st) :
            Enemy(nm, c, p, TypeOfCreature::reasonable, level::Side::enemy),
            accuracy(acc),
            stocks(st)
        {};
        Reasonable(std::string nm, Characteristics c, Point p) : Enemy(nm, c, p, TypeOfCreature::reasonable, level::Side::enemy) {};
        Reasonable(std::string nm, Characteristics c, Point p, int acc, inventory::Weapon *weapon,  std::vector<Point> st) :
        Enemy(nm, c, p, TypeOfCreature::reasonable, level::Side::enemy), activeWeapon(weapon), accuracy(acc), stocks(st) {};



        int getAccuracy() const { return accuracy; }

        Reasonable &setAccuracy(const int naccuracy) {
            accuracy = naccuracy;
            return *this;
        }

        inventory::Weapon getActiveWeapon() const { return *activeWeapon; }

        Reasonable &setActiveWeapon(inventory::Weapon weapon) {
            activeWeapon = &weapon;
            return *this;
        }

        void attack(character::Character *enemy) override;

        void throwWeapon() override;

        void takeWeapon(int index) override;

        int getDamage() override;

        Character &move(Point npoint) override;

    };

} // character

#endif //LAB3_CPP_REASONABLE_H
