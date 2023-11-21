#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../Level/Level.cpp"
#include "../Level/Cell.cpp"
#include "../Level/Matrix.cpp"


#include "../Character/Character.cpp"
#include "../Character/Kinds/Reasonable.cpp"
#include "../Character/Kinds/Operative.cpp"
#include "../Character/Kinds/Wild.cpp"
#include "../Character/Kinds/Forager.cpp"
#include "../Character/Kinds/Enemy.cpp"


#include "../Inventory/Items/Item.cpp"
#include "../Inventory/Inventory.cpp"
#include "../Inventory/Items/Weapon.cpp"
#include "../Inventory/Items/MedKit.cpp"
#include "../Inventory/Items/ContainerForBullet.cpp"


TEST_CASE("LEVEL") {
    SECTION("Constructors", "DefaultConstructor") {
        Level l1;
        REQUIRE(l1.getMap().getRows() == 0);
        REQUIRE(l1.getMap().getCols() == 0);
    }SECTION("Constructors") {
        Level l1(10, 15);
        REQUIRE(l1.getMap().getRows() == 10);
        REQUIRE(l1.getMap().getCols() == 15);
    }SECTION("Getters/Setters") {
        Level l1(10, 15);
        Weapon item = *(Weapon::createPistol());
        REQUIRE(item.getCurrentCountOfBuillet() == 12);
        REQUIRE(item.getPointsForShoot() == 4);
        REQUIRE(item.getName() == TypeOfItem::weapon);
        REQUIRE(item.getBullet() == BulletType::pistol);

        l1.getMap().getElementByAdress(3, 3)->addItem(&item);
        REQUIRE(((Weapon *) (l1.getMap().getElementByAdress(3, 3)->getItems()[0])) == &item);
        l1.createCharacter();
        l1.createEnemy(TypeOfCreature::reasonable);
        l1.createEnemy(TypeOfCreature::reasonable);
        REQUIRE(l1.getEnemies().size() == 2);
        REQUIRE(l1.getOperatives().size() == 1);
        for (auto &i: l1.getOperatives()) {
            REQUIRE(*i.second->getActiveWeapon() == item);
            REQUIRE(i.second->getCell() == l1.getMap().getElementByAdress(i.second->getCell()->getPoint().y,
                                                                          i.second->getCell()->getPoint().x));
            REQUIRE(i.second->getStrength() == 150);
            REQUIRE(i.second->getCurrentWeight() == 0);
            REQUIRE(i.second->getTime() == 50);
            REQUIRE(i.second->getMaxTime() == 50);
            REQUIRE(i.second->getRadius() == 2);
            REQUIRE(i.second->getInventory().getItems().empty());
            REQUIRE(i.second->getCurrentWeight() == 0);
            REQUIRE(i.second->getHealth() == 100);
            REQUIRE(i.second->getName() == "operative");
        }
    }
}

TEST_CASE("GAME") {
    Level level(20, 30);
    Reasonable reasonable;
    reasonable.setCell(level.getMap().getElementByAdress(15, 14));
    level.pushEnemy(&reasonable);
    Operative operative;
    operative.setCell(level.getMap().getElementByAdress(3, 5));
    level.pushCharacter(&operative);
    Weapon *sniper = Weapon::createSniper();
    Weapon *pistol = Weapon::createPistol();
    MedKit medKit;
    level.getMap().getElementByAdress(3, 5)->addItem(sniper);
    SECTION("Situation1") {    // персонажи далеко друг от друга и не видят никого в округе, цели для передвижений нет, то есть они беспорядочно ходят
        REQUIRE(level.getSide() == Side::player);
        level.move();
//        std::cout << operative.getX() << " " << operative.getY();

        REQUIRE(level.getSide() == Side::enemy);
        REQUIRE((operative.getCell()->getPoint().y != 3 || operative.getCell()->getPoint().x != 5) == true);
        level.move();
//        std::cout << reasonable.getCell()->getPoint().y << " " << reasonable.getCell()->getPoint().x << "\n";
        REQUIRE((reasonable.getCell()->getPoint().y != 15 || reasonable.getCell()->getPoint().x != 4) == true);
    } SECTION("Situation2") { // персонаж поднимает оружие и берет его в инвентарь
        operative.takeItem(sniper);
        REQUIRE(level.getMap().getElementByAdress(3, 5)->getItems().empty());
        REQUIRE(operative.getInventory().getItems()[operative.getInventory().getItems().size() - 1] == sniper);
        REQUIRE(operative.getInventory().getCountOfItems() == 1);
        REQUIRE(operative.getInventory().getCurrentWeight() == sniper->getWeight());
    } SECTION("Situation3") { // персонаж берет в руки оружие заменяя свое на новое из инвентаря
        operative.takeItem(sniper);
        REQUIRE(level.getMap().getElementByAdress(3, 5)->getItems().empty());
        REQUIRE(operative.getInventory().getItems()[operative.getInventory().getItems().size() - 1] == sniper);
        operative.useItem(operative.getInventory().getItems().size() - 1);
        REQUIRE(*operative.getActiveWeapon() == *sniper);
        REQUIRE(operative.getInventory().getCountOfItems() == 1);
        REQUIRE(*(Weapon *) (operative.getInventory().getItems()[0]) == *pistol);
    } SECTION("Situation4") { // персонаж выбрасывает оружие, которое в руках, на пол и обратно берет в руки пистолет
        operative.takeItem(sniper);
        REQUIRE(level.getMap().getElementByAdress(3, 5)->getItems().empty());
        REQUIRE(operative.getInventory().getItems()[operative.getInventory().getItems().size() - 1] == sniper);
        operative.useItem(operative.getInventory().getItems().size() - 1);
        REQUIRE(*operative.getActiveWeapon() == *sniper);
        REQUIRE(operative.getInventory().getItems().size() == 1);
        operative.throwWeapon();
        REQUIRE(*operative.getActiveWeapon() == Weapon());
        REQUIRE(*(Weapon *) (level.getMap().getElementByAdress(3, 5)->getItems()[0]) == *sniper);
        operative.useItem(0);
        REQUIRE(*operative.getActiveWeapon() == *pistol);
    } SECTION("Situation5") { // персонаж выбрасывает оружие и берет новое с пола
        operative.takeWeapon(sniper);
        REQUIRE(*(Weapon *) (level.getMap().getElementByAdress(3, 5)->getItems()[0]) == *pistol);
        REQUIRE(*(operative.getActiveWeapon()) == *sniper);
    } SECTION("Situation6") { // персонаж поднимает с пола аптечку, получает урон, лечится
        level.getMap().getElementByAdress(3, 5)->addItem(&medKit);
        operative.takeItem(&medKit);
        Reasonable reasonable1;
        reasonable1.setActiveWeapon(pistol);
        reasonable1.setCell(level.getMap().getElementByAdress(5, 5));
        REQUIRE(operative.getInventory().getItems().size() == 1);
        REQUIRE(*(dynamic_cast<MedKit *>(operative.getInventory().getItems()[0])) == medKit);
        reasonable1.attack(&operative, level.getMap());
        REQUIRE(operative.getHealth() != 100);
        int hp = operative.getHealth();
        operative.useItem(0);
        REQUIRE((operative.getHealth() == hp + medKit.getHealth() ||
                 operative.getHealth() == operative.getMaxHealth()) == true);
        REQUIRE(operative.getInventory().getItems().size() == 0);
        REQUIRE(operative.getTime() == operative.getMaxTime() - medKit.getPointsForUsing());
    } SECTION("Situation7") { // перезарядка оружия + стрельба + урон
        Reasonable reasonable1;
        reasonable1.setActiveWeapon(pistol);
        reasonable1.setCell(level.getMap().getElementByAdress(5, 5));
        operative.attack(&reasonable1, level.getMap());
        REQUIRE(reasonable1.getHealth() != 100);
        int time = operative.getTime();
        ContainerForBullet container;
        int cnt = container.getCurrentSize();
        operative.takeItem(&container);
        operative.reload();
        REQUIRE(operative.getTime() < time);
        REQUIRE(*((ContainerForBullet *) (operative.getInventory().getItems()[0])) == container);
        REQUIRE(container.getCurrentSize() == cnt - operative.getActiveWeapon()->getMaxCountOfBullet());
        operative.getActiveWeapon()->shoot();
        operative.reload();
        REQUIRE(operative.getInventory().getItems().size() == 0);
    }SECTION("Situation8") { // дикий автоатакует
        Operative operative1;
        operative1.setCell(level.getMap().getElementByAdress(7, 7));
        Wild wild;
        wild.setCell(level.getMap().getElementByAdress(8, 7));
        level.pushEnemy(&wild);
        level.pushCharacter(&operative1);
        level.moveEnemy();
        REQUIRE(operative1.getHealth() != operative1.getMaxHealth());
    }SECTION("Situation9") { // Wild гонится за оперативником
        Operative operative1;
        operative1.setCell(level.getMap().getElementByAdress(7, 7));
        Wild wild;
        wild.setCell(level.getMap().getElementByAdress(10, 5));
        int x = 5, y = 2;
        level.pushEnemy(&wild);
        level.pushCharacter(&operative1);
        level.moveEnemy();
//        std::cout << wild.getX() << " " << wild.getY();
        REQUIRE(wild.way(wild.getCell(), operative1.getCell()) <
                wild.way(level.getMap().getElementByAdress(y, x), operative1.getCell()));
    } SECTION("Situation10") { // Reasonable идет к ближайшей складской точке, а потом к другой
        level.getMap().getElementByAdress(15, 16)->setType(TypeOfPoint::stock);
        level.getMap().getElementByAdress(10, 10)->setType(TypeOfPoint::stock);
        level.getMap().getElementByAdress(8, 8)->setType(TypeOfPoint::wall);
        int way = reasonable.way(level.getMap().getElementByAdress(10, 10), reasonable.getCell());
        reasonable.setStocks(level.getStocks());
        std::vector<Character *> ans;
        level.seeEnemies(ans, &reasonable);
        reasonable.move1(level.getMap(), ans);
        reasonable.move1(level.getMap(), ans);
        REQUIRE(reasonable.way(reasonable.getCell(), level.getMap().getElementByAdress(15, 16)) == 0);
        reasonable.move1(level.getMap(), ans);
        reasonable.move1(level.getMap(), ans);
        reasonable.move1(level.getMap(), ans);
        reasonable.move1(level.getMap(), ans);
        REQUIRE(reasonable.way(reasonable.getCell(), level.getMap().getElementByAdress(15, 16)) > 0);
    } SECTION(
            "Situation11") { // Reasonable автоматически подбирает оружие, если оно в поле зрения, и идет искать врагов
        level.getMap().getElementByAdress(15, 10)->addItem(pistol);
        std::vector<Character *> ans;
        level.seeEnemies(ans, &reasonable);
        reasonable.move1(level.getMap(), ans);
        reasonable.move1(level.getMap(), ans);
        reasonable.move1(level.getMap(), ans);
        reasonable.move1(level.getMap(), ans);
        REQUIRE(reasonable.getCell() == level.getMap().getElementByAdress(15, 10));
        reasonable.move1(level.getMap(), ans);
        REQUIRE(*(reasonable.getActiveWeapon()) == *pistol);
        reasonable.move1(level.getMap(), ans);
        REQUIRE(reasonable.getCell() != level.getMap().getElementByAdress(15, 10));
    } SECTION("Situation12") { // Forager ходит в поисках предметов, когда находит, идет к ближайшей складской точке
        Forager forager;
        forager.setCell(level.getMap().getElementByAdress(10, 10));
        level.getMap().getElementByAdress(11, 12)->addItem(&medKit);
        level.getMap().getElementByAdress(11, 12)->addItem(&medKit);
        level.getMap().getElementByAdress(11, 12)->addItem(pistol);
        REQUIRE(level.getMap().getElementByAdress(11, 12)->getItems().size() == 3);
        level.getMap().getElementByAdress(19, 16)->setType(TypeOfPoint::stock);
        level.getMap().getElementByAdress(7, 10)->setType(TypeOfPoint::stock);
        level.getMap().getElementByAdress(8, 8)->setType(TypeOfPoint::wall);
        int way = forager.way(level.getMap().getElementByAdress(11, 12), forager.getCell());
        forager.setStocks(level.getStocks());
        std::vector<Character *> ans;
        level.seeEnemies(ans, &forager);
        // не меняются координаты у Forager, исправить!
        forager.move1(level.getMap(), ans);
        REQUIRE(forager.way(forager.getCell(), level.getMap().getElementByAdress(11, 12)) < way);
        forager.move1(level.getMap(), ans);
        forager.move1(level.getMap(), ans);
        REQUIRE(forager.way(forager.getCell(), level.getMap().getElementByAdress(11, 12)) == 0);
        forager.move1(level.getMap(), ans);
        REQUIRE(forager.getInventory().getItems().size() == 3);
        REQUIRE(level.getMap().getElementByAdress(11, 12)->getItems().size() == 0);
        way = forager.way(forager.getCell(), level.getMap().getElementByAdress(7, 10));
        forager.move1(level.getMap(), ans);
        forager.move1(level.getMap(), ans);
        forager.move1(level.getMap(), ans);
        forager.move1(level.getMap(), ans);
        REQUIRE(forager.way(forager.getCell(), level.getMap().getElementByAdress(7, 10)) < way);
        forager.move1(level.getMap(), ans);
        forager.move1(level.getMap(), ans);
        forager.move1(level.getMap(), ans);
        REQUIRE(forager.way(forager.getCell(), level.getMap().getElementByAdress(7, 10)) == 0);
        way = forager.way(forager.getCell(), level.getMap().getElementByAdress(19, 16));
        forager.move1(level.getMap(), ans);
        forager.move1(level.getMap(), ans);
        REQUIRE(forager.way(forager.getCell(), level.getMap().getElementByAdress(19, 16)) != 0);
//        REQUIRE(fo)
    } SECTION("Situation13") { // Forager ходит на рандом
        Level level1(10, 10);
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(5, 5));
        std::vector<Character *> enemies;
        forager.move1(level1.getMap(), enemies);
        REQUIRE((forager.getX() != 5 || forager.getY() != 5) == true);
    } SECTION("Situation14") { // Operative атака вниз + атака через стену + через стекло
        Level level1(15, 15);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(10, 8));
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(12, 8));
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() != forager.getMaxHealth());
        int hp = forager.getHealth();
        level1.getMap().getElementByAdress(11, 8)->setType(TypeOfPoint::wall);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        level1.getMap().getElementByAdress(11, 8)->setType(TypeOfPoint::glass);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(11, 8)->getType() == TypeOfPoint::tile);
    } SECTION("Situation15") { // Operative атака вправо + атака через стену + через стекло
        Level level1(15, 15);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(10, 8));
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(10, 10));
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() != forager.getMaxHealth());
        int hp = forager.getHealth();
        level1.getMap().getElementByAdress(10, 9)->setType(TypeOfPoint::wall);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        level1.getMap().getElementByAdress(10, 9)->setType(TypeOfPoint::glass);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(10, 9)->getType() == TypeOfPoint::tile);

    } SECTION("Situation16") { // Operative атака влево + атака через стену + через стекло
        Level level1(15, 15);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(10, 8));
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(10, 6));
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() != forager.getMaxHealth());
        int hp = forager.getHealth();
        level1.getMap().getElementByAdress(10, 7)->setType(TypeOfPoint::wall);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        level1.getMap().getElementByAdress(10, 7)->setType(TypeOfPoint::glass);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(10, 7)->getType() == TypeOfPoint::tile);
    } SECTION("Situation17") { // Operative атака вверх + через стену + через стекло
        Level level1(15, 15);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(10, 8));
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(6, 8));
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() != forager.getMaxHealth());
        int hp = forager.getHealth();
        level1.getMap().getElementByAdress(7, 8)->setType(TypeOfPoint::wall);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        level1.getMap().getElementByAdress(7, 8)->setType(TypeOfPoint::glass);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(7, 8)->getType() == TypeOfPoint::tile);
    } SECTION("Situation18") { // Reasonable атака вниз + атака через стену + через стекло
        Level level1(15, 15);
        Reasonable reasonable1;
        reasonable1.setCell(level1.getMap().getElementByAdress(10, 8));
        reasonable1.setActiveWeapon(pistol);
        Operative oper;

        oper.setCell(level1.getMap().getElementByAdress(12, 8));
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() != oper.getMaxHealth());
        int hp = oper.getHealth();
        level1.getMap().getElementByAdress(11, 8)->setType(TypeOfPoint::wall);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        level1.getMap().getElementByAdress(11, 8)->setType(TypeOfPoint::glass);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(11, 8)->getType() == TypeOfPoint::tile);
    } SECTION("Situation19") { // Reasonable атака вправо + атака через стену + через стекло
        Level level1(15, 15);
        Reasonable reasonable1;

        reasonable1.setCell(level1.getMap().getElementByAdress(10, 8));
        reasonable1.setActiveWeapon(pistol);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(10, 10));
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() != oper.getMaxHealth());
        int hp = oper.getHealth();
        level1.getMap().getElementByAdress(10, 9)->setType(TypeOfPoint::wall);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        level1.getMap().getElementByAdress(10, 9)->setType(TypeOfPoint::glass);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(10, 9)->getType() == TypeOfPoint::tile);

    } SECTION("Situation20") { // Reasonable атака влево + атака через стену + через стекло
        Level level1(15, 15);
        Reasonable reasonable1;
        reasonable1.setCell(level1.getMap().getElementByAdress(10, 8));
        reasonable1.setActiveWeapon(pistol);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(10, 6));
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() != oper.getMaxHealth());
        int hp = oper.getHealth();
        level1.getMap().getElementByAdress(10, 7)->setType(TypeOfPoint::wall);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        level1.getMap().getElementByAdress(10, 7)->setType(TypeOfPoint::glass);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(10, 7)->getType() == TypeOfPoint::tile);
    } SECTION("Situation21") { // Reasonable атака вверх + через стену + через стекло
        Level level1(15, 15);
        Reasonable reasonable1;
        reasonable1.setCell(level1.getMap().getElementByAdress(10, 8));
        reasonable1.setActiveWeapon(pistol);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(6, 8));
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() != oper.getMaxHealth());
        int hp = oper.getHealth();
        level1.getMap().getElementByAdress(7, 8)->setType(TypeOfPoint::wall);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        level1.getMap().getElementByAdress(7, 8)->setType(TypeOfPoint::glass);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(7, 8)->getType() == TypeOfPoint::tile);
    }SECTION("Situation22") { // Reasonable атакует без оружия
        Level level1(15, 15);
        Reasonable reasonable1;
        reasonable1.setCell(level1.getMap().getElementByAdress(10, 8));
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(6, 8));
        level1.pushEnemy(&reasonable1);
        level1.pushCharacter(&oper);
        int way = reasonable1.way(reasonable1.getCell(), oper.getCell());
        level1.moveEnemy();
        REQUIRE(reasonable1.way(reasonable1.getCell(), oper.getCell()) < way);
        REQUIRE(oper.getHealth() != oper.getMaxHealth());
    } SECTION("Situation23") { // wild двигается на рандом, если не видит никого вокруг
        Level level1(50, 50);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(0, 0));
        Wild wild;
        wild.setCell(level1.getMap().getElementByAdress(30, 30));
        level1.pushEnemy(&wild);
        level1.pushCharacter(&oper);
        level1.moveEnemy();
        REQUIRE((wild.getX() != 30 || wild.getY() != 30) == true);
    } SECTION("Situation24") { // смерть Forager
        Level level1(10, 15);
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(3, 8));
        forager.takeItem(pistol);
        forager.takeItem(pistol);
        forager.takeItem(sniper);
        forager.takeItem(&medKit);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(6, 8));
        level1.pushCharacter(&oper);
        level1.pushEnemy(&forager);
        oper.attack(&forager, level1.getMap());
        oper.attack(&forager, level1.getMap());
        oper.attack(&forager, level1.getMap());
        oper.attack(&forager, level1.getMap());
        oper.attack(&forager, level1.getMap());
        oper.attack(&forager, level1.getMap());
        oper.attack(&forager, level1.getMap());
        oper.attack(&forager, level1.getMap());
        oper.attack(&forager, level1.getMap());
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == 0);
        REQUIRE(level1.getMap().getElementByAdress(3, 8)->getItems().size() == 4);
        REQUIRE(forager.getInventory().getItems().size() == 0);
        REQUIRE(forager.getCell() == nullptr);
    } SECTION("Situation25") { // Reasonable умирает
        Level level1(10, 15);
        Reasonable reasonable1;
        reasonable1.setCell(level1.getMap().getElementByAdress(3, 8));
        reasonable1.takeWeapon(pistol);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(6, 8));
        level1.pushCharacter(&oper);
        level1.pushEnemy(&reasonable1);
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        REQUIRE(reasonable1.getHealth() == 0);
        REQUIRE(level1.getMap().getElementByAdress(3, 8)->getItems().size() == 1);
        REQUIRE(*reasonable1.getActiveWeapon() == Weapon());
        REQUIRE(reasonable1.getCell() == nullptr);
    } SECTION("Situation26") {
        Level level1(10, 15);
        Wild wild;
        wild.setCell(level1.getMap().getElementByAdress(3, 8));
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(6, 8));
        level1.pushCharacter(&oper);
        level1.pushEnemy(&wild);
        oper.attack(&wild, level1.getMap());
        oper.attack(&wild, level1.getMap());
        oper.attack(&wild, level1.getMap());
        oper.attack(&wild, level1.getMap());
        oper.attack(&wild, level1.getMap());
        oper.attack(&wild, level1.getMap());
        oper.attack(&wild, level1.getMap());
        oper.attack(&wild, level1.getMap());
        oper.attack(&wild, level1.getMap());
        oper.attack(&wild, level1.getMap());
        REQUIRE(wild.getHealth() == 0);
        REQUIRE(wild.getCell() == nullptr);
    } SECTION("Situation27") {
        Level level1(10, 15);
        Reasonable oper;
        oper.setCell(level1.getMap().getElementByAdress(3, 8));
        oper.takeWeapon(pistol);
        Operative reasonable1;
        reasonable1.takeItem(pistol);
        reasonable1.takeItem(pistol);
        reasonable1.takeItem(sniper);
        reasonable1.setCell(level1.getMap().getElementByAdress(6, 8));
        level1.pushCharacter(&reasonable1);
        level1.pushEnemy(&oper);
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        oper.attack(&reasonable1, level1.getMap());
        REQUIRE(reasonable1.getHealth() == 0);
        REQUIRE(level1.getMap().getElementByAdress(6, 8)->getItems().size() == 4);
        REQUIRE(*reasonable1.getActiveWeapon() == Weapon());
        REQUIRE(reasonable1.getCell() == nullptr);
    } SECTION("Situation28") { // оперативник пытается взять больше, чем ему позволено
        Operative oper;
        oper.takeItem(pistol);
        oper.takeItem(pistol);
        oper.takeItem(pistol);
        oper.takeItem(pistol);
        oper.takeItem(pistol);
        REQUIRE_THROWS(oper.takeItem(pistol));
    }
    Level level1(15, 20);
    Operative oper;
    oper.setCell(level1.getMap().getElementByAdress(6, 7));
    level1.pushCharacter(&oper);
    SECTION("Situation29") { // передвижение Operative
        level1.makeActionPlayer({1}, &oper);
        REQUIRE((oper.getX() == 6 && oper.getY() == 6) == true);
    } SECTION("Situation30") { // передвижение Operative
        level1.makeActionPlayer({2}, &oper);
        REQUIRE((oper.getX() == 7 && oper.getY() == 5) == true);
    } SECTION("Situation31") { // передвижение Operative
        level1.makeActionPlayer({3}, &oper);
        REQUIRE((oper.getX() == 8 && oper.getY() == 6) == true);
    } SECTION("Situation32") { // передвижение Operative
        level1.makeActionPlayer({4}, &oper);
        REQUIRE(oper.getCell() == level1.getMap().getElementByAdress(7, 7));
        REQUIRE((oper.getX() == 7 && oper.getY() == 7) == true);
    } SECTION("Situation33") { // передвижение Operative
        level1.getMap().getElementByAdress(7, 7)->changeTypeOfCell(TypeOfPoint::wall);
        level1.makeActionPlayer({4}, &oper);
        REQUIRE((oper.getX() == 7 && oper.getY() == 6) == true);
    }
}


TEST_CASE("Operative") {
    Level level1(15, 20);
    Operative oper;
    oper.setCell(level1.getMap().getElementByAdress(6, 7));
    level1.pushCharacter(&oper);
    Weapon *pistol = Weapon::createPistol();
    Weapon *sniper = Weapon::createSniper();
    MedKit medKit;
    SECTION("Move Left") {
        oper.move(1, level1.getMap());
        REQUIRE((oper.getX() == 6 && oper.getY() == 6) == true);
    } SECTION("Move Up") {
        oper.move(2, level1.getMap());
        REQUIRE((oper.getX() == 7 && oper.getY() == 5) == true);
    } SECTION("Move Right") {
        oper.move(3, level1.getMap());
        REQUIRE((oper.getX() == 8 && oper.getY() == 6) == true);
    } SECTION("Move Down") {
        oper.move(4, level1.getMap());
        REQUIRE(oper.getCell() == level1.getMap().getElementByAdress(7, 7));
        REQUIRE((oper.getX() == 7 && oper.getY() == 7) == true);
    } SECTION("Move Down Cansel") {
        level1.getMap().getElementByAdress(7, 7)->changeTypeOfCell(TypeOfPoint::wall);
        oper.move(4, level1.getMap());
        REQUIRE((oper.getX() == 7 && oper.getY() == 6) == true);
    } SECTION("Inventory tests") {
        oper.takeItem(pistol);
        REQUIRE(oper.getInventory().getCountOfItems() == 1);
        REQUIRE(oper.getInventory().getItems()[0] == pistol);
        oper.dropItem(0);
        REQUIRE(oper.getInventory().getCountOfItems() == 0);
        REQUIRE(level1.getMap().getElementByAdress(6, 7)->getItems().size() == 1);
        REQUIRE(level1.getMap().getElementByAdress(6, 7)->getItems()[0] == pistol);
        oper.takeItem(pistol);
        oper.takeItem(pistol);
        oper.takeItem(pistol);
        oper.takeItem(pistol);
        oper.takeItem(pistol);
        REQUIRE_THROWS(oper.takeItem(pistol));
    } SECTION("Attack Down + Attack threw wall + Destroy glass") {
        oper.setCell(level1.getMap().getElementByAdress(10, 8));
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(12, 8));
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() != forager.getMaxHealth());
        int hp = forager.getHealth();
        level1.getMap().getElementByAdress(11, 8)->setType(TypeOfPoint::wall);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        level1.getMap().getElementByAdress(11, 8)->setType(TypeOfPoint::glass);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(11, 8)->getType() == TypeOfPoint::tile);
    } SECTION("Attack Right + Attack threw wall + Destroy glass") {
        oper.setCell(level1.getMap().getElementByAdress(10, 8));
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(10, 10));
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() != forager.getMaxHealth());
        int hp = forager.getHealth();
        level1.getMap().getElementByAdress(10, 9)->setType(TypeOfPoint::wall);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        level1.getMap().getElementByAdress(10, 9)->setType(TypeOfPoint::glass);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(10, 9)->getType() == TypeOfPoint::tile);

    } SECTION( "Attack Left + Attack threw wall + Destroy glass") {
        oper.setCell(level1.getMap().getElementByAdress(10, 8));
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(10, 6));
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() != forager.getMaxHealth());
        int hp = forager.getHealth();
        level1.getMap().getElementByAdress(10, 7)->setType(TypeOfPoint::wall);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        level1.getMap().getElementByAdress(10, 7)->setType(TypeOfPoint::glass);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(10, 7)->getType() == TypeOfPoint::tile);
    } SECTION("Attack Up + Attack threw wall + Destroy glass") {
        oper.setCell(level1.getMap().getElementByAdress(10, 8));
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(6, 8));
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() != forager.getMaxHealth());
        int hp = forager.getHealth();
        level1.getMap().getElementByAdress(7, 8)->setType(TypeOfPoint::wall);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        level1.getMap().getElementByAdress(7, 8)->setType(TypeOfPoint::glass);
        oper.attack(&forager, level1.getMap());
        REQUIRE(forager.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(7, 8)->getType() == TypeOfPoint::tile);
    } SECTION("Weapon swap") {
        level1.getMap().getElementByAdress(6, 7)->addItem(sniper);
        oper.takeWeapon(sniper);
        REQUIRE(*(Weapon *)(level1.getMap().getElementByAdress(6, 7)->getItems()[0]) == *pistol);
        REQUIRE(*(oper.getActiveWeapon()) == *sniper);
    } SECTION("MedKit use") {
        oper.takeItem(&medKit);
        oper.changeHealth(20, -1);
        REQUIRE(oper.getHealth() != oper.getMaxHealth());
        int hp = oper.getHealth();
        oper.useItem(0);
        REQUIRE(oper.getHealth() > hp);
    } SECTION("Weapon Reload") {
        ContainerForBullet container;
        oper.takeItem(&container);
        oper.getActiveWeapon()->shoot();
        int size = ((ContainerForBullet *)(oper.getInventory().getItems()[0]))->getCurrentSize();
        oper.reload();
        REQUIRE(((ContainerForBullet *)(oper.getInventory().getItems()[0]))->getCurrentSize() == size - oper.getActiveWeapon()->getMaxCountOfBullet());
    } SECTION("Dead") {
        oper.setCell(level1.getMap().getElementByAdress(6, 7));
        oper.changeHealth(150, -1);
        REQUIRE(oper.getCell() == nullptr);
    }
}


TEST_CASE("Reasonable") {
    Weapon *pistol = Weapon::createPistol();
    SECTION("Attack Down + Attack threw wall + Destroy glass") {
        Level level1(15, 15);
        Reasonable reasonable1;
        reasonable1.setCell(level1.getMap().getElementByAdress(10, 8));
        reasonable1.setActiveWeapon(pistol);
        Operative oper;

        oper.setCell(level1.getMap().getElementByAdress(12, 8));
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() != oper.getMaxHealth());
        int hp = oper.getHealth();
        level1.getMap().getElementByAdress(11, 8)->setType(TypeOfPoint::wall);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        level1.getMap().getElementByAdress(11, 8)->setType(TypeOfPoint::glass);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(11, 8)->getType() == TypeOfPoint::tile);
    } SECTION("Attack Right + Attack threw wall + Destroy glass") {
        Level level1(15, 15);
        Reasonable reasonable1;

        reasonable1.setCell(level1.getMap().getElementByAdress(10, 8));
        reasonable1.setActiveWeapon(pistol);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(10, 10));
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() != oper.getMaxHealth());
        int hp = oper.getHealth();
        level1.getMap().getElementByAdress(10, 9)->setType(TypeOfPoint::wall);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        level1.getMap().getElementByAdress(10, 9)->setType(TypeOfPoint::glass);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(10, 9)->getType() == TypeOfPoint::tile);

    } SECTION("Attack Left + Attack threw wall + Destroy glass") {
        Level level1(15, 15);
        Reasonable reasonable1;
        reasonable1.setCell(level1.getMap().getElementByAdress(10, 8));
        reasonable1.setActiveWeapon(pistol);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(10, 6));
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() != oper.getMaxHealth());
        int hp = oper.getHealth();
        level1.getMap().getElementByAdress(10, 7)->setType(TypeOfPoint::wall);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        level1.getMap().getElementByAdress(10, 7)->setType(TypeOfPoint::glass);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(10, 7)->getType() == TypeOfPoint::tile);
    } SECTION("Attack Up + Attack threw wall + Destroy glass") {
        Level level1(15, 15);
        Reasonable reasonable1;
        reasonable1.setCell(level1.getMap().getElementByAdress(10, 8));
        reasonable1.setActiveWeapon(pistol);
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(6, 8));
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() != oper.getMaxHealth());
        int hp = oper.getHealth();
        level1.getMap().getElementByAdress(7, 8)->setType(TypeOfPoint::wall);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        level1.getMap().getElementByAdress(7, 8)->setType(TypeOfPoint::glass);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == hp);
        REQUIRE(level1.getMap().getElementByAdress(7, 8)->getType() == TypeOfPoint::tile);
    } SECTION("Attack without weapon") {
        Level level1(15, 15);
        Reasonable reasonable1;
        reasonable1.setCell(level1.getMap().getElementByAdress(10, 8));
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(9, 8));
        level1.pushEnemy(&reasonable1);
        level1.pushCharacter(&oper);
        reasonable1.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() != oper.getMaxHealth());
    } SECTION("Take weapon") {
        Weapon *sniper = Weapon::createSniper();
        Level level1(15, 15);
        Reasonable reasonable1;
        reasonable1.setCell(level1.getMap().getElementByAdress(10, 8));
        level1.getMap().getElementByAdress(10, 8)->addItem(sniper);
        reasonable1.takeWeapon(sniper);
        REQUIRE(reasonable1.getActiveWeapon() == sniper);
        REQUIRE(level1.getMap().getElementByAdress(10, 8)->getItems().size() == 0);
    } SECTION("Dead") {
        Level level1(10, 10);
        Reasonable reasonable1;
        reasonable1.setCell(level1.getMap().getElementByAdress(6, 7));
        reasonable1.changeHealth(150, -1);
        REQUIRE(reasonable1.getCell() == nullptr);
    }
}

TEST_CASE("Forager") {
    SECTION("Take Item") {
        Level level1(20, 30);
        Weapon *pistol = Weapon::createPistol();
        Weapon *pistol1 = Weapon::createPistol();
        Weapon *pistol2 = Weapon::createPistol();
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(7, 5));
        level1.getMap().getElementByAdress(7, 5)->addItem(pistol);
        level1.getMap().getElementByAdress(7, 5)->addItem(pistol1);
        level1.getMap().getElementByAdress(7, 5)->addItem(pistol2);
        forager.takeAllOfItems();
        REQUIRE(forager.getInventory().getItems().size() == 3);
        REQUIRE(level1.getMap().getElementByAdress(7, 5)->getItems().size() == 0);
    } SECTION("Drop item") {
        Level level1(20, 30);
        Weapon *pistol = Weapon::createPistol();
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(6, 9));
        level1.getMap().getElementByAdress(6, 9)->addItem(pistol);
        forager.takeItem(pistol);
        forager.dropItem(0);
        REQUIRE(forager.getInventory().getItems().size() == 0);
        REQUIRE(level1.getMap().getElementByAdress(6, 9)->getItems().size() == 1);
        REQUIRE((Weapon *)(level1.getMap().getElementByAdress(6, 9)->getItems()[0]) == pistol);
    } SECTION("Dead") {
        Level level1(10, 10);
        Forager forager;
        forager.setCell(level1.getMap().getElementByAdress(6, 7));
        forager.changeHealth(150, -1);
        REQUIRE(forager.getCell() == nullptr);
    }
}

TEST_CASE("Wild") {
    SECTION("Attack") {
        Level level1(10, 15);
        Wild wild;
        wild.setCell(level1.getMap().getElementByAdress(4, 3));
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(3, 3));
        level1.pushCharacter(&oper);
        level1.pushEnemy(&wild);
        wild.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() != oper.getMaxHealth());
        REQUIRE(wild.getTime() != wild.getMaxTime());
    } SECTION("Attack Cansel") {
        Level level1(10, 15);
        Wild wild;
        wild.setCell(level1.getMap().getElementByAdress(4, 3));
        Operative oper;
        oper.setCell(level1.getMap().getElementByAdress(7, 8));
        level1.pushCharacter(&oper);
        level1.pushEnemy(&wild);
        wild.attack(&oper, level1.getMap());
        REQUIRE(oper.getHealth() == oper.getMaxHealth());
        REQUIRE(wild.getTime() == wild.getMaxTime());
    }
    SECTION("Dead") {
        Level level1(10, 10);
        Wild wild;
        wild.setCell(level1.getMap().getElementByAdress(6, 7));
        wild.changeHealth(150, -1);
        REQUIRE(wild.getCell() == nullptr);
    }
}


TEST_CASE("MATRIX") {
    SECTION("DefaultConstructor") {
        Matrix<Cell> matr(15, 10);
        for (auto i: matr) {
            REQUIRE(i.getType() == TypeOfPoint::tile);
        }
        REQUIRE(matr.getCols() == 10);
        REQUIRE(matr.getRows() == 15);
        Matrix<Cell> matr1;
        REQUIRE(matr1.getRows() == 0);
        REQUIRE(matr1.getCols() == 0);
    } SECTION("CopyConstructor") {
        Matrix<int> matr(10, 10);
        for (auto i = matr.begin(); i != matr.end(); i++) {
            (*i) = i.getIndex();
        }
        Matrix<int> matr1(matr);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                REQUIRE((matr.getElement(i, j) == matr1.getElement(i, j)) == true);
            }
        }
    } SECTION("MoveConstructor") {
        Matrix<int> matr(10, 10);
        for (auto i = matr.begin(); i != matr.end(); i++) {
            (*i) = i.getIndex();
        }
        Matrix<int> matr1(matr);
        Matrix<int> matr2 = std::move(matr);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                REQUIRE((matr1.getElement(i, j) == matr2.getElement(i, j)) == true);
            }
        }
        REQUIRE_THROWS(matr.getElement(5, 2));
    } SECTION("Special Iterator") {
        Matrix<int> matr(10, 10);
        std::function func = [&matr](int element) {
            return element % 10 == 0;
        };
        for (auto i = matr.begin(); i != matr.end(); i++) {
            *i = i.getIndex();
        }
        std::vector<int> ans;
        for (auto i = matr.beginSpecial(func); i != matr.endSpecial(func); i++) {
            ans.push_back(*i);
        }
        std::vector<int> check = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
        REQUIRE(check == ans);
    } SECTION("[][]") {
        Matrix<int> matr(10, 10);
        for (auto i = matr.begin(); i != matr.end(); i++) {
            *i = i.getIndex();
        }
        REQUIRE(55 == *(matr[5][5]));
        *(matr[5][5]) = 100;
        REQUIRE(100 == *(matr[5][5]));
    } SECTION("[][] for cell") {
        Matrix<Cell> matr(8, 9);
        Cell cell(5, 3);
        for (auto i = matr.begin(); i != matr.end(); i++) {
            (*i).setPoint(i.getY(), i.getX());
        }
        Cell check = *matr[5][3];
        REQUIRE(check == cell);
        REQUIRE(matr[5][3]->getType() == TypeOfPoint::tile);
        matr[5][3]->changeTypeOfCell(TypeOfPoint::wall);
        REQUIRE(matr[5][3]->getType() == TypeOfPoint::wall);
    }
}