//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_LEVEL_H
#define LAB3_CPP_LEVEL_H


#include "../Character/Kinds/Operative.h"
#include "../Character/Kinds/Enemy.h"
#include "../Character/Kinds/Forager.h"
#include "../Character/Kinds/Reasonable.h"
#include "../Character/Kinds/Wild.h"

#include "Cell.h"
#include "../Matrix.h"

namespace level {
    typedef enum Side{
        player,
        enemy
    } Side;

    class Level {
    private:
        matrix::Matrix<Cell> matr;
        std::vector<character::Operative*> characters;
        std::vector<character::Enemy*> enemies;
        Side move;
    public:
        Level(int rows, int cols) : matr(matrix::Matrix<Cell>(rows, cols)), characters(), enemies(), move(Side::player) {};
        Level &changeSize(const int nr, const int nc);
        Level &createCharacter();
        Level &createEnemy(character::TypeOfCreature type);
        Level &changeMove();
        character::Character *chooseCharacterForMove(level::Side type);
    };
}

#endif //LAB3_CPP_LEVEL_H
