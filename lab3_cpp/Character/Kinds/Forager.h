//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_FORAGER_H
#define LAB3_CPP_FORAGER_H

#include "iostream"
#include "Enemy.h"
// абстрактный класс содержащий в себе методы взаимодействия с инвентарем

namespace character {

    class Forager : public Enemy, public interface::InventoryUser {
    private:
        inventory::Inventory inventory;
        std::vector<Point> stocks;
    public:
        Forager(std::string nm, Characteristics c, Point p) :
        Enemy(nm, c, p, TypeOfCreature::forager, level::Side::enemy)
        {};
        Forager(std::string nm, Characteristics c, Point p, std::vector<Point> st) :
                Enemy(nm, c, p, TypeOfCreature::forager, level::Side::enemy), stocks(st)
        {};
        void takeItem(int index) override;
        void dropItem(int index) override;
        Character &move(Point npoint) override;
    };

} // character

#endif //LAB3_CPP_FORAGER_H
