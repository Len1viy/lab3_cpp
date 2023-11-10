//
// Created by vadim on 16.10.2023.
//

#include "Level.h"
namespace level {
    Level &Level::changeSize(const int nr, const int nc) {}
    Level &Level::createCharacter() {
        character::Characteristics nc(100, 100, 50, 50, 10, 100);
        Point np;
        np.x = rand() % matr.getCols();
        np.y = rand() % matr.getRows();
        while (matr.getElement(np.x, np.y).isCharacter() || matr.getElement(np.x, np.y).canMove()) {
            np.x = rand() % matr.getCols();
            np.y = rand() % matr.getRows();
        }
        characters.push_back(new character::Operative("operative", nc, np, 20, 150));

    }
    Level &Level::createEnemy(character::TypeOfCreature type) {
        if (type == character::TypeOfCreature::forager) {
            character::Characteristics nc(100, 100, 50, 50, 10, 100);
            Point np;
            np.x = rand() % matr.getCols();
            np.y = rand() % matr.getRows();
            while (matr.getElement(np.x, np.y).isCharacter() || matr.getElement(np.x, np.y).canMove()) {
                np.x = rand() % matr.getCols();
                np.y = rand() % matr.getRows();
            }
            std::vector<Point> st;
            if (matr.getRows() != 0 and matr.getCols() != 0) {
                for (int i = 0; i < matr.getRows(); i++) {
                    for (int j = 0; j < matr.getCols(); j++) {
                        if (matr.getElement(i, j).getType() == TypeOfPoint::stock) st.push_back(Point{i, j});
                    }
                }
            }

            character::Forager nEnemy("forager", nc, np, st);
            enemies.push_back((character::Enemy *) new character::Forager("forager", nc, np, st));
        } else if (type == character::TypeOfCreature::wild) {
            character::Characteristics nc(100, 100, 50, 50, 10, 100);
            Point np;
            np.x = rand() % matr.getCols();
            np.y = rand() % matr.getRows();
            while (matr.getElement(np.x, np.y).isCharacter() || matr.getElement(np.x, np.y).canMove()) {
                np.x = rand() % matr.getCols();
                np.y = rand() % matr.getRows();
            }
            enemies.push_back((character::Enemy *) new character::Wild("wild", nc, np, 20, 25, 50));
        } else if (type == character::TypeOfCreature::reasonable) {
            character::Characteristics nc(100, 100, 50, 50, 10, 100);
            Point np;
            np.x = rand() % matr.getCols();
            np.y = rand() % matr.getRows();
            while (matr.getElement(np.x, np.y).isCharacter() || matr.getElement(np.x, np.y).canMove()) {
                np.x = rand() % matr.getCols();
                np.y = rand() % matr.getRows();
            }
            std::vector<Point> st;
            if (matr.getRows() != 0 and matr.getCols() != 0) {
                for (int i = 0; i < matr.getRows(); i++) {
                    for (int j = 0; j < matr.getCols(); j++) {
                        if (matr.getElement(i, j).getType() == TypeOfPoint::stock) st.push_back(Point{i, j});
                    }
                }
            }
//            character::Reasonable nEnemy("resonable", nc, np, 50, st);
            enemies.push_back((character::Enemy *) new character::Reasonable ("resonable", nc, np, 50, st));
        }
        return *this;
    }
    Level &Level::changeMove() {
        if (move == Side::player) move = Side::enemy;
        else move = Side::player;
        return *this;
    }
    character::Character *Level::chooseCharacterForMove(level::Side type) {
        int index = rand() % characters.size();
        if (type == level::Side::player) {
            return (character::Character *) characters[index];
        }
        return (character::Character *) enemies[index];
    }
}