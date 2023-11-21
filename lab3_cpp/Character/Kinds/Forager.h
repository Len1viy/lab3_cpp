
//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_FORAGER_H
#define LAB3_CPP_FORAGER_H


#include "iostream"
#include "Enemy.h"


class Forager : public Enemy, public InventoryUser {
private:
    Inventory inventory;
    std::vector<Cell *> stocks;
    std::vector<Cell *> visitedStocks;
public:
    Forager() : Enemy(TypeOfCreature::forager), inventory(), stocks(), visitedStocks() {};
    Forager(std::string nm, Characteristics c, Cell *ncell) :
            Enemy(std::move(nm), c, ncell, TypeOfCreature::forager, Side::enemy)
    {};
    Forager(std::string nm, Characteristics c, Cell *ncell, std::vector<Cell *> st) :
            Enemy(std::move(nm), c, ncell, TypeOfCreature::forager, Side::enemy), stocks(std::move(st)), visitedStocks()
    {};
    [[nodiscard]] Inventory getInventory() const {return inventory;}
    Forager &setStocks(std::vector <Cell *> nstocks) {
        stocks = nstocks;
        return *this;
    }
    void takeItem(Item *nItem) override;
    void dropItem(int index) override;
//    std::ostream &print(std::ostream &c) override;
//    friend std::ostream &operator<<(std::ostream &c, Forager &forager);
    void Dead() override;
    Character &move1(Matrix<Cell> &matr, std::vector<Character *> iSeeEnemies) override;

    void takeAllOfItems();
};


#endif //LAB3_CPP_FORAGER_H



////
//// Created by vadim on 16.10.2023.
////
//
//#ifndef LAB3_CPP_FORAGER_H
//#define LAB3_CPP_FORAGER_H
//
//
//#include "iostream"
//#include "Enemy.h"
//
//
//    class Forager : public Enemy, public InventoryUser {
//    private:
//        Inventory inventory;
//        std::vector<Cell *> stocks;
//        std::vector<Cell *> visitedStocks;
//    public:
//        Forager() : Enemy(), inventory(), stocks(), visitedStocks() {};
//        Forager(std::string nm, Characteristics c, Cell *ncell) :
//        Enemy(std::move(nm), c, ncell, TypeOfCreature::forager, Side::enemy)
//        {};
//        Forager(std::string nm, Characteristics c, Cell *ncell, std::vector<Cell *> st) :
//                Enemy(std::move(nm), c, ncell, TypeOfCreature::forager, Side::enemy), stocks(std::move(st)), visitedStocks()
//        {};
//        [[nodiscard]] Inventory getInventory() const {return inventory;}
//        void takeItem(Item *nItem) override;
//        void dropItem(int index) override;
//        Character &move(std::vector<Cell *> points, Matrix<Cell> matr) override;
//        std::ostream &print(std::ostream &c) override;
//        friend std::ostream &operator<<(std::ostream &c, Forager &forager);
//        void Dead() override;
//
//    };
//
//
//#endif //LAB3_CPP_FORAGER_H
