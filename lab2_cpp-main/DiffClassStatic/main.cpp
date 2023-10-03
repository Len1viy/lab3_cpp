#include <iostream>
#include "../SimpleClass/cards/cards.h"
#include "../SimpleClass/input/input.h"
#include "deck/deck.h"

// 1 - ♦
// 2 - ♥
// 3 - ♣
// 4 - ♠


int main() {
    system("chcp 65001");
    srand(time(0));
    Lab2::Deck dc(56);
    Lab2::Deck dc1(5);
//    dc.printDeck(std::cout);
//    dc1.printDeck(std::cout);
//    dc1 + dc;
//    dc1.printDeck(std::cout);
//    dc.printDeck(std::cout);
    dc.printDeck(std::cout);
    dc1.printDeck(std::cout);
    dc.pop(1).print(std::cout);
//
//    dc.push();
//    dc.printDeck(std::cout);
//    Lab2::Deck newDeck = dc.oneSuitDeck(2);
//    newDeck.printDeck(std::cout);
//    newDeck.printCardsMatrix(std::cout);
//    newDeck.mixing();
//    newDeck.printDeck(std::cout);
//    newDeck.orderByRang();
//    newDeck.printDeck(std::cout);
//    Lab2::Deck dc2 = dc.oneSuitDeck(2);
//    dc2.printDeck(std::cout);
//    dc2.mixing();
//    dc2.printDeck(std::cout);
//    dc >> dc2;
//    dc2.printDeck(std::cout);
//    dc2.orderByRang();
//
//    dc2.printDeck(std::cout);

    return 0;
}
