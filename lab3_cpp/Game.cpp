//
// Created by vadim on 25.11.2023.
//

#include "Game.h"


sf::RenderWindow Game::createWindow() {
    int rows = level.getMap().getRows();
    int cols = level.getMap().getCols();
//    return sf::RenderWindow(sf::VideoMode(rows * size_of_cell, cols * size_of_cell), "Game", sf::Style::Close | sf::Style::Titlebar);
    return sf::RenderWindow(sf::VideoMode(), "Game", sf::Style::Fullscreen);
}

int Game::showMap(sf::RenderWindow &window) {
    sf::Sprite heroSprite;

//    sf::Texture texture1;
//    if (!texture.loadFromFile(R"(C:\Users\vadim\CLionProjects\lab3_cpp\imgs\Soldier_1\Idle.png)"))
//        return EXIT_FAILURE;
    sf::Image img;
    if (!img.loadFromFile(R"(C:\Users\vadim\CLionProjects\lab3_cpp\imgs\StayingSoldierSprite.png)"))
        return EXIT_FAILURE;
    img.createMaskFromColor(sf::Color(255, 255, 255));
    sf::Texture heroTexture;
    heroTexture.loadFromImage(img);
    heroSprite.setTexture(heroTexture);
    heroSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    sf::Sprite wallSprite;
    sf::Sprite floorSprite;
    sf::Sprite glassSprite;
    sf::Texture cellsTextures;
    if (!cellsTextures.loadFromFile(R"(C:\Users\vadim\CLionProjects\lab3_cpp\imgs\Cells.png)"))
        return EXIT_FAILURE;
    wallSprite.setTexture(cellsTextures);
    wallSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
    floorSprite.setTexture(cellsTextures);
    floorSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    glassSprite.setTexture(cellsTextures);
    glassSprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
    for (auto i = level.getMap().begin(); i != level.getMap().end(); i++) {
        if ((*i).getType() == TypeOfPoint::wall) {
            wallSprite.setPosition(i.getX() * size_of_cell, i.getY() * size_of_cell);
            window.draw(wallSprite);
        } else if ((*i).getType() == TypeOfPoint::tile) {
            floorSprite.setPosition(i.getX() * size_of_cell, i.getY() * size_of_cell);
            window.draw(floorSprite);
            if (level.getOperatives().count(&(*i)) != 0) {
                heroSprite.setPosition(i.getX() * size_of_cell, i.getY() * size_of_cell);
                window.draw(heroSprite);
            }
        } else if ((*i).getType() == TypeOfPoint::glass) {
            glassSprite.setPosition(i.getX() * size_of_cell, i.getY() * size_of_cell);
            window.draw(glassSprite);
        }
    }
    return 1;
}

void Game::controlPanel(sf::RenderWindow &window) {

}


int Game::play() {
    Operative oper;
    oper.setCell(level.getMap().getElementByAdress(3, 4));
    level.pushCharacter(&oper);
    int rows = level.getMap().getRows();
    int cols = level.getMap().getCols();
    sf::RenderWindow window = createWindow();
    cam.view.reset(sf::FloatRect(0, 0, 640, 480));
    float minZoom = (cam.view.getSize().x / window.getSize().x) / 2;
    float maxZoom = (cam.view.getSize().x / window.getSize().x) * 2;
    bool lock = true;
    bool isKeyPressed = false;
//    for (auto &i: level.getOperatives()) {
//        std::cout << i.first->getPoint().x << " " << i.first->getPoint().y << "\n";
//        std::cout << i.second->getX() << " " << i.second->getY() << "\n";
//    }
//    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
                lock = true;
                cam.view.setCenter(oper.getX() * size_of_cell, oper.getY() * size_of_cell);
            } else if (event.type == sf::Event::MouseMoved) {
                cam.move(event.mouseMove.x, event.mouseMove.y);
            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                lock = false;
                cam.lock(event.mouseButton.x, event.mouseButton.y);
            } else if (event.type == sf::Event::MouseButtonReleased &&
                       event.mouseButton.button == sf::Mouse::Left) {
                cam.unlock();
            } else if (event.type == sf::Event::MouseWheelMoved) {
                float newZoom = cam.view.getSize().x / window.getSize().x;
//                    std::cout << newZoom << "\n";
//                    std::cout << minZoom << "\n";
//                    std::cout << maxZoom << "\n";
//                    std::cout << event.mouseWheelScroll.wheel << "\n";
//                    std::cout << "-------------------\n";
                if (event.mouseWheelScroll.wheel == 1 && newZoom > minZoom) {
                    cam.view.zoom(0.9f);
                } else if (event.mouseWheelScroll.wheel == -1 && newZoom < maxZoom) {
                    cam.view.zoom(1.1f);
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                if (!isKeyPressed) level.makeActionPlayer({2}, &oper);
                isKeyPressed = !isKeyPressed;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if (!isKeyPressed) level.makeActionPlayer({4}, &oper);
                isKeyPressed = !isKeyPressed;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                if (!isKeyPressed) level.makeActionPlayer({1}, &oper);
                isKeyPressed = !isKeyPressed;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if (!isKeyPressed) level.makeActionPlayer({3}, &oper);
                isKeyPressed = !isKeyPressed;
            } if (lock) {
                cam.view.setCenter(oper.getX() * size_of_cell, oper.getY() * size_of_cell);
            }
//            std::cout << oper.getX() << " " << oper.getY() << "\n";
            level.changePositionsPlayers();
        }
        window.setView(cam.view);
        window.clear();
        showMap(window);
        controlPanel(window);
        window.display();

    }
    return 1;
}



void Game::move(sf::Event &event) {
    if (level.getSide() == Side::enemy) level.moveEnemy();


}
