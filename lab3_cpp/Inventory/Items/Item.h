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
    /**
     * @brief Default constructor
     */
    Item() : name(), weight(0) {};

    /**
     * @brief Constructor
     * @param n type of item
     * @param w weight of item
     */

    Item(TypeOfItem n, int w) : name(n), weight(w) {}
/**
 * @brief getter of type
 * @return type of item
 */

    [[nodiscard]] TypeOfItem getName() const { return name; };
/**
 * @brief setter of name
 * @param nname new name which we want to set
 * @return changed item
 */
    Item &setName(const TypeOfItem nname) {
        name = nname;
        return *this;
    }
/**
 * @brief getter of weight
 * @return weight of item
 */
    [[nodiscard]] int getWeight() const { return weight; };
/**
 * @brief setter if weight
 * @param nweight new weight which we want to set
 * @return changed item
 */
    Item &setWeight(const int nweight) {
        weight = nweight;
        return *this;
    }
/**
 * @brief pure virtual function of using items
 * @param oper - oper which has used item
 * @return points for using
 */
    virtual int use(Operative &oper) = 0;
//    virtual std::ostream &print(std::ostream &) = 0;
/**
 * @brief move constructor of item
 * @param element item which we will move
 */
    Item(Item &&element) noexcept: name(element.name), weight(element.weight) {};
/**
 * @brief copy constructor of item
 * @param element item which we will copy
 */
    Item(Item &element) noexcept: name(element.name), weight(element.weight) {};

//    friend std::ostream& operator<<(std::ostream &c, Item &item);
};


#endif //LAB3_CPP_ITEM_H
