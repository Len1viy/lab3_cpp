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
    MedKit() : Item(TypeOfItem::medKit, 10), health(20), pointsForUsing(10) {};

    MedKit(TypeOfItem n, int w, int h, int p) : Item(n, w), health(h), pointsForUsing(p) {}

    [[nodiscard]] int getHealth() const { return health; };

    MedKit &setHealth(int nhealth) {
        health = nhealth;
        return *this;
    }

    [[nodiscard]] int getPointsForUsing() const { return pointsForUsing; };

    MedKit &setPointsForUsing(int p) {
        pointsForUsing = p;
        return *this;
    };
//    std::ostream &print(std::ostream &c) override;
    int use(Operative &oper) override;

    bool operator==(const MedKit &medKit) const;

};


#endif //LAB3_CPP_MEDKIT_H
