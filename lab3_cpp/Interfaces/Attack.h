//
// Created by vadim on 24.10.2023.
//

#ifndef LAB3_CPP_ATTACK_H
#define LAB3_CPP_ATTACK_H

#include "../Character/Character.h"


namespace interface {
    class Attack {
    public:

        virtual void attack(character::Character *enemy) = 0;

        virtual int getDamage() = 0;
    };
}



#endif //LAB3_CPP_ATTACK_H
