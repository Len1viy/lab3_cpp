#include <iostream>
#include "Game.cpp"

int main() {
    Level level(100, 100);
    level.getMap().getElementByAdress(10, 10)->changeTypeOfCell(TypeOfPoint::glass);
    Game game(level, 30);
    game.play();
}