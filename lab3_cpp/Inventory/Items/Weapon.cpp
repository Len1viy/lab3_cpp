//
// Created by vadim on 16.10.2023.
//

#include "Weapon.h"
#include "../../Character/Kinds/Operative.h"


// логика стрельбы - кол-во очков для стрельбы = кол-ву выстреливаемых патронов
// pointsForReload - кол-во патронов, которые нужно перезарядить
int Weapon::getDamage() {
    shoot();
    return rand() % (damageMax - damageMin) + damageMin;

}


void Weapon::shoot() {
    --currentCountOfBullets;
}

void Weapon::reload() {
    currentCountOfBullets = maxCountOfBullets;
}

Weapon &Weapon::operator=(const Weapon &weapon1) {
    damageMin = weapon1.damageMin;
    damageMax = weapon1.damageMax;
    pointsForReload = weapon1.pointsForReload;
    pointsForShoot = weapon1.pointsForShoot;
    bullet = weapon1.bullet;
    currentCountOfBullets = weapon1.currentCountOfBullets;
    maxCountOfBullets = weapon1.maxCountOfBullets;
    return *this;
}

bool Weapon::operator==(const Weapon &weapon1) const {
    return bullet == weapon1.bullet && pointsForShoot == weapon1.pointsForShoot &&
           currentCountOfBullets == weapon1.currentCountOfBullets && maxCountOfBullets == weapon1.maxCountOfBullets &&
           damageMin == weapon1.damageMin && damageMax == weapon1.damageMax;
}

bool Weapon::operator!=(const Weapon &weapon1) const {
    return !(*this == weapon1);
}


//std::ostream &operator<<(std::ostream &c, Weapon *weapon) {
//    if (weapon == nullptr) return c;
//    if (weapon->bullet == BulletType::pistol) c << "Type - pistol; ";
//    else if (weapon->bullet == BulletType::sniper) c << "Type - sniper; ";
//    else if (weapon->bullet == BulletType::assault) c << "Type - assault rifle; ";
//    else if (weapon->bullet == BulletType::expansive) c << "Type - shotgun; ";
//    else if (weapon->bullet == BulletType::none) return c << "NONE; ";
//    c << "Bullets " << weapon->currentCountOfBullets << "/" << weapon->maxCountOfBullets << "\n";
//    return c;
//
//}

int Weapon::use(Operative &oper) {
    if (*(oper.getActiveWeapon()) != Weapon()) {
        Weapon *weapon = oper.getActiveWeapon();
        int index;
        for (int i = 0; i < oper.getInventory().getItems().size(); i++) {
            if (oper.getInventory().getItems()[i] == this) {
                index = i;
                break;
            }
        }
        oper.deleteFromInventory(index);
        oper.throwWeapon();
        oper.takeItem(weapon);
        oper.setActiveWeapon(this);
    } else {
        int index = -1;
        for (int i = 0; i < oper.getInventory().getItems().size(); i++) {
            if (oper.getInventory().getItems()[i] == this) {
                index = i;
                break;
            }
        }
        if (index == -1) oper.deleteFromInventory(index);
        oper.setActiveWeapon(this);
    }
    return 0;

}

//std::ostream &Weapon::print(std::ostream &c) {
//    if (this == nullptr) return c;
//    c << "Weapon: ";
//    if (bullet == BulletType::pistol) c << "Type - pistol; ";
//    else if (bullet == BulletType::sniper) c << "Type - sniper; ";
//    else if (bullet == BulletType::assault) c << "Type - assault rifle; ";
//    else if (bullet == BulletType::expansive) c << "Type - shotgun; ";
//    c << "Bullets " << currentCountOfBullets << "/" << maxCountOfBullets << "\n";
//    return c;
//}

//void Weapon::use(Operative *character) {
//    Weapon *weapon = character->getActiveWeapon();
//    character->setActiveWeapon(this);
//    character->getInventory().addItem(weapon);
//}

