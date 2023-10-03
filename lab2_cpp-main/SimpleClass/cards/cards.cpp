#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include "cards.h"

// 1 - ♦
// 2 - ♥
// 3 - ♣
// 4 - ♠

namespace Lab2 {
    Card::Card(int nrang, int nsuit) {
        if (nrang > 14 || nrang < 2) throw std::invalid_argument("Error with rang");
        rang = nrang;
        if (nsuit > 4 || nsuit < 1) throw std::invalid_argument("Error with suit");
        suit = nsuit;
    }

    Card::Card(void) {
        rang = rand() % 13 + 2;
        suit = rand() % 4 + 1;
    }


    Card &Card::setRang(int nrang) {
        if (nrang > 14 || nrang < 2) throw std::invalid_argument("Error with rang");
        rang = nrang;
        return *this;
    }

    Card &Card::setSuit(int nsuit) {
        if (nsuit > 4 || nsuit < 1) throw std::invalid_argument("Error with suit");
        suit = nsuit;
        return *this;
    }

    std::string Card::formatString() const {
        std::string result = "";
        if (rang <= 10) result += std::to_string(rang);
        else if (rang == 11) result += "J";
        else if (rang == 12) result += "Q";
        else if (rang == 13) result += "K";
        else if (rang == 14) result += "A";
        if (suit == 1) result += "\u2666"; // ♦
        else if (suit == 2) result += "\u2665"; // ♥
        else if (suit == 3) result += "\u2663"; // ♣
        else if (suit == 4) result += "\u2660"; // ♠
        return result;
    }

    std::ostream &Card::print(std::ostream &c) const {
        return c << formatString() << " ";
    }



    std::strong_ordering Card::operator<=>(const Card &other) {
        if (suit != other.getSuit()) throw std::invalid_argument("Different suits!");
        return rang <=> other.rang;
    }

}