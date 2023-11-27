
#include "Level.h"
#include "../Character/Kinds/Forager.h"
#include "../Character/Kinds/Wild.h"
#include "../Character/Kinds/Reasonable.h"



//    Level &Level::createCharacter() {
//        characters.push_back(new character::Operative());
//        return *this;
//    }
//
//    Level &Level::createEnemy(character::TypeOfCreature type) {
//        if (type == character::TypeOfCreature::forager) enemies.push_back(new character::Forager());
//        else if (type == character::TypeOfCreature::reasonable) enemies.push_back(new character::Reasonable());
//        else if (type == character::TypeOfCreature::wild) enemies.push_back(new character::Wild());
//        return *this;
//    }

std::vector<Cell *> Level::getStocks() {
    std::vector<Cell *> st;
    if (matr.getRows() != 0 and matr.getCols() != 0) {
        for (int i = 0; i < matr.getRows(); i++) {
            for (int j = 0; j < matr.getCols(); j++) {
                if (matr.getElement(i, j).getType() == TypeOfPoint::stock) st.push_back(matr.getElementByAdress(i, j));
            }
        }
    }
    return st;
}

Level &Level::createCharacter() {
    Characteristics nc(100, 100, 50, 50, 10, 2);
    Point np;
    np.x = rand() % matr.getCols();
    np.y = rand() % matr.getRows();
    Cell *cell = matr.getElementByAdress(np.y, np.x);
//        while (matr.getElement(np.x, np.y).isCharacter()) {
//            np.x = rand() % matr.getCols();
//            np.y = rand() % matr.getRows();
//        }
    Operative *operative = new Operative("operative", nc, matr.getElementByAdress(np.y, np.x), 20, 150);
    characters.insert({matr.getElementByAdress(np.y, np.x), operative});
}

Level &Level::createEnemy(TypeOfCreature type) {
    if (type == TypeOfCreature::forager) {
        Characteristics nc(100, 100, 50, 50, 10, 2);
        Point np;
        np.x = rand() % matr.getCols();
        np.y = rand() % matr.getRows();
//            while (matr.getElement(np.x, np.y).isCharacter()) {
//                np.x = rand() % matr.getCols();
//                np.y = rand() % matr.getRows();
//            }
        std::vector<Cell *> st;
        Cell *cell = matr.getElementByAdress(np.y, np.x);
        if (matr.getRows() != 0 and matr.getCols() != 0) {
            for (int i = 0; i < matr.getRows(); i++) {
                for (int j = 0; j < matr.getCols(); j++) {
                    if (matr.getElement(i, j).getType() == TypeOfPoint::stock)
                        st.push_back(matr.getElementByAdress(i, j));
                }
            }
        }
        Enemy *enemy = new Forager("forager", nc, cell, st);
        enemies.insert({matr.getElementByAdress(np.y, np.x), enemy});
    } else if (type == TypeOfCreature::wild) {
        Characteristics nc(100, 100, 50, 50, 10, 2);
        Point np;
        np.x = rand() % matr.getCols();
        np.y = rand() % matr.getRows();
        Cell *cell = matr.getElementByAdress(np.y, np.x);
//            while (matr.getElement(np.x, np.y).isCharacter()) {
//                np.x = rand() % matr.getCols();
//                np.y = rand() % matr.getRows();
//            }
        Enemy *enemy = new Wild("wild", nc, cell, 20, 25, 50);
        enemies.insert({matr.getElementByAdress(np.y, np.x), enemy});
    } else if (type == TypeOfCreature::reasonable) {
        Characteristics nc(100, 100, 50, 50, 10, 2);
        Point np;
        np.x = rand() % matr.getCols();
        np.y = rand() % matr.getRows();
        Cell *cell = matr.getElementByAdress(np.y, np.x);
//            while (matr.getElement(np.x, np.y).isCharacter()) {
//                np.x = rand() % matr.getCols();
//                np.y = rand() % matr.getRows();
//            }
        std::vector<Cell *> st;
        if (matr.getRows() != 0 and matr.getCols() != 0) {
            for (int i = 0; i < matr.getRows(); i++) {
                for (int j = 0; j < matr.getCols(); j++) {
                    if (matr.getElement(i, j).getType() == TypeOfPoint::stock)
                        st.push_back(matr.getElementByAdress(i, j));
                }
            }
        }
        Enemy *enemy = new Reasonable("reasonable", nc, cell, 50, st);
        enemies.insert({matr.getElementByAdress(np.y, np.x), enemy});
    }
    return *this;
}


Level &Level::changeMove() {
    if (side == Side::player) side = Side::enemy;
    else side = Side::player;
    return *this;
}

//Operative *Level::chooseCharacterForMove() {
//    for (auto i: characters) {
//        return i.second;
//    }
//}

std::ostream &operator<<(std::ostream &c, Level &l) {
    c << l.matr << std::endl;
    return c;
}

void Level::addTime() {
    if (side == Side::player) {
        for (auto &i: characters) {
            i.second->setTime(i.second->getMaxTime());
        }
    } else {
        for (auto &i: enemies) {
            i.second->setTime(i.second->getMaxTime());
        }
    }
}

Level &Level::move() {
    if (side == Side::player) {
        movePlayer();
    } else moveEnemy();
    addTime();
    changeMove();
    return *this;
}

Level &Level::changePositionsPlayers() {
    std::vector<Operative *> arrayOfOpers;
    for (auto i: characters) {
        arrayOfOpers.push_back(i.second);

    }
    std::vector<Enemy *> arrayOfEnemy;
    for (auto i: enemies) {
        arrayOfEnemy.push_back(i.second);
    }
    characters.clear();
    for (auto i: arrayOfOpers) {
        characters.insert({i->getCell(), i});
    }
    enemies.clear();
    for (auto i: arrayOfEnemy) {
        enemies.insert({i->getCell(), i});
    }
    return *this;
}

Level &Level::makeActionPlayer(std::vector<int> option, Operative *oper) {
    switch (option[0]) {
        case 1:
            oper->move(Direction::left, getMap());
            break;
        case 2:
            oper->move(Direction::up, getMap());
            break;
        case 3:
            oper->move(Direction::right, getMap());
            break;
        case 4:
            oper->move(Direction::down, getMap());
            break;
        case 5: { // атаковать
            std::vector<Character *> iSeeEnemies;
            seeEnemies(iSeeEnemies, oper);
            oper->attack(chooseCharacterForAttack(iSeeEnemies, 0), getMap());
            break;
        }

        case 6: { // взять предмет
            if (oper->getCell()->getItems().size() == 0) return *this;
            oper->takeItem(oper->getCell()->getItems()[0]);
            break;
        }
        case 7: { // дропнуть предмет
            if (oper->getCurrentWeight() == 0) return *this;
            int index;
            index = chooseItemForDrop(oper->getInventory());
            if (index == -1) return *this;
            oper->dropItem(index);
            break;
        }
        case 8: { // взять оружие
            if (!oper->getCell()->isWeapon()) return *this;
            oper->takeWeapon(dynamic_cast<Weapon *>(chooseWeaponForTake(oper->getCell())));
            break;
        }
        case 9: { // дропнуть оружие
            oper->throwWeapon();
            break;
        }

    }
    return *this;
}

Item *Level::chooseWeaponForTake(Cell *cell) {
    for (auto i: cell->getItems()) {
        if (i->getName() == TypeOfItem::weapon) return i;
    }
    return nullptr;
}


int Level::chooseItemForDrop(Inventory inv) {
    int index = 0;
    if (index < inv.getCountOfItems()) return -1;
    return index;
}

Level &Level::movePlayer() {
    std::vector<Operative *> arrayOfOpers;
    for (auto i: characters) {
        if (i.second->getCell() == nullptr) continue;
        while (i.second->getTime() > 0) {
            makeActionPlayer({1}, i.second);
        }
        arrayOfOpers.push_back(i.second);
    }
    characters.clear();
    for (auto i: arrayOfOpers) {
        characters.insert({i->getCell(), i});
    }
    return *this;
}

//Character *Level::chooseCharacterForAttack(std::vector<Character *> enemy, int index) {
//    return enemy[index];
//}

void Level::seeEnemies(std::vector<Character *> &ans, Character *i) {
    std::vector<Cell *> cellWhichISee = i->iSee(matr);
    for (auto j: cellWhichISee) {
        if (characters.find(j) != characters.end()) {
            ans.push_back(characters.find(j)->second);
        }
    }
}

Level &Level::moveEnemy() {
    std::vector<Enemy *> arrayOfenemies;
    for (auto i: enemies) {
        if (i.second->getCell() == nullptr) continue;
        while (i.second->getTime() > 0) {
//            std::cout << i.second->getX() << " " << i.second->getY() << "\n";

            std::vector<Character *> iSeeEnemies;
            seeEnemies(iSeeEnemies, i.second);
            i.second->move1(getMap(), iSeeEnemies);
        }
        arrayOfenemies.push_back(i.second);
    }
    enemies.clear();
    for (auto i: arrayOfenemies) {
        enemies.insert({i->getCell(), i});
    }
    return *this;
}


Level &Level::pushEnemy(Enemy *enemy) {
    enemies.insert(std::map<Cell *, Enemy *>::value_type(
            matr.getElementByAdress(enemy->getCell()->getPoint().y, enemy->getCell()->getPoint().x), enemy));
    enemy->setCell(getMap().getElementByAdress(enemy->getCell()->getPoint().y, enemy->getCell()->getPoint().x));
    return *this;
}

Level &Level::pushCharacter(Operative *character) {
    characters.insert(std::map<Cell *, Operative *>::value_type(
            matr.getElementByAdress(character->getCell()->getPoint().y, character->getCell()->getPoint().x),
            character));
    character->setCell(
            getMap().getElementByAdress(character->getCell()->getPoint().y, character->getCell()->getPoint().x));
    return *this;
}

Character *Level::chooseCharacterForAttack(std::vector<Character *> &enemy, int index) {
    return enemy[index];
}
