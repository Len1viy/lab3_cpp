//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_ITEM_H
#define LAB3_CPP_ITEM_H

#include "iostream"
#include "../../Character/Character.h"


namespace inventory {
    typedef enum TypeOfItem {
        weapon,
        containerForBullets,
        medKit,
    } TypeOfItem;

    class Item {
    private:
         TypeOfItem name;
         int weight;
         character::Character *owner;
    public:
        Item(TypeOfItem n, int w) : name(n), weight(w) {}
        TypeOfItem getName() const {return name;};
        Item &setName(const TypeOfItem nname) {
            name = nname;
            return *this;
        }
        int getWeight() const {return weight;};
        Item &setWeight(const int nweight) {
            weight = nweight;
            return *this;
        }
        character::Character &getOwner() const { return *owner; };
        Item &setOwner(character::Character *character) {
            owner = character;
            return *this;
        }
        virtual bool isOwner();
    };

} // game

#endif //LAB3_CPP_ITEM_H
