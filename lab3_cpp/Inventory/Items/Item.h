//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_ITEM_H
#define LAB3_CPP_ITEM_H

#include "iostream"

class Operative;

typedef enum BulletType {
    assault,
    sniper,
    expansive,
    pistol,
    none
} BulletType;

typedef enum TypeOfItem {
    weapon,
    containerForBullets,
    medKit,
} TypeOfItem;

class Item {
private:
    TypeOfItem name;
    int weight;
public:
    Item() : name(), weight(0) {};

    Item(TypeOfItem n, int w) : name(n), weight(w) {}

    [[nodiscard]] TypeOfItem getName() const { return name; };

    Item &setName(const TypeOfItem nname) {
        name = nname;
        return *this;
    }

    [[nodiscard]] int getWeight() const { return weight; };

    Item &setWeight(const int nweight) {
        weight = nweight;
        return *this;
    }

    virtual int use(Operative &) = 0;
//    virtual std::ostream &print(std::ostream &) = 0;

    Item(Item &&element) noexcept: name(element.name), weight(element.weight) {};

    Item(Item &element) noexcept: name(element.name), weight(element.weight) {};

//    friend std::ostream& operator<<(std::ostream &c, Item &item);
};


#endif //LAB3_CPP_ITEM_H
