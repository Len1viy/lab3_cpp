//
// Created by vadim on 16.10.2023.
//

#include "ContainerForBullet.h"

namespace inventory {
    void ContainerForBullet::takeFromContainer(int count) {
        if (count > currentSize) return;
        else currentSize -= count;
    }
} // inventory