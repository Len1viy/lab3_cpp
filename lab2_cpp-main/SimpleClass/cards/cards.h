//
// Created by vadim on 13.09.2023.
//
#include <iostream>

#ifndef _CARDS_H
#define _CARDS_H

namespace Lab2 {
    class Card {
    private:
        int rang;
        int suit;
    public:
        Card(int nrang, int nsuit);

        explicit Card(void);


        Card &setRang(int nrang);

        Card &setSuit(int nsuit);

        int getRang() const { return rang; };

        int getSuit() const { return suit; };

        std::string formatString() const;

        std::ostream &print(std::ostream &c) const;

        std::strong_ordering operator<=>(const Card &other);
    };


}

#endif
