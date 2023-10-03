#define CATCH_CONFIG_MAIN

#include "../../catch.hpp"
#include "../deck/deck.cpp"
#include "../../SimpleClass/cards/cards.cpp"


TEST_CASE("DeckStaticConstructor") {
    SECTION("DefaultConstructor") {
        Lab2::Deck deck;
        REQUIRE(deck.getSize() == 52);
        REQUIRE(deck.checkRepeated() == 0);
    }
    SECTION("InitConstructor") {
        Lab2::Deck deck(15);
        REQUIRE(deck.getSize() == 15);
        REQUIRE(deck.checkRepeated() == 0);
        Lab2::Deck deck1(60);
        REQUIRE(deck1.getSize() == 60);
        REQUIRE(deck1.checkRepeated() == 1);
        Lab2::Deck deck2(100);
        REQUIRE_THROWS(deck2.push(10, 3));
    }
}

TEST_CASE("DeckStaticOperators") {
    SECTION("IND >>") {
        Lab2::Deck dc1(10);
        Lab2::Deck dc2(10);
        Lab2::Card card(dc1[0].getRang(), dc1[0].getSuit());
        dc1 >> dc2;
        REQUIRE(dc2.getSize() == 11);
        REQUIRE((dc2[0] <=> card) == std::strong_ordering::equal);
        Lab2::Card card1(dc1[0].getRang(), dc1[0].getSuit());
        for (int i = 0; i < 9; i++) {
            dc2.push(5, 4);
        }
        dc1 >> dc2;
        REQUIRE((dc2[0] <=> card1) == std::strong_ordering::equal);
        Lab2::Deck dc3(0);
        REQUIRE_THROWS(dc3 >> dc2);
    } SECTION("+") {
        Lab2::Deck dc(10);
        Lab2::Deck dc1(13);
        REQUIRE(dc.equal(dc1) == false);
        Lab2::Deck dc2 = dc + dc1;
        REQUIRE(dc2.getSize() == 23);
        for (int i = 0; i < dc2.getSize(); i++) {
            if (i < dc1.getSize()) {
                REQUIRE((dc2[i] <=> dc1[i]) == std::strong_ordering::equal);
            } else {
                REQUIRE((dc2[i] <=> dc[i - dc1.getSize()]) == std::strong_ordering::equal);
            }
        }
    }
}


TEST_CASE("DeckStaticMethods", "Setters") {
    SECTION("Setters") {
        Lab2::Deck deck(50);
        Lab2::Card card(11, 2);
        deck[10].setRang(10);
        deck[10].setSuit(2);
        REQUIRE(deck[10].getSuit() == 2);
        REQUIRE(deck[10].getRang() == 10);
        for (int i = 0; i < 11; i++) {
            deck.push(5, 4);
        }
        REQUIRE(deck.getDeck()[deck.getSize() - 1].getRang() == 5);
        REQUIRE(deck.getDeck()[deck.getSize() - 1].getSuit() == 4);
        deck[40] = card;
        REQUIRE(deck[40].getRang() == 11);
        REQUIRE(deck[40].getSuit() == 2);
    }
    SECTION("MIXING") {
        Lab2::Deck dc;
        Lab2::Deck dc1;
        REQUIRE(dc.equal(dc1) == true);
        dc1.mixing();
        REQUIRE_THROWS(dc.equal(dc1) == false);
    }SECTION("ORDER") {
        Lab2::Deck dc(10);
        dc.orderByRang();
        for (int i = 0; i < dc.getSize() - 1; i++) {
            REQUIRE((dc[i + 1].getRang() <= dc[i].getRang()) == true);
        }
        Lab2::Deck dc1(25);
        dc1.orderBySuit();
        for (int i = 0; i < dc1.getSize() - 1; i++) {
            REQUIRE((dc1[i + 1].getSuit() <= dc1[i].getSuit()) == true);
        }
    } SECTION("ONESUIT") {
        Lab2::Deck dc(30);
        Lab2::Deck dc1 = dc.oneSuitDeck(2);
        for (int i = 0; i < dc1.getSize(); i++) {
            REQUIRE(dc1[i].getSuit() == 2);
        }
        REQUIRE_THROWS(dc.oneSuitDeck(5));
        REQUIRE_THROWS(dc.oneSuitDeck(-1));
    } SECTION("POP") {
        Lab2::Deck dc(10);
        dc[4].setRang(10);
        dc[4].setSuit(2);
        dc[5].setRang(11);
        dc[5].setSuit(2);
        Lab2::Deck dc1(dc);
        Lab2::Card card(10, 2);
        Lab2::Card card1 = dc.pop(4);
        REQUIRE((card <=> card1) == std::strong_ordering::equal);
        REQUIRE(dc.getSize() == dc1.getSize() - 1);
        REQUIRE((dc1[4] <=> dc[4]) != std::strong_ordering::equal);
        REQUIRE(dc1[5] <=> dc[4] == std::strong_ordering::equal);
        Lab2::Deck throw1(0);
        REQUIRE_THROWS(throw1.pop(0));
        Lab2::Deck throw2(1);
        REQUIRE_THROWS(throw2.pop(10));
        REQUIRE_THROWS(throw2.pop(-10));
        REQUIRE_THROWS(throw2.pop(1));
    }
}