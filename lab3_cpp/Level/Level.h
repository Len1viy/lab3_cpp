
//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_LEVEL_H
#define LAB3_CPP_LEVEL_H

//#include "Point.h"
//#include "Cell.h"
#include "../Character/Character.h"
#include "../Character/Kinds/Operative.h"
#include "Matrix.h"
#include "../Character/Kinds/Enemy.h"
#include "map"
//#include "../Character/Kinds/Forager.h"
//#include "../Character/Kinds/Wild.h"
//#include "../Character/Kinds/Reasonable.h"

/**
 * @brief class of level of the game which contains all of the information about game and does ticks of the game
 */
class Level {
private:
    Matrix<Cell> matr;
    std::map<Cell *, Operative *> characters;
    std::map<Cell *, Enemy *> enemies;
    Side side;
public:
    /**
     * @brief constructor
     * @param rows count of rows on the map
     * @param cols count of columns on the map
     */
    Level(int rows, int cols) : matr(Matrix<Cell>(rows, cols)), characters(), enemies(),
                                side(Side::player) {
        for (auto i = matr.begin(); i != matr.end(); i++) {
            int x = i.getX();
            int y = i.getY();
            if (x == 0 || y == 0 || x == matr.getCols() - 1 || y == matr.getRows() - 1) {
                matr[y][x]->setType(TypeOfPoint::wall);
            }
            matr.getElementByAdress(y, x)->setPoint(y, x);
        }
    }
/**
 * @brief default constructor
 */
    Level() : matr(Matrix<Cell>()), characters(), enemies(), side(Side::player) {};
//
    ~Level() {
//            std::cout << characters.size();
//            for (auto i : characters) {
//                delete [] i;
//            }
    }

    Level(Level &nLevel) : matr(nLevel.matr), characters(nLevel.characters), enemies(nLevel.enemies), side(side) {
        for (auto i = matr.begin(); i != matr.end(); i++) {
            int x = i.getX();
            int y = i.getY();
            if (x == 0 || y == 0 || x == matr.getCols() - 1 || y == matr.getRows() - 1) {
                matr[y][x]->setType(TypeOfPoint::wall);
            }
            matr.getElementByAdress(y, x)->setPoint(y, x);
        }
    }

    /**
     * @brief getter of map
     * @return matrix of cells
     */


    [[nodiscard]] Matrix<Cell> &getMap() {
        return matr;
    }

//        character::Character *chooseCharacterForAttack();
/**
 * @brief does the move/tick of the game
 * @return changed level
 */
    Level &move();
    /**
     * @brief does the logic player's move
     * @return changed level
     */
    Level &movePlayer();
    /**
     * @brief does the logic enemy's move
     * @return changed level
     */
    Level &moveEnemy();
/**
 * @brief random creating operative
 * @return changed level
 */
    Level &createCharacter();
/**
 * @brief random creating enemy by type
 * @param type type of enemy
 * @return changed level
 */
    Level &createEnemy(TypeOfCreature type);
/**
 * @brief pushing character to level
 * @param character operative which we want to add to level
 * @return
 */
    Level &pushCharacter(Operative *character);
/**
 * @brief pushing enemy to level
 * @param enemy enemy which we want to add to level
 * @return changed level
 */
    Level &pushEnemy(Enemy *enemy);

/**
 * @brief getter of std::map of cells and operatives
 * @return std::map of cells and operatives
 */
    [[nodiscard]] std::map<Cell *, Operative *> getOperatives() const {return characters;}
    /**
     * @brief getter of std::map of cells and enemies
     * @return std::map of cells and enemies
     */
    [[nodiscard]] std::map<Cell *, Enemy *> getEnemies() const {return enemies;}
/**
 * @brief method of changing the move
 * @return changed level
 */
    Level &changeMove();

    Operative *chooseCharacterForMove();

    friend std::ostream &operator<<(std::ostream &, Level &);

//    Level &reload(Operative *player);



//    std::vector<Cell *> iSee(int y, int x, int rad);
/**
 * @brief getter of side which does move now
 * @return side
 */
    [[nodiscard]] Side getSide() const {
        return side;
    }


    void printSide() {
        if (side == Side::player) std::cout << "PLAYER";
        else std::cout << "ENEMY";
    }
/// \brief method of choosing character for attack
/// \param enemy vector of character which we can to choose
/// \param index index of character which we want to attack
/// \return character which we have chosen
    static Character *chooseCharacterForAttack(std::vector<Character *> &enemy, int index);

//    int timeOfOpers();
/**
 * @brief method of updating time of characters
 */
    void addTime();
/**
 * @brief method of getting vector of stocks from all of the map
 * @return vector of stocks from all of the map
 */
    std::vector<Cell *> getStocks();

//    std::vector<Character *> seeEnemies(Character *);
/**
 * @brief method which collect all of the enemies which character sees
 * @param ans vector of enemies which the character sees
 * @param i character which try to see somebody around of him
 */
    void seeEnemies(std::vector<Character *> &ans, Character *i);
/**
 * @brief method which allow to choose what action player want to do
 * @param option
 * \li **1** - move to left on the 1 cell
 * \li **2** - move to up on the 1 cell
 * \li **3** - move to right on the 1 cell
 * \li **4** - move to down on the 1 cell
 * \li **5** - to attack someone
 * \li **6** - to take the item
 * \li **7** - to drop the item
 * \li **8** - to take the weapon to hands
 * \li **9** - to throw weapon to the cell on which he stays
 * @param oper - operative who will do the action
 * @return changed level
 */
    Level &makeActionPlayer(std::vector<int> option, Operative *oper);
/**
 * @brief method for choosing item for drop
 * @param inv inventory from which we want to drom smth
 * @return index of item
 */
    static int chooseItemForDrop(Inventory inv);
/**
 * @brief method for choosing the weapon which player want to take from the cell
 * @param cell cell from which player want to take weapon
 * @return weapon which we want to take into the hands
 */
    static Item *chooseWeaponForTake(Cell *cell);

    Level &changeMap();

    Level &changePositionsPlayers();
};

#endif //LAB3_CPP_LEVEL_H
