//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_WEAPON_H
#define LAB3_CPP_WEAPON_H

#include "iostream"
#include "Item.h"

namespace inventory {
    typedef enum BulletType {
        assault,
        sniper,
        expansive,
        pistol,
        none
    } BulletType;

    class Weapon : Item {
    private:
        int damageMin;
        int damageMax;
        int pointsForShoot;
        int pointsForReload;
        BulletType bullet;
        int currentCountOfBullets;
        int maxCountOfBullets;
    public:
        Weapon(int w, int dMin, int dMax, int PFS, int PFR, BulletType bul, int curCnt, int maxCnt) : Item(TypeOfItem::weapon, w),
        damageMin(dMin), damageMax(dMax), pointsForShoot(PFS), pointsForReload(PFR), bullet(bul), currentCountOfBullets(curCnt),
        maxCountOfBullets(maxCnt)
        {}

        Weapon() : Item(TypeOfItem::weapon, 0), damageMin(0), damageMax(0), pointsForShoot(0),
        pointsForReload(0), bullet(BulletType::none), currentCountOfBullets(0), maxCountOfBullets(0) {};

        int getDamage() const;
        int getMinDamage() const {return damageMin;}
        int getMaxDamage() const {return damageMin;}
        Weapon &setMaxDamage(int damage) {
            damageMax = damage;
            return *this;
        };
        int getPointsForShoot() const {return pointsForShoot;}
        int getPointsForReload() const {return pointsForReload;}
        BulletType getBullet() const {return bullet;};
        int getCurrentCountOfBuillet() const {return currentCountOfBullets;};
        int getMaxCountOfBullet() const {return maxCountOfBullets;}
        Weapon &setPointsForShoot(int p) {
            pointsForShoot = p;
            return *this;
        }
        Weapon &setPointsForReload(int p) {
            pointsForReload = p;
            return *this;
        }
        Weapon &setBullet(BulletType type) {
            bullet = type;
            return *this;
        }
        Weapon &setCurrentCountOfBuillet(int count) {
            currentCountOfBullets = count;
            return *this;
        }
        Weapon &setMaxCountOfBullet(int count) {
            maxCountOfBullets = count;
            return *this;
        }
        bool isHit(int acc);

//        void reload();
//        void shoot();

    };

} // inventory

#endif //LAB3_CPP_WEAPON_H
