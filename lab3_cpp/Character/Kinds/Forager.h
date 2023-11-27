
//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_FORAGER_H
#define LAB3_CPP_FORAGER_H


#include "iostream"
#include "Enemy.h"

/**
 * @brief class of enemy with type Forager. It goes around of map and collects items. His mission - to deliver items to stock
 */
class Forager : public Enemy, public InventoryUser {
private:
    /**
     * @param inventory Inventory of forager
     */
    Inventory inventory;
    /**
     * @param stocks Stocks located on the map
     */
    std::vector<Cell *> stocks;
    /**
     * @param visitedStocks visited stocks
     */
    std::vector<Cell *> visitedStocks;
public:
    /**
     * @brief Default constructor of Forager
     */
    Forager() : Enemy(TypeOfCreature::forager), inventory(), stocks(), visitedStocks() {};
    /**
     * @brief Constructor without stocks and with all of needed information
     * @param nm name of creature
     * @param c characteristics of creature
     * @param ncell Cell for spawn of Forager
     */
    Forager(std::string nm, Characteristics c, Cell *ncell) :
            Enemy(std::move(nm), c, ncell, TypeOfCreature::forager, Side::enemy)
    {};
    /**
     * @brief Constructor with stocks and all of needed information
     * @param nm name of creature
     * @param c characteristics of creature
     * @param ncell Cell for spawn of Forager
     * @param st vector of stocks located on map
     */
    Forager(std::string nm, Characteristics c, Cell *ncell, std::vector<Cell *> st) :
            Enemy(std::move(nm), c, ncell, TypeOfCreature::forager, Side::enemy), stocks(std::move(st)), visitedStocks()
    {};
    /**
     * Getter of inventory
     * @return inventory
     */
    [[nodiscard]] Inventory getInventory() const {return inventory;}
    /**
     * Setter of stocks
     * @param nstocks vector of stocks located on the map
     * @return changed forager
     */
    Forager &setStocks(std::vector <Cell *> nstocks) {
        stocks = nstocks;
        return *this;
    }
    /**
     * @brief overrided function of taking items
     * @param nItem item which Forager will take
     */
    void takeItem(Item *nItem) override;
    /**
     * @brief overrided function to drop item to cell
     * @param index index of item which Forager will drop
     */
    void dropItem(int index) override;
//    std::ostream &print(std::ostream &c) override;
//    friend std::ostream &operator<<(std::ostream &c, Forager &forager);
    /**
     * @brief overrided function of death creature
     */
    void Dead() override;
    /**
     * @brief Function with logic of move forager
     * @param matr Map of level
     * @param iSeeEnemies vector of enemies which forager see
     * @return forager with changed fields after move
     */
    Character &move1(Matrix<Cell> &matr, std::vector<Character *> iSeeEnemies) override;
    /**
     * take all of items from cell
     */
    void takeAllOfItems();
};


#endif //LAB3_CPP_FORAGER_H