//
// Created by vadim on 25.11.2023.
//

#ifndef LAB3_CPP_GAME_H
#define LAB3_CPP_GAME_H
#include "../Level/Level.cpp"
#include "map.h"
#include "SFML/Graphics.hpp"


struct Camera
{
    sf::View view;
    sf::Vector2f pos;
    bool locked = false;

    void lock(float x, float y)
    {
        pos.x = x;
        pos.y = y;
        locked = true;
    }

    void unlock() { locked = false; }

    void move(float x, float y)
    {
        if (locked)
        {
            view.move(pos.x - x, pos.y - y);
            pos.x = x;
            pos.y = y;
        }
    }
    void getPlayerCoordinateForView(float x, float y) { //функция для считывания координат игрока
        float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

        if (x < 320) tempX = 320;//убираем из вида левую сторону
        if (y < 240) tempY = 240;//верхнюю сторону
        if (y > 554) tempY = 554;//нижнюю сторону

        view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты.

    }
};


class Game {
private:
    Level level;
    int size_of_cell = 10;
    Camera cam;
public:
    Game(Level nLevel) : level(nLevel) {};
    Game(Level nLevel, int size) : level(nLevel), size_of_cell(size) {};

    int play();


    void createWindow(sf::RenderWindow *window, int size_of_cell);

    sf::RenderWindow createWindow(int size_of_cell);

    int showMap(sf::RenderWindow &window);

    sf::RenderWindow createWindow();
    void controlPanel(sf::RenderWindow &window);
    void move(sf::Event &event);
};


#endif //LAB3_CPP_GAME_H
