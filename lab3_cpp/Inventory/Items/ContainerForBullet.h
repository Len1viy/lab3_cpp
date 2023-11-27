//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_CONTAINERFORBULLET_H
#define LAB3_CPP_CONTAINERFORBULLET_H

#include "Item.h"

class ContainerForBullet : public Item {
private:
    BulletType bullet;
    int maxSize;
    int currentSize;
public:
    /**
     * Default constructor
     */
    ContainerForBullet() : Item(TypeOfItem::containerForBullets, 12), bullet(BulletType::pistol), maxSize(96),
                           currentSize(24) {};
/**
 * Constructor
 * @param n - type of item
 * @param w - weight of item
 * @param b - type of the bullets
 * @param mS - max size of container and current size of container
 */
    ContainerForBullet(TypeOfItem n, int w, BulletType b, int mS) : Item(n, w),
                                                                    bullet(b), maxSize(mS), currentSize(mS) {}
/**
 * @brief getter of type of bullets which container contains
 * @return type of bullets
 */
    [[nodiscard]] BulletType getBulletType() const { return bullet; }

    /**
     * @brief setter of bullet type
     * @param type - type of bullet
     * @return changed container
     */

    ContainerForBullet &setBulletType(const BulletType type) {
        bullet = type;
        return *this;
    }
/**
 * @brief setter of max size
 * @param nMaxSize - max size whoch we want to set to container
 * @return changed container
 */
    ContainerForBullet &setMaxSize(const int nMaxSize) {
        maxSize = nMaxSize;
        return *this;
    }
    /**
     * @brief getter of max size
     * @return max size of container
     */

    [[nodiscard]] int getMaxSize() const { return maxSize; };
/**
 * @brief setter of current size of container
 * @param size - new current size of container
 * @return changed container
 */
    ContainerForBullet &setCurrentSize(int size) {
        currentSize = size;
        return *this;
    };
/**
 * @brief getter of current size of container
 * @return current size of container
 */
    [[nodiscard]] int getCurrentSize() const { return currentSize; };
/**
 * @brief use of container. take count of bullets which active weapon in operative's hands contains
 * @param oper operative which uses the container
 * @return returned points of time which were spent for reload
 */
    int use(Operative &oper) override;


//        std::ostream &print(std::ostream &c) override;
/**
 * @brief overloaded operator !=
 * @param container container with which we compare
 * @return true if containers are not equal and false otherwise
 */
    bool operator!=(const ContainerForBullet &container) const;
/**
 * @brief overloaded operator ==
 * @param container container with which we compare
 * @return true if containers are equal and false otherwise
 */
    bool operator==(const ContainerForBullet &container) const;

};


#endif //LAB3_CPP_CONTAINERFORBULLET_H
