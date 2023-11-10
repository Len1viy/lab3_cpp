//
// Created by vadim on 24.10.2023.
//

#ifndef LAB3_CPP_ENEMY_H
#define LAB3_CPP_ENEMY_H

#include "../../Interfaces/Attack.h"


namespace character {


    class Enemy : public Character {
    public:
        Enemy(std::string nm, Characteristics c, Point p, TypeOfCreature t, level::Side s) :
        Character(nm, c, p, t, s)
        {};
    };
}



#endif //LAB3_CPP_ENEMY_H
