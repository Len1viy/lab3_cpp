//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_MEDKIT_H
#define LAB3_CPP_MEDKIT_H

#include "Item.h"

namespace inventory {

    class MedKit : Item {
    private:
        int health;
        int pointsForUsing;
    public:
        MedKit(TypeOfItem n, int w, int h, int p) : Item(n, w), health(h), pointsForUsing(p) {}
        int getHealth() const {return health;};
        MedKit &setHealth(int nhealth) {
            health = nhealth;
            return *this;
        }
        int getPointsForUsing() const {return pointsForUsing;};
        MedKit &setPointsForUsing(int p) {
            pointsForUsing = p;
            return *this;
        };

    };

}



#endif //LAB3_CPP_MEDKIT_H
