
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


class Level {
private:
    Matrix<Cell> matr;
    std::map<Cell *, Operative *> characters;
    std::map<Cell *, Enemy *> enemies;
    Side side;
public:
    Level(int rows, int cols) : matr(Matrix<Cell>(rows, cols)), characters(), enemies(),
                                side(Side::player) {
        for (auto i = matr.begin(); i != matr.end(); i++) {
            int x = i.getX();
            int y = i.getY();
            matr.getElementByAdress(y, x)->setPoint(y, x);
        }
    }

    Level() : matr(Matrix<Cell>()), characters(), enemies(), side(Side::player) {};
//
    ~Level() {
//            std::cout << characters.size();
//            for (auto i : characters) {
//                delete [] i;
//            }
    }
    [[nodiscard]] Matrix<Cell> &getMap() {
        return matr;
    }

//        character::Character *chooseCharacterForAttack();

    Level &move();
    Level &movePlayer();
    Level &moveEnemy();

    Level &createCharacter();

    Level &createEnemy(TypeOfCreature type);

    Level &pushCharacter(Operative *character);

    Level &pushEnemy(Enemy *enemy);


    [[nodiscard]] std::map<Cell *, Operative *> getOperatives() const {return characters;}
    [[nodiscard]] std::map<Cell *, Enemy *> getEnemies() const {return enemies;}

    Level &changeMove();

    Operative *chooseCharacterForMove();

    friend std::ostream &operator<<(std::ostream &, Level &);

//    Level &reload(Operative *player);



//    std::vector<Cell *> iSee(int y, int x, int rad);
    [[nodiscard]] Side getSide() const {
        return side;
    }


    void printSide() {
        if (side == Side::player) std::cout << "PLAYER";
        else std::cout << "ENEMY";
    }

    static Character *chooseCharacterForAttack(std::vector<Character *> &enemy, int index);

    int timeOfOpers();

    void addTime();

    std::vector<Cell *> getStocks();

//    std::vector<Character *> seeEnemies(Character *);
    void seeEnemies(std::vector<Character *> &ans, Character *i);

    Level &makeActionPlayer(std::vector<int> option, Operative *oper);

    static int chooseItemForDrop(Inventory inv);

    static Item *chooseWeaponForTake(Cell *cell);
};

#endif //LAB3_CPP_LEVEL_H



////
//// Created by vadim on 16.10.2023.
////
//
//#ifndef LAB3_CPP_LEVEL_H
//#define LAB3_CPP_LEVEL_H
//
////#include "Point.h"
////#include "Cell.h"
//#include "../Character/Character.h"
//#include "../Character/Kinds/Operative.h"
//#include "Matrix.h"
//#include "../Character/Kinds/Enemy.h"
//#include "map"
////#include "../Character/Kinds/Forager.h"
////#include "../Character/Kinds/Wild.h"
////#include "../Character/Kinds/Reasonable.h"
//
//
//    class Level {
//    private:
//        Matrix<Cell> matr;
//        std::map<Cell *, Operative *> characters;
//        std::map<Cell *, Enemy *> enemies;
//        Side side;
//    public:
//        Level(int rows, int cols) : matr(Matrix<Cell>(rows, cols)), characters(), enemies(),
//                                    side(Side::player) {
//            for (auto i = matr.begin(); i != matr.end(); i++) {
//                int x = i.getX();
//                int y = i.getY();
//                matr.getElementByAdress(y, x)->setPoint(y, x);
//            }
//        }
//
//        Level() : matr(Matrix<Cell>()), characters(), enemies(), side(Side::player) {};
////
//        ~Level() {
////            std::cout << characters.size();
////            for (auto i : characters) {
////                delete [] i;
////            }
//        }
//        Level &changeSize(int nr, int nc);
//        [[nodiscard]] Matrix<Cell> &getMap() {
//            return matr;
//        }
//
////        character::Character *chooseCharacterForAttack();
//
//        Level &move();
//        Level &movePlayer();
//        Level &moveEnemy();
//
//        Level &createCharacter();
//
//        Level &createEnemy(TypeOfCreature type);
//
//        Level &pushCharacter(Operative *character);
//
//        Level &pushEnemy(Enemy *enemy);
//
//        Level &attack(Operative *player, Enemy *enemy);
//
//        [[nodiscard]] std::map<Cell *, Operative *> getOperatives() const {return characters;}
//        [[nodiscard]] std::map<Cell *, Enemy *> getEnemies() const {return enemies;}
//
//        Level &changeMove();
//
//        Operative *chooseCharacterForMove();
//
//        friend std::ostream &operator<<(std::ostream &, Level &);
//
//        Level &reload(Operative *player);
//
//
//
//        std::vector<Cell *> iSee(int y, int x, int rad);
//
//        void getSide() {
//            if (side == Side::player) std::cout << "PLAYER";
//            else std::cout << "ENEMY";
//        }
//
//        static Character *chooseCharacterForAttack(std::vector<Character *> enemy, int index);
//
//        int timeOfOpers();
//
//        void addTime();
//    };
//
//#endif //LAB3_CPP_LEVEL_H
