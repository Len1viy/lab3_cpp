//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_CONTAINERFORBULLET_H
#define LAB3_CPP_CONTAINERFORBULLET_H

#include "../../Level/Point.h"
#include "Item.h"

namespace inventory {
    class ContainerForBullet : public Item {
    private:
        BulletType bullet;
        int maxSize;
        int currentSize;
    public:
        ContainerForBullet(TypeOfItem n, int w, BulletType b, int mS) : Item(n, w),
        bullet(b), maxSize(mS), currentSize(mS)
        {}

        BulletType getBulletType() const {return bullet;}
        ContainerForBullet &setBulletType(const BulletType type) {
            bullet = type;
            return *this;
        }
        ContainerForBullet &setMaxSize(const int nMaxSize) {
            maxSize = nMaxSize;
            return *this;
        }
        int getMaxSize() const {return maxSize;};
        ContainerForBullet & setCurrentSize(int size) {
            currentSize = size;
            return *this;
        };
        int getCurrentSize() const {return currentSize;};
        void takeFromContainer(int count);

    };

} // inventory

#endif //LAB3_CPP_CONTAINERFORBULLET_H
