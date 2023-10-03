//
// Created by vadim on 17.09.2023.
//

// Написать копирующий и перемещающий конструкторы

#include "deck.h"

namespace Lab2 {
    Deck::Deck(int cnt) {
        if (cnt < 0) throw std::invalid_argument("Error with count of cards in the deck");
        countMax = cnt + reserveSize;
        top = cnt;

        if (cnt > 52) {
            int rang, suit;
            deck = new Card[countMax];
            createCardsMatrix(0);
            deleteDublicateCardsMatrix();
            for (int i = 52; i < cnt; i++) {
                rang = rand() % 13 + 2;
                suit = rand() % 4 + 1;
                deck[i].setRang(rang);
                deck[i].setSuit(suit);
                changeCardsMatrix(rang, suit, 1);
            }
        } else {
            deck = new Card[countMax];
            createCardsMatrix(0);
            deleteDublicateCardsMatrix();
        }

    }

    Deck::Deck(void) {
        countMax = 52 + reserveSize;
        deck = new Card[countMax];
        top = 52;
        createCardsMatrix(1);
        for (int i = 2; i < 15; i++) {
            for (int j = 1; j < 5; j++) {
                deck[(i - 2) * 4 + (j - 1)].setRang(i);
                deck[(i - 2) * 4 + (j - 1)].setSuit(j);
            }
        }
    }

    // копирующий конструктор
    Deck::Deck(const Deck &dc) : countMax(dc.countMax), top(dc.top) {
        deck = new Card[countMax];
        std::copy(dc.deck, dc.deck + dc.top, deck);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                cardsMatrix[i][j] = dc.cardsMatrix[i][j];
            }
        }
    }

    // перемещающий конструктор
    Deck::Deck(Deck &&dc) noexcept: countMax(dc.countMax), top(dc.top), deck(dc.deck) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                cardsMatrix[i][j] = dc.cardsMatrix[i][j];
            }
        }
        dc.top = 0;
        dc.deck = nullptr;
    }

    // копирующий оператор присваивания
    Deck &Deck::operator=(const Lab2::Deck &dc) {
        if (this != &dc) {
            top = dc.top;
            countMax = dc.countMax;
            Card *new_arr = new Card[countMax];
            delete[] deck;
            deck = new_arr;
            std::copy(dc.deck, dc.deck + top, deck);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 13; j++) {
                    cardsMatrix[i][j] = dc.cardsMatrix[i][j];
                }
            }
        }
        return *this;
    }
    // можно сделать через swap
    Deck &Deck::operator=(Deck &&dc) {
        if (this != &dc) {
            countMax = dc.countMax;
            top = dc.top;
            delete [] deck;
            deck = dc.getDeck();
            dc.deck = nullptr;
            dc.countMax = 0;
            dc.top = 0;
        }
        return *this;
    }

    Deck &Deck::setTop(int tp) {
        if (tp >= 0) top = tp;
        return *this;
    }

    void Deck::resize(int new_size) {
        if (new_size < top) throw std::runtime_error("New size is too small!");
        Card *new_deck = new Card[new_size];
        std::move(deck, deck + top, new_deck);
        delete[] deck;
        countMax = new_size;
        deck = new_deck;
    }

    void Deck::createCardsMatrix(int count) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                cardsMatrix[i][j] = count;
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


    void Deck::operator>>(Deck &other) {
        if (other.getSize() == other.getMaxSize()) other.resize(other.getMaxSize() + reserveSize);
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
    // a  = b[i] - b-const не хватит

    Card &Deck::operator[](int index) {
        return deck[top - index - 1];
    }
    // a[i] = b - не хватит, тк const неизменно
    const Card &Deck::operator[](int index) const {
        return deck[top - index - 1];
    }

    void Deck::push(const Card &card) {
        if (top == countMax) resize(countMax + reserveSize);
        deck[top++] = card;
        changeCardsMatrix(card.getRang(), card.getSuit(), 1);
    }

    void Deck::push(int nrang, int nsuit) {
        if (top == countMax) resize(countMax + reserveSize);
        Card card(nrang, nsuit);
        deck[top++] = card;
        changeCardsMatrix(nrang, nsuit, 1);
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

    Deck &Deck::operator+=(Deck const &dc) {
        int new_top = top + dc.top;
        if (new_top > countMax) resize(new_top + reserveSize);
        for (int i = top; i < new_top; i++) {
            deck[i].setRang(dc.deck[i - top].getRang());
            deck[i].setSuit(dc.deck[i - top].getSuit());
            changeCardsMatrix(deck[i].getRang(), deck[i].getSuit(), 1);
        }
        top = new_top;
        return *this;
    }
// переделать оператор сложения
    Deck Deck::operator+(Deck const &dc) const {
        Lab2::Deck newDeck;
        newDeck.top = top + dc.top;
        if (newDeck.top > countMax) newDeck.resize(newDeck.top + reserveSize);
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

    Deck Deck::oneSuitDeck(int suit) {
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
                    if (cardsMatrix[j][i] != other.cardsMatrix[j][i]) {;
                        return false;
                    }
                }
            }
        } else return false;
        return true;
    }

    bool Deck::equal(const Deck &other) {
        if (top == other.top) {
            for (int i = 0; i < top; i++) {
                if ((deck[i] <=> other.deck[i]) != std::strong_ordering::equal) return false;
            }
        } else return false;
        return true;
    }

    Deck &Deck::operator++() {
        push();
        return *this;
    }

    Deck Deck::operator++(int) {
        Deck newDeck = *this;
        push();
        return newDeck;
    }

    std::ostream &operator<<(std::ostream &c, Deck &dc) {
        for (int i = 0; i < dc.getSize(); i++) {
            c << dc[i].formatString() << " ";
        }
        return c << std::endl;
    }

    std::istream &operator>>(std::istream &c, Deck &dc) {
        int rang, suit;
        c >> rang >> suit;
        dc.push(rang, suit);
        return c;
    }

    void input(int cnt, Deck &dc) {
        dc.setTop(0);
        for (int i = 0; i < cnt; i++) {
            std::cout << "Input (rang suit) [" << i << "]. 2 <= rang <= 13; 1 <= suit <= 4: >> ";
            std::cin >> dc;
        }
    }

    Deck Deck::operator!() const {
        for (int i = 0; i < top; i++) {
            if (deck[i].getSuit() == 1) {
                deck[i].setSuit(2);
            } else if (deck[i].getSuit() == 2) {
                deck[i].setSuit(1);
            } else if (deck[i].getSuit() == 3) {
                deck[i].setSuit(4);
            } else if (deck[i].getSuit() == 4) {
                deck[i].setSuit(3);
            }
        }
        return *this;
    }
}

