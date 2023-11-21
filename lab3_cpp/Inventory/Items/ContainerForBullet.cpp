//
// Created by vadim on 16.10.2023.
//

#include "ContainerForBullet.h"
#include "../../Character/Kinds/Operative.h"


//void ContainerForBullet::takeFromContainer(int count) {
//    if (count > currentSize) return;
//    else currentSize -= count;
//}
// вынести changeTime в метод перезарядки
int ContainerForBullet::use(Operative &oper) {
    if (oper.getTime() < oper.getActiveWeapon()->getPointsForReload()) return 0;
    oper.getActiveWeapon()->reload();
    currentSize -= oper.getActiveWeapon()->getMaxCountOfBullet();
    oper.changeTime(oper.getActiveWeapon()->getPointsForReload(), -1);
    if (currentSize == 0) {
        int index;
        for (int i = 0; i < oper.getInventory().getItems().size(); i++) {
            if (oper.getInventory().getItems()[i] == this) {
                index = i;
                break;
            }
        }
        oper.deleteFromInventory(index);
    }
    return oper.getActiveWeapon()->getPointsForReload();
}

//std::ostream &ContainerForBullet::print(std::ostream &c) {
//    c << "Contaiter For Bullets: ";
//    if (bullet == BulletType::pistol) c << "Bullet Type - pistol; ";
//    else if (bullet == BulletType::sniper) c << "Bullet Type - sniper; ";
//    else if (bullet == BulletType::assault) c << "Bullet Type - assault; ";
//    else if (bullet == BulletType::expansive) c << "Bullet Type - shotgun; ";
//    c << "Count: " << currentSize << "/" << maxSize << "\n";
//    return c;
//}

bool ContainerForBullet::operator==(const ContainerForBullet &container) const {
    return bullet == container.bullet && currentSize == container.currentSize && maxSize == container.maxSize;
}

bool ContainerForBullet::operator!=(const ContainerForBullet &container) const {
    return !(*this == container);
}


//void ContainerForBullet::use(Operative *character) {
//    character->getActiveWeapon()->reload();
//    currentSize -= character->getActiveWeapon()->getMaxCountOfBullet();
//    character->changeTime(character->getActiveWeapon()->getPointsForReload(), -1);
//}
