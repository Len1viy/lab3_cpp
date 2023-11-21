//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_WEAPON_H
#define LAB3_CPP_WEAPON_H

#include "Item.h"


class Weapon : public Item {
protected:
    int damageMin;
    int damageMax;
    int pointsForShoot;
    int pointsForReload;
    BulletType bullet;
    int currentCountOfBullets;
    int maxCountOfBullets;
public:
    Weapon(int w, int dMin, int dMax, int PFS, int PFR, BulletType bul, int curCnt, int maxCnt) : Item(
            TypeOfItem::weapon, w),
                                                                                                  damageMin(dMin),
                                                                                                  damageMax(dMax),
                                                                                                  pointsForShoot(PFS),
                                                                                                  pointsForReload(PFR),
                                                                                                  bullet(bul),
                                                                                                  currentCountOfBullets(
                                                                                                          curCnt),
                                                                                                  maxCountOfBullets(
                                                                                                          maxCnt) {}

    Weapon() : Item(TypeOfItem::weapon, 20), damageMin(0), damageMax(0), pointsForShoot(0),
               pointsForReload(0), bullet(BulletType::none), currentCountOfBullets(0), maxCountOfBullets(0) {};

    static Weapon *createPistol() {
        return new Weapon(20, 10, 20, 4, 10, BulletType::pistol, 12, 12);
    }

    static Weapon *createSniper() {
        return new Weapon(50, 25, 50, 10, 20, BulletType::sniper, 3, 3);
    }

    Weapon(Weapon &weapon1) noexcept: Item(TypeOfItem::weapon, weapon1.getWeight()), damageMin(weapon1.damageMin),
                                      damageMax(weapon1.damageMax),
                                      pointsForShoot(weapon1.pointsForShoot), pointsForReload(weapon1.pointsForReload),
                                      bullet(weapon1.bullet),
                                      currentCountOfBullets(weapon1.currentCountOfBullets),
                                      maxCountOfBullets(weapon1.maxCountOfBullets) {};

    Weapon &operator=(const Weapon &weapon1);

    [[nodiscard]] int getDamage();

    [[nodiscard]] int getMinDamage() const { return damageMin; }

    [[nodiscard]] int getMaxDamage() const { return damageMin; }

    Weapon &setMaxDamage(int damage) {
        damageMax = damage;
        return *this;
    };

    [[nodiscard]] int getPointsForShoot() const { return pointsForShoot; }

    [[nodiscard]] int getPointsForReload() const { return pointsForReload; }

    [[nodiscard]] BulletType getBullet() const { return bullet; };

    [[nodiscard]] int getCurrentCountOfBuillet() const { return currentCountOfBullets; };

    [[nodiscard]] int getMaxCountOfBullet() const { return maxCountOfBullets; }

    bool operator!=(const Weapon &other) const;

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

    int use(Operative &oper) override;

    bool operator==(const Weapon &other) const;

    void reload();

    void shoot();

//    std::ostream &print(std::ostream &c) override;
//    friend std::ostream &operator<<(std::ostream &c, Weapon *weapon);

};


#endif //LAB3_CPP_WEAPON_H
