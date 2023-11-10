//
// Created by vadim on 16.10.2023.
//

#include "Character.h"

namespace character {
    Character &Character::changeHealth(int healthOut, int operation) {
        if (characteristics.currentHealth + operation * healthOut < 0) {
            characteristics.currentHealth = 0;
            return *this;
        } else if (characteristics.currentHealth + operation * healthOut > characteristics.maxHealth) {
            characteristics.currentHealth = characteristics.maxHealth;
            return *this;
        }
        characteristics.currentHealth += operation * healthOut;
        return *this;
    }

    Character &Character::changeTime(int time, int operation) {
        if (characteristics.currentTime + operation * time < 0) {
            characteristics.currentTime = 0;
            return *this;
        } else if (characteristics.currentTime + operation * time > characteristics.maxTime) {
            characteristics.currentTime = characteristics.maxTime;
            return *this;
        }
        characteristics.currentTime += operation * time;
        return *this;
    }


    bool Character::isSeeSmb(level::Cell &cl) {
        if (cl.isCharacter()) return true;
        return false;
    }
} // character