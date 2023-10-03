#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../cards/cards.cpp"


TEST_CASE("CardConstructor") {
    SECTION("DefaultConstructor") {
        Lab2::Card card;
        REQUIRE(2 <=  card.getRang());
        REQUIRE(1 <= card.getSuit());
        REQUIRE(13 >= card.getRang());
        REQUIRE(4 >= card.getSuit());
    }
    SECTION("InitConstructor") {
        Lab2::Card card(13, 2);
        REQUIRE(card.getRang() == 13);
        REQUIRE(card.getSuit() == 2);
    }
    SECTION("TestExseptions") {
        Lab2::Card card;
        REQUIRE_THROWS(card.setSuit(-2));
        REQUIRE_THROWS(card.setSuit(5));
        REQUIRE_THROWS(card.setRang(15));
        REQUIRE_THROWS(card.setRang(-5));
    }
}

TEST_CASE("CardMethods", "Setters") {
    SECTION("Setters") {
        Lab2::Card card;
        card.setRang(12);
        card.setSuit(1);
        REQUIRE(card.getRang() == 12);
        REQUIRE(card.getSuit() == 1);
        card.setRang(10);
        card.setSuit(2);
        REQUIRE(card.getRang() == 10);
        REQUIRE(card.getSuit() == 2);
        REQUIRE_THROWS(card.setRang(15));
        REQUIRE_THROWS(card.setSuit(-15));
    }
    SECTION("FORMAT_STRING") {
        Lab2::Card card;
        card.setSuit(2);
        card.setRang(10);
        REQUIRE(card.getRang() == 10);
        REQUIRE(card.getSuit() == 2);
        REQUIRE(card.formatString() == "10♥");
        card.setSuit(1);
        card.setRang(11);
        REQUIRE(card.formatString() == "J♦");
        card.setSuit(3);
        card.setRang(12);
        REQUIRE(card.formatString() == "Q♣");
        card.setSuit(4);
        card.setRang(13);
        REQUIRE(card.formatString() == "K♠");
        card.setSuit(4);
        card.setRang(14);
        REQUIRE(card.formatString() == "A♠");
    } SECTION("SPACESHIP") {
        Lab2::Card card;
        card.setSuit(2);
        card.setRang(10);
        Lab2::Card card1(4, 2);
        REQUIRE(card1.getRang() == 4);
        REQUIRE(card1.getSuit() == 2);
        Lab2::Card card2(10, 3);
        REQUIRE(card <=> card1 == std::strong_ordering::greater);
        REQUIRE(card1 <=> card == std::strong_ordering::less);
        REQUIRE_THROWS(card2 <=> card);
    }
}