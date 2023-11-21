#include <iostream>
#include "Level/Level.cpp"

int main() {
    srand(time(0));
//    matrix::Matrix<int> matr(10, 10);
//    std::cout << matr.getElement(2, 3) << std::endl;


//    character::Characteristics nc(100, 100, 50, 50, 10, 100);
//    Point np;
//    np.x = rand() % 10;
//    np.y = rand() % 10;
//    character::Operative oper("John", nc, np, 20, 150);
//    character::Forager forager;
//    character::Wild wild;
//    l1.pushCharacter(&oper);
//    l1.pushEnemy(&forager);
//    l1.pushEnemy(&wild);
//    level::Level l1(15, 10);
//    std::cout << l1;
//    l1.createEnemy(character::TypeOfCreature::forager);
//    l1.createCharacter();
//    for (auto i : l1.getOperatives()) {
//        std::cout << *i;
//    }
//    for (auto i : l1.getEnemies()) {
//        std::cout << *i;
//    }
//    l1.createEnemy(character::TypeOfCreature::forager);

//    l1.attack(l1.chooseCharacterForMove(), l1.getEnemies()[1]);
//    l1.attack(l1.chooseCharacterForMove(), l1.getEnemies()[1]);
//    l1.attack(l1.chooseCharacterForMove(), l1.getEnemies()[1]);
//    l1.reload(l1.chooseCharacterForMove());
//    l1.attack(l1.chooseCharacterForMove(), l1.getEnemies()[1]);
//    l1.attack(l1.chooseCharacterForMove(), l1.getEnemies()[1]);
//    l1.attack(l1.chooseCharacterForMove(), l1.getEnemies()[1]);
//    l1.reload(l1.chooseCharacterForMove());
//    l1.attack(l1.chooseCharacterForMove(), l1.getEnemies()[1]);
//    l1.attack(l1.chooseCharacterForMove(), l1.getEnemies()[1]);
//
//    l1.attack(l1.chooseCharacterForMove(), l1.getEnemies()[1]);


//    std::cout << l1.getEnemies();

//      l1.getMap().popColumn(3);
//      std::cout << l1;
//      std::cout << l1.getMap().getCols();
//      l1.getMap().popRow(5);
//      std::cout << l1;

//    matrix::Matrix<level::Cell> matr(15, 10);
//    std::cout << matr;
//    matr.popColumn(3);
//    std::cout << matr;
//      std::cout << l1;

//    std::cout << oper.getAccuracy() << std::endl;
//    return 0;


//    Weapon item;
//    Weapon *item1;
//    std::cout << &item;
//    std::cout << item1;
//    if (item == *item1) std::cout << "ДА";
//    else std::cout << "Нет";
    Level l1(10, 10);
    l1.getMap().getElementByAdress(3, 5)->changeTypeOfCell(TypeOfPoint::stock);
//    l1.createCharacter();
    Operative oper;
    oper.setCell(l1.getMap().getElementByAdress(8, 8));
    l1.getOperatives().clear();
    l1.pushCharacter(&oper);
    Wild enemy;

    enemy.setCell(l1.getMap().getElementByAdress(8, 7));
    l1.pushEnemy(&enemy);
//
//    enemy.attack(&oper, l1.getMap());
    std::cout << oper;
//    enemy.setStocks(l1.getStocks());

//    l1.createEnemy(TypeOfCreature::reasonable);
//    Reasonable enemy;
//    enemy.setCell(l1.getMap().getElementByAdress(4, 5));
//    enemy.setStocks(l1.getStocks());





//    for (auto i: l1.getOperatives()) {
//        std::cout << *(i.second);
//    }
//    for (auto i: l1.getEnemies()) {
//        std::cout << *(i.second);
//    }
//
//    MedKit medKit;
//    l1.getMap().getElementByAdress(2, 5)->addItem(&medKit);
//    oper.takeItem(l1.getMap().getElementByAdress(2, 5)->getItems()[0]);
//    oper.changeHealth(20, -1);
//    oper.useItem(oper.getInventory().getItems()[0]);
//    Weapon weapon1 = *Weapon::createSniper();
//    weapon1.setBullet(sniper);
//    std::cout << &weapon1;
//    weapon1.setMaxCountOfBullet(3);
//    weapon1.setCurrentCountOfBuillet(3);
//    l1.getMap().getElementByAdress(2, 5)->addItem(&weapon1);
//    oper.takeItem(l1.getMap().getElementByAdress(2, 5)->getItems()[0]);
//    std::cout << oper;
//    oper.useItem(&weapon1);
//    Inventory inventory = oper.getInventory();

//    std::cout << inventory;

    l1.move();
    for (auto i: l1.getOperatives()) {
        std::cout << *(i.second);
    }
    for (auto i: l1.getEnemies()) {
        std::cout << *(i.second);
    }

    std::cout << "-----------------";
    l1.getSide();
    std::cout << "-------------------\n";
    for (auto i: l1.getOperatives()) {
        std::cout << *(i.second);
    }
    for (auto i: l1.getEnemies()) {
        std::cout << *(i.second);
    }
    l1.move();
    std::cout << "-----------------";
    l1.getSide();
    std::cout << "-------------------\n";
    for (auto i: l1.getOperatives()) {
        std::cout << *(i.second);
    }
    for (auto i: l1.getEnemies()) {
        std::cout << *(i.second);
    }
    l1.move();
    std::cout << "-----------------";
    l1.getSide();
    std::cout << "-------------------\n";
    for (auto i: l1.getOperatives()) {
        std::cout << *(i.second);
    }
    for (auto i: l1.getEnemies()) {
        std::cout << *(i.second);
    }
}
