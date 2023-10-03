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
        static const int reserveSize = 10;
        Card *deck;
        int countMax;
        int cardsMatrix[4][13];
        int top = 0;
        void resize(int new_size);
        Deck &setTop(int top);
    public:
        Deck(void);
        explicit Deck(int cnt);
        ~Deck(){delete[] deck;}
        // зачем нужен перемещающий конструктор
        // Нужен для того, чтобы перемещать элементы из rvalue в lvalue
        Deck(const Deck &dc);
        Deck(Deck &&) noexcept;


        Card *getDeck() {
            return deck;
        }


        int getSize() {return top;}
        auto getCardMatrix() {return cardsMatrix;}
        int getMaxSize() {return countMax;}
        void createCardsMatrix(int cnt);
        void deleteDublicateCardsMatrix();
        void changeCardsMatrix(int rang, int suit, int op);
        void push(const Card & = Lab2::Card());
        void push(int nrang, int nsuit);
        Card pop(int index = 0);


        std::ostream &printCardsMatrix(std::ostream &c);

        void mixing();

        int checkRepeated();
        Deck oneSuitDeck(int suit);
        void orderByRang();
        void orderBySuit();
        bool equal(const Deck &other);


        friend std::istream &operator>>(std::istream &, Deck &);
        friend std::ostream &operator<<(std::ostream &, Deck &);
//        std::ostream &operator<<(std::ostream &);
        // объект класса << std::cout

        Deck operator!() const;
        void operator >> (Deck &other);
        // a = b[i] // b - const
        Card &operator[] (int index);
        // a[i] = b
        const Card &operator[] (int index) const;
        // сделать перемещающее присваивание
        Deck &operator=(const Deck &);
        Deck &operator=(Deck &&);
        Deck &operator+=(const Deck &);
        Deck operator+(Deck const &) const;
        bool operator==(Deck &);
        // ссылка на класс
        // 2 версии для каждого
        Deck &operator++();
        Deck operator++(int);
        friend void input(int cnt, Deck &dc);
    };
}

#endif //_DECK_H
