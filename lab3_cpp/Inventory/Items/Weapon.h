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
    /**
     * @brief Constructor
     * @param w - weight of weapon
     * @param dMin - minimal damage
     * @param dMax - maximum damage
     * @param PFS - points of time for shooting
     * @param PFR - points of time for reload
     * @param bul - type of bullets which item uses
     * @param curCnt - count of bullets in chamber
     * @param maxCnt - maximum count of bullets in chamber
     */
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
/**
 * @brief Default constructor
 */
    Weapon() : Item(TypeOfItem::weapon, 20), damageMin(0), damageMax(0), pointsForShoot(0),
               pointsForReload(0), bullet(BulletType::none), currentCountOfBullets(0), maxCountOfBullets(0) {};
/**
 * @brief method of creating pistol
 * @return pointer to new pistol
 */
    static Weapon *createPistol() {
        return new Weapon(20, 10, 20, 4, 10, BulletType::pistol, 12, 12);
    }
/**
 * @brief method of creating sniper
 * @return pointer to new sniper
 */
    static Weapon *createSniper() {
        return new Weapon(50, 25, 50, 10, 20, BulletType::sniper, 3, 3);
    }
/**
 * @brief copy constructor
 * @param weapon1 weapon which we will copy
 */
    Weapon(Weapon &weapon1) noexcept: Item(TypeOfItem::weapon, weapon1.getWeight()), damageMin(weapon1.damageMin),
                                      damageMax(weapon1.damageMax),
                                      pointsForShoot(weapon1.pointsForShoot), pointsForReload(weapon1.pointsForReload),
                                      bullet(weapon1.bullet),
                                      currentCountOfBullets(weapon1.currentCountOfBullets),
                                      maxCountOfBullets(weapon1.maxCountOfBullets) {};
/**
 * @brief overloaded copy operator =
 * @param weapon1 the other weapon with which we will copy
 * @return new copied weapon
 */
    Weapon &operator=(const Weapon &weapon1);
/**
 * @brief method of get amount damage which will be applied
 * @return amount of damage
 */
    [[nodiscard]] int getDamage();
/**
 * @brief getter of minimal damage
 * @return minimal damage
 */
    [[nodiscard]] int getMinDamage() const { return damageMin; }
/**
 * @brief getter of maximum damage
 * @return maximum damage
 */
    [[nodiscard]] int getMaxDamage() const { return damageMin; }
/**
 * @brief setter of maximum damage
 * @param damage new maximum damage
 * @return changed weapon
 */
    Weapon &setMaxDamage(int damage) {
        damageMax = damage;
        return *this;
    };
/**
 * @brief getter if points for shoot
 * @return points for shoot
 */
    [[nodiscard]] int getPointsForShoot() const { return pointsForShoot; }
/**
 * @brief getter if points for reload
 * @return points for reload
 */
    [[nodiscard]] int getPointsForReload() const { return pointsForReload; }
/**
 * @brief getter of type of bullets which this weapon uses
 * @return type of bullets
 */
    [[nodiscard]] BulletType getBullet() const { return bullet; };
/**
 * @brief getter of current count of bullets
 * @return current count of bullets
 */
    [[nodiscard]] int getCurrentCountOfBuillet() const { return currentCountOfBullets; };
/**
 * @brief getter of maximum count of bullets
 * @return maximum count of bullets
 */
    [[nodiscard]] int getMaxCountOfBullet() const { return maxCountOfBullets; }
/**
 * @brief overloaded operator !=
 * @param other the other weapon with which we will compare
 * @return true if weapons are not equal and false if otherwise
 */
    bool operator!=(const Weapon &other) const;
/**
 * @brief setter of points of time for shoot
 * @param p points of time for shoot
 * @return changed weapon
 */
    Weapon &setPointsForShoot(int p) {
        pointsForShoot = p;
        return *this;
    }
/**
 * @brief setter of points of time for reload
 * @param p points of time for reload
 * @return changed weapon
 */
    Weapon &setPointsForReload(int p) {
        pointsForReload = p;
        return *this;
    }
/**
 * @brief setter of type of bullets which weapon uses
 * @param type type of bullets
 * @return changed weapon
 */
    Weapon &setBullet(BulletType type) {
        bullet = type;
        return *this;
    }
/**
 * @brief setter of current count of bullets
 * @param count current count of bullets
 * @return changed weapon
 */
    Weapon &setCurrentCountOfBuillet(int count) {
        currentCountOfBullets = count;
        return *this;
    }
/**
 * @brief setter of max count of bullets
 * @param count max count of bullets
 * @return changed weapon
 */
    Weapon &setMaxCountOfBullet(int count) {
        maxCountOfBullets = count;
        return *this;
    }
/**
 * @brief using weapon. operative takes this weapon to hands
 * @param oper - Operative which uses weapon
 * @return points for using
 */
    int use(Operative &oper) override;
/**
 * @brief overloaded operator ==
 * @param other the other weapon with which we will compare
 * @return true if weapons are equal and false if otherwise
 */
    bool operator==(const Weapon &other) const;
/**
 * @brief reloading weapon count of bullets changing to max count of bullets
 */
    void reload();
/**
 * @brief makes shoot from weapon, changes count of bullets by one
 */
    void shoot();

//    std::ostream &print(std::ostream &c) override;
//    friend std::ostream &operator<<(std::ostream &c, Weapon *weapon);

};


#endif //LAB3_CPP_WEAPON_H
