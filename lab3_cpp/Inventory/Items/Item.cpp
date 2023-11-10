//
// Created by vadim on 16.10.2023.
//

#include "Item.h"

namespace inventory {
    bool Item::isOwner() {
        if (owner == nullptr) return false;
        return true;
    }
} // game