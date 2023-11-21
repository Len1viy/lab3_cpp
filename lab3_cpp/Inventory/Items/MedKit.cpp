//
// Created by vadim on 16.10.2023.
//

#include "MedKit.h"

#include "../../Character/Kinds/Operative.h"

//    void MedKit::use(character::Character *character) {
////        character->getType()
//    }
//void MedKit::use(Operative *character) {
//    character->changeHealth(health, 1);
//    character->changeTime(pointsForUsing, -1);
//    int index;
//    for (int i = 0; i < character->getInventory().getItems().size(); i++) {
//        if (character->getInventory().getItems()[i] == this) {
//            index = i;
//            break;
//        }
//    }
//    character->getInventory().deleteItem(index);
//}
int MedKit::use(Operative &oper) {
    if (oper.getTime() < pointsForUsing) return 0;
    oper.changeHealth(health, 1);
    oper.changeTime(pointsForUsing, -1);
    int index;
    for (int i = 0; i < oper.getInventory().getItems().size(); i++) {
        if (oper.getInventory().getItems()[i] == this) {
            index = i;
            break;
        }
    }
    oper.deleteFromInventory(index);
    return pointsForUsing;
}

//std::ostream &MedKit::print(std::ostream &c) {
//    c << "MedKit: " << health << "HP\n";
//    return c;
//}

bool MedKit::operator==(const MedKit &medKit) const {
    return health == medKit.health && pointsForUsing == medKit.pointsForUsing && getWeight() == medKit.getWeight();
}
