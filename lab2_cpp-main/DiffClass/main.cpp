#include <iostream>
#include "../SimpleClass/cards/cards.h"
#include "../SimpleClass/input/input.h"
#include "deck/deck.h"

// 1 - ?
// 2 - ?
// 3 - ?
// 4 - ?

int main() {
    system("chcp 65001");
    srand(time(0));

//    Lab2::Deck dc(10);
//    Lab2::Deck dc1(dc);
//    Lab2::Card card(dc[0].getRang(), dc[0].getSuit());
//    std::cout << dc;
//    Lab2::Deck dc2 = dc--;
//    std::cout << dc;
//    Lab2::Deck dc(10);
//    Lab2::Card card = dc[4];
//    Lab2::Card card1;
//    if ((dc[4] <=> card) == std::strong_ordering::equal) {
//        std::cout << "-----------------" << std::endl;
//        dc[4].print(std::cout);
//        card.print(std::cout);
//        card1.print(std::cout) << std::endl;
//    }
//    int rang = 3;
//    while (rang == dc[4].getRang()) rang = rand() % 13 + 2;
//    card.setRang(rang);
//    if ((dc[4] <=> card) == std::strong_ordering::equal) {
//        std::cout << "-----------------" << std::endl;
//        dc[4].print(std::cout);
//        card.print(std::cout);
//        card1.print(std::cout) << std::endl;
//    }
//    dc[4] = card1;
//    if ((dc[4] <=> card1) == std::strong_ordering::equal) {
//        std::cout << "-----------------" << std::endl;
//
//        dc[4].print(std::cout);
//        card.print(std::cout);
//        card1.print(std::cout) << std::endl;
//    }
//    Lab2::Deck dc;
//    input(3, dc);
//    std::cout << dc;
//    Lab2::Deck dc(10);
//    dc[4].setRang(10);
//    dc[4].setSuit(2);
//    dc[5].setRang(11);
//    dc[5].setSuit(2);
//    dc.printDeck(std::cout);
//    Lab2::Deck dc1(dc);
//    dc1.printDeck(std::cout);
//    dc.printDeck(std::cout);
//    dc1.printDeck(std::cout);
//    dc1[2] = Lab2::Card (2, 1);
//    dc1.printDeck(std::cout);
//    dc.printDeck(std::cout);
//    Lab2::Card card(10, 2);
//    Lab2::Card card1 = dc.pop(5);
//    dc.printDeck(std::cout);
//    dc1.printDeck(std::cout);
//    dc.printDeck(std::cout);
//    card.print(std::cout);
//    card1.print(std::cout);
//    Lab2::Deck dc1(2);
//    Lab2::Deck dc2(3);
//    int top = dc1.getSize();
//    dc1 += dc2;
//    dc1.printDeck(std::cout);
//    for (int i = 0; i <= top; i++) {
//        dc1[i].print(std::cout) << ' ';
//        dc2[i].print(std::cout) << std::endl;
//    }
//    std::cout << "Input (rang suit). 2 <= rang <= 13; 1 <= suit <= 4: >> ";
//    std::cin >> dc1;
//    std::cout << dc1;
//    Lab2::Deck dc;
//    dc.printDeck(std::cout);
//    dc.mixing();
//    Lab2::Deck dc1(dc);
//    dc.printDeck(std::cout);
//    dc1.printDeck(std::cout);
//    Lab2::Deck test(30);
//
//    Lab2::Deck test1(test);
//    test.printDeck(std::cout);
//
//    test1.printDeck(std::cout);
//    if (test1 == test) {
//        std::cout << "DA" << std::endl;
//    } else std::cout << "NET" << std::endl;

//    Lab2::Card card1;
//    card1.print(std::cout) << std::endl;
//    std::cout << card1.getRang() << std::endl;
//    Lab2::Card card2 = Lab2::Card();
//    Lab2::Card card3 = Lab2::Card();
//    Lab2::Deck dc = Lab2::Deck();
//    Lab2::Deck dc(10);
//    dc.printDeck(std::cout);
//    dc.pop(5).print(std::cout) << std::endl;
//    dc.printDeck(std::cout);
//    Lab2::Deck dc1(4);
//    Lab2::Deck dc2(5);
//    dc2.printDeck(std::cout);
//    dc2.mixing();
//    dc2.printDeck(std::cout);
//    std::cout << dc.getSize() << std::endl;
//    dc.printDeck(std::cout);
//    dc1 >> dc;
//    dc[10].print(std::cout) << std::endl;
//    dc.printDeck(std::cout);

//    std::cout << std::endl;

//    try {
//        dc.printDeck(std::cout);
//        std::cout << std::endl;
//        std::cout << "------------------" << std::endl;
//
//        dc1.printDeck(std::cout);
//        std::cout << std::endl;
//        std::cout << "------------------" << std::endl;
//        dc1 >> dc;
//        dc.printDeck(std::cout);
//
//        std::cout << std::endl;
//        std::cout << "------------------" << std::endl;
//        dc1.printDeck(std::cout);
//
//    } catch (std::exception &exception) {
//        std::cout << exception.what() << std::endl;
//    }

//    int command;
//    help();
//    do {
//        std::cout << "Input command: ";
//        getNum(command);
//        try {
//            if (command == 1) {
//                Lab2::Card card = Lab2::Card();
//                int rang;
//                std::cout << "Input rang: ";
//                card.setRang(getNum(rang));
//            }
//        } catch (std::exception &exception) {
//            cout << exception.what() << endl;
//        }
//    }
//    while (command != 0);



    return 0;
}
