//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_OPERATIVE_H
#define LAB3_CPP_OPERATIVE_H
#include "iostream"
#include "../../Interfaces/Attack.h"


namespace character {

    class Operative : public Character, public interface::UserWeapon, public interface::InventoryUser, public interface::Attack {
    private:
        int strength;
        int accuracy;
        inventory::Inventory inventory;
        inventory::Weapon *activeWeapon;
    public:
        void attack(character::Character *enemy) override;

        Operative(std::string nm, Characteristics c, Point p, int acc, int stth, inventory::Weapon *weapon) :
        Character(nm, c, p, TypeOfCreature::operative, level::Side::player),
        strength(stth),
        accuracy(acc),
        activeWeapon(weapon)
        {};

        Operative(std::string nm, Characteristics c, Point p, int acc, int stth) :
                Character(nm, c, p, TypeOfCreature::operative, level::Side::player),
                strength(stth),
                accuracy(acc)
        {};

        int getStrength() const { return strength; };
        int getAccuracy() const { return accuracy; };
        Operative &setStrength(const int nstrength) {
            strength = nstrength;
            return *this;
        }
        Operative &setAccuracy(const int nstrength) {
            strength = nstrength;
            return *this;
        }
        int getWearableWeight() const {
            return inventory.getCurrentWeight();
        };
        Operative &setActiveWeapon(inventory::Weapon &weapon) {
            activeWeapon = &weapon;
            return *this;
        };
        void takeItem(int index) override;
        void dropItem(int index) override;
        void throwWeapon() override;
        void takeWeapon(int index) override;

        int getDamage() override;

        int getCurrentWeight() const { return inventory.getCurrentWeight(); };
        int useItem(inventory::Item *item);
        Character &move(Point npoint) override;
    };

} // character

#endif //LAB3_CPP_OPERATIVE_H
