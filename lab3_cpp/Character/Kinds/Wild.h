//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_WILDCREATURE_H
#define LAB3_CPP_WILDCREATURE_H
#include <iostream>
#include "Enemy.h"


namespace character {

    class Wild : public Enemy, public interface::Attack {
    private:
        int accuracy;
        int minDamage;
        int maxDamage;
    public:
        void attack(character::Character *enemy) override;

        Wild(std::string nm, Characteristics c, Point p, int acc, int minD, int maxD) :
        Enemy(nm, c, p, TypeOfCreature::wild, level::Side::enemy),
        accuracy(acc),
        minDamage(minD),
        maxDamage(maxD)
        {};
        int getAccuracy() const {return accuracy;};
        Wild &setAccuracy(int naccuracy) {
            accuracy = naccuracy;
            return *this;
        };
        int getDamage() override;
        int getMaxDamage() const { return maxDamage; };
        Wild &setMaxDamage(int nMaxDamage) {
            maxDamage = nMaxDamage;
            return *this;
        }
        int getMinDamage() const { return minDamage; };
        Wild &setMinDamage(int nMinDamage) {
            minDamage = nMinDamage;
            return *this;
        };

        Character &move(Point npoint) override;
    };

} // character

#endif //LAB3_CPP_WILDCREATURE_H
