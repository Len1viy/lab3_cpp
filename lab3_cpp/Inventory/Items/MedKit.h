//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_MEDKIT_H
#define LAB3_CPP_MEDKIT_H

#include "Item.h"


class MedKit : public Item {
private:
    int health;
    int pointsForUsing;
public:
    /**
     * @brief Default constructor
     */
    MedKit() : Item(TypeOfItem::medKit, 10), health(20), pointsForUsing(10) {};
/**
 * @brief Constructor
 * @param n Type of item
 * @param w weight of item
 * @param h health which this med kit will add
 * @param p points for using
 */
    MedKit(TypeOfItem n, int w, int h, int p) : Item(n, w), health(h), pointsForUsing(p) {}
/**
 * @brief getter of health which med kit will add
 * @return health which med kit will add
 */
    [[nodiscard]] int getHealth() const { return health; };
/**
 * @brief setter of health which med kit will add
 * @param nhealth health which med kit will add
 * @return changed MedKit
 */
    MedKit &setHealth(int nhealth) {
        health = nhealth;
        return *this;
    }
/**
 * @brief getter of points of time for using
 * @return points for using
 */
    [[nodiscard]] int getPointsForUsing() const { return pointsForUsing; };
/**
 * @brief setter of points of time for using
 * @param p new points of time for using
 * @return changed med kit
 */
    MedKit &setPointsForUsing(int p) {
        pointsForUsing = p;
        return *this;
    };
//    std::ostream &print(std::ostream &c) override;
/**
 * @brief using medkit. if all of the conditions were met, this method add health to oper
 * @param oper - Operative which uses med kit
 * @return points for using
 */
    int use(Operative &oper) override;
/**
 * @brief overloaded operator ==
 * @param medKit - other med kit for compare
 * @return true if medkits are equal and false otherwise
 */
    bool operator==(const MedKit &medKit) const;

};


#endif //LAB3_CPP_MEDKIT_H
