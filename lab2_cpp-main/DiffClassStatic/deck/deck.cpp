//
// Created by vadim on 17.09.2023.
//

#include "deck.h"

// Добавление и удаление карт также можно реализовать через сдвиг (head - удаление, tail - добавление)
namespace Lab2 {
    Deck::Deck(int cnt) {
        if (cnt > 52 && cnt <= 100) {
            int rang, suit;
            top = cnt;
            createCardsMatrix(0);

            deleteDublicateCardsMatrix();


            for (int i = 52; i < cnt; i++) {
                rang = rand() % 13 + 2;
                suit = rand() % 4 + 1;
                deck[i].setRang(rang);
                deck[i].setSuit(suit);
                changeCardsMatrix(rang, suit, 1);
            }
        } else if (cnt < 0 || cnt > 100) throw std::invalid_argument("Error with count of cards in the deck");
        else {
            top = cnt;
            createCardsMatrix(0);
            deleteDublicateCardsMatrix();
        }

    }

    Deck::Deck(void) {
        top = 52;
        createCardsMatrix(1);
        for (int i = 2; i < 15; i++) {
            for (int j = 1; j < 5; j++) {

                deck[(i - 2) * 4 + (j - 1)].setRang(i);
                deck[(i - 2) * 4 + (j - 1)].setSuit(j);
            }
        }
    }

    bool Deck::equal(const Deck &other) {
        if (top == other.top) {
            for (int i = 0; i < top; i++) {
                if ((deck[i] <=> other.deck[i]) != std::strong_ordering::equal) return false;
            }
        } else return false;
        return true;
    }

    void Deck::createCardsMatrix(int cnt) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                cardsMatrix[i][j] = cnt;
            }
        }
    }

    std::ostream &Deck::printCardsMatrix(std::ostream &c) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                c << cardsMatrix[i][j] << " ";
            }
            c << std::endl;
        }
        return c;
    }

    std::ostream &Deck::printDeck(std::ostream &c) {
        if (top == 0) return c << "Stack is empty!" << std::endl;
        for (int i = top - 1; i >= 0; i--) {
            deck[i].print(c);
        }
        return c << std::endl << "----------------------------------" << std::endl;
    }

    void Deck::operator>>(Deck &other) {
        if (other.top == other.countMax) throw std::runtime_error("Deck overflow!");
        if (top == 0) throw std::runtime_error("Deck is empty!");
        other.changeCardsMatrix(deck[top - 1].getRang(), deck[top - 1].getSuit(), 1);
        changeCardsMatrix(deck[top - 1].getRang(), deck[top - 1].getSuit(), -1);
        other.deck[other.top++] = deck[--top];
    }


    void Deck::deleteDublicateCardsMatrix() {

        for (int i = 0; i < top; i++) {
            while (cardsMatrix[deck[i].getSuit() - 1][deck[i].getRang() - 2] == 1 && i < 52) {
                deck[i].setSuit(rand() % 4 + 1);
                deck[i].setRang(rand() % 13 + 2);
            }

            cardsMatrix[deck[i].getSuit() - 1][deck[i].getRang() - 2] += 1;
        }
    }

    void Deck::changeCardsMatrix(int rang, int suit, int op) {
        cardsMatrix[suit - 1][rang - 2] += 1 * op;
    }

    int Deck::checkRepeated() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                if (cardsMatrix[i][j] >= 2) return 1;
            }
        }
        return 0;
    }

    void Deck::mixing() {
        for (int i = top - 1; i >= 1; i--) {
            int j = rand() % (i + 1);
            Card tmp = deck[j];
            deck[j] = deck[i];
            deck[i] = tmp;
        }
    }

    Card &Deck::operator[](int index) {
        return deck[top - index - 1];
    }

    void Deck::push(const Card &card) {
        if (top == countMax) throw std::runtime_error("Deck overflow!");
        deck[top++] = card;
        changeCardsMatrix(card.getRang(), card.getSuit(), 1);
    }

    void Deck::push(int nrang, int nsuit) {
        if (top == countMax) throw std::runtime_error("Deck overflow!");
        Card card(nrang, nsuit);
        deck[top++] = card;
        changeCardsMatrix(nrang, nsuit , 1);
    }

    Card Deck::pop(int index) {
        if (top == 0) throw std::runtime_error("Deck is empty!");
        if (index >= top || index < 0) throw std::invalid_argument("Wrong index!");

        changeCardsMatrix(deck[index].getRang(), deck[index].getSuit(), -1);
        Card tmp = deck[top - index - 1];

        for (int i = top - index; i < top; i++) {
            deck[i-1] = deck[i];
        }
        deck[--top] = tmp;
        return deck[top];
    }

    Deck Deck::operator+(Deck const &dc) const {
        Lab2::Deck newDeck;
        newDeck.top = top + dc.top;
        if (newDeck.top > countMax) throw std::runtime_error("Deck is overflow");
        for (int i = 0; i < newDeck.top; i++) {
            if (i < top) {
                newDeck.deck[i].setRang(deck[i].getRang());
                newDeck.deck[i].setSuit(deck[i].getSuit());
            } else {
                newDeck.deck[i].setRang(dc.deck[i - top].getRang());
                newDeck.deck[i].setSuit(dc.deck[i - top].getSuit());
            }
            newDeck.changeCardsMatrix(newDeck.deck[i].getRang(), newDeck.deck[i].getSuit(), 1);
        }
        return newDeck;
    }

    Deck Deck::oneSuitDeck(int suit) const {
        if (suit < 1 || suit > 4) throw std::invalid_argument("Error with suit!");
        Deck newDeck(0);
        Card card;
        card.setSuit(suit);
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < cardsMatrix[suit - 1][i]; j++) {
                card.setRang(i + 2);
                newDeck.push(card);
            }
        }
        return newDeck;
    }

    void Deck::orderByRang() {
        top = 0;
        int cnt;
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 4; j++) {
                cnt = cardsMatrix[j][i];
                for (int c = 0; c < cnt; c++) {
                    push(i + 2, j + 1);
                }
                cardsMatrix[j][i] = cnt;
            }
        }
    }

    void Deck::orderBySuit() {
        top = 0;
        int cnt;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                cnt = cardsMatrix[i][j];
                for (int c = 0; c < cnt; c++) {
                    push(j + 2, i + 1);
                }
                cardsMatrix[i][j] = cnt;
            }
        }
    }
    bool Deck::operator==(Deck &other) {
        if (top == other.top) {
            for (int i = 0; i < 13; i++) {
                for (int j = 0; j < 4; j++) {
                    if (cardsMatrix[j][i] != other.cardsMatrix[j][i]) return false;
                }
            }
        }
        return true;
    }
}

