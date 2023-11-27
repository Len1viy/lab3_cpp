//
// Created by vadim on 24.10.2023.
//

#ifndef LAB3_CPP_ENEMY_H
#define LAB3_CPP_ENEMY_H

#include <utility>
#include "../Character.h"

/**
 * @brief Expandable enemy class
 */
class Enemy : public Character {
public:
    /**
     * @brief Constructor of Enemy by type
     * @param type Type of creature
     */
    Enemy(TypeOfCreature type) : Character(type) {};
    /**
     * @brief Constructor of Enemy by all parameters
     * @param nm name of creature
     * @param c characteristics of creature
     * @param ncell cell for spawn enemy on the map
     * @param t type of creature
     * @param s side of creature
     */
    Enemy(std::string nm, Characteristics c, Cell *ncell, TypeOfCreature t, Side s) :
            Character(std::move(nm), c, ncell, t, s) {};

//    virtual std::ostream &print(std::ostream &) = 0;

//    friend std::ostream &operator<<(std::ostream &c, Enemy &enemy);
    /**
     * @brief Algorithm Lee for finding the shortest path to target
     * @param matr The map of level
     * @param to The target for going
     * @return Way to target if it is possible and empty vector if it isn't, for one tick move u need to use [1] element of way
     */
    std::vector<Cell *> lee(Matrix<Cell> &matr, Cell *to);

    /**
     * @brief pure virtual function of enemie's move. For override you need to write all of the logic of moving enemy
     * @param matr Map of level
     * @param iSeeEnemies Vector of player's characters which enemy can see around of it
     * @return Our enemy which has moved
     */

    virtual Character &move1(Matrix<Cell> &matr, std::vector<Character *> iSeeEnemies) = 0;

};


#endif //LAB3_CPP_ENEMY_H
