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
    ContainerForBullet() : Item(TypeOfItem::containerForBullets, 12), bullet(BulletType::pistol), maxSize(96), currentSize(24) {};
        ContainerForBullet(TypeOfItem n, int w, BulletType b, int mS) : Item(n, w),
        bullet(b), maxSize(mS), currentSize(mS)
        {}

        [[nodiscard]] BulletType getBulletType() const {return bullet;}
        ContainerForBullet &setBulletType(const BulletType type) {
            bullet = type;
            return *this;
        }
        ContainerForBullet &setMaxSize(const int nMaxSize) {
            maxSize = nMaxSize;
            return *this;
        }
        [[nodiscard]] int getMaxSize() const {return maxSize;};
        ContainerForBullet & setCurrentSize(int size) {
            currentSize = size;
            return *this;
        };
        [[nodiscard]] int getCurrentSize() const {return currentSize;};

        int use(Operative &oper) override;

        void takeFromContainer(int count);

//        std::ostream &print(std::ostream &c) override;

        bool operator!=(const ContainerForBullet &container) const;
        bool operator==(const ContainerForBullet &container) const;

    };


#endif //LAB3_CPP_CONTAINERFORBULLET_H
