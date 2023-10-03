//
// Created by vadim on 17.09.2023.
//

#ifndef _DECK_H
#define _DECK_H
#include <iostream>
#include "../../SimpleClass/cards/cards.h"


namespace Lab2 {
    class Deck{
    private:
        int top = 0;
        static const int countMax = 100;
        Card deck[countMax];
        int cardsMatrix[4][13];
    public:
        Deck(void);
        explicit Deck(int cnt);


        Card *getDeck() {
            return deck;
        }

        // nodiscard указывает что возвращаемое значение нельзя игнорировать и обязательно должно быть внесено в переменную
        [[nodiscard]] int getSize() const {return top;}
        [[nodiscard]] auto getCardMatrix() const {return cardsMatrix;}
        [[nodiscard]] int getMaxSize() const {return countMax;}
        void createCardsMatrix(int cnt);
        void deleteDublicateCardsMatrix();
        void changeCardsMatrix(int rang, int suit, int op);
        void push(const Card & = Lab2::Card());
        void push(int nrang, int nsuit);
        Card pop(int index);
        bool equal(const Deck &other);


        std::ostream &printCardsMatrix(std::ostream &c);
        std::ostream &printDeck(std::ostream &c);
        void operator >> (Deck &other);

        void mixing();

        int checkRepeated();
        Card &operator[] (int index);
        Deck oneSuitDeck(int suit) const;
        void orderByRang();
        void orderBySuit();
        Deck operator+(Deck const &) const;

        bool operator==(Deck &);
    };

}

#endif //_DECK_H
