#include "doctest.h"
#include "sources/card.hpp"
#include "sources/deck.hpp"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include <iostream>
#include <sstream>
using namespace ariel ;

DOCTEST_TEST_CASE("Card Class Test") {
    //-----Ctors tests-----
    try {
        Card invalid(HEARTS, 15);
    }catch(std::runtime_error& e){
        CHECK_EQ(std::string(e.what()), "Invalid value supplied, value should be in range (2, 14)") ;
    }
    try {
        Card invalid(1, 15);
    }catch(std::runtime_error& e){
        CHECK_EQ(std::string(e.what()), "Invalid value supplied, value should be in range (2, 14)") ;
    }
    try {
        Card invalid(6, 3);
    }catch(std::runtime_error& e){
        CHECK_EQ(std::string(e.what()), "Invalid type supplied, type value should be in range (-1, 3)") ;
    }

    Card card1(1, 14);
    Card card2(HEARTS, 2);
    Card card3(CLUBS, 11);
    Card card4(SPADES, 12);
    Card card5(CLUBS, 13);
    Card card6(DIAMONDS, 2) ;

    CHECK(card1.getType() == DIAMONDS) ;
    CHECK(card1.getValue() == 14) ;
    CHECK(card2.getType() == HEARTS) ;
    CHECK(card2.getValue() == 2) ;

    //-----Compare method tests-----
    int res = -1 ;
    res = card1.compare(card2) ;
    CHECK(res == 1) ;
    res = card2.compare(card3) ;
    CHECK(res == -1) ;
    res = card3.compare(card4) ;
    CHECK(res == -1) ;
    res = card5.compare(card4) ;
    CHECK(res == 1) ;
    res = card5.compare(card1) ;
    CHECK(res == -1) ;
    res = card2.compare(card6) ;
    CHECK(res == 0) ;
    //-----ToString method tests-----

    CHECK_EQ(card1.toString(), "Ace of Diamonds") ;
    CHECK_EQ(card2.toString(), "2 of Hearts") ;
    CHECK_EQ(card3.toString(), "Jack of Clubs") ;
    CHECK_EQ(card4.toString(), "Queen of Spades") ;
    CHECK_EQ(card5.toString(), "King of Clubs") ;

    //-----Getters tests-----
    CHECK(card3.getType() == CLUBS) ;
    CHECK(card4.getType() == SPADES) ;
    CHECK(card3.getValue() == 11) ;
    CHECK(card4.getValue() == 12) ;
}

DOCTEST_TEST_CASE("Deck class test"){
    Deck playersDeck(PLAYER_DECK);
    Deck gameDeck(GAME_DECK) ;
    Deck cardsStack(CARDS_STACK) ;

    //-----Ctors tests-----
    CHECK(playersDeck.getSize() == 0) ;
    CHECK(gameDeck.getSize() == 52) ;
    CHECK(cardsStack.getSize() == 0) ;

    //-----Deck holds all cards test-----
    bool uniqueCardArr[4][13] ;
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 13 ; j++){
            uniqueCardArr[i][j] = false ;
        }
    }
    Card* currentCard ;
    int typeNum ;
    int modifiedValue ;
    for(int i = 0 ; i < 52 ; i++){
        currentCard = gameDeck.drawCard() ;
        typeNum = static_cast<int>(currentCard->getType());
        modifiedValue = currentCard->getValue()-2 ;
        CHECK(uniqueCardArr[typeNum][modifiedValue] == false) ;
        uniqueCardArr[typeNum][modifiedValue] = true ;
    }
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 13 ; j++){
            CHECK(uniqueCardArr[i][j]) ;
        }
    }
    CHECK(gameDeck.getSize() == 0) ;

    //-----addCard method test-----
    Card card(1, 13) ;
    CHECK(cardsStack.getSize() == 0) ;
    cardsStack.addCard(&card) ;
    CHECK(cardsStack.getSize() == 1) ;

    //-----drawCard method test-----
    Card* cardP = cardsStack.drawCard() ;
    CHECK(cardP->getValue() == 13) ;
    CHECK(cardP->getType() == DIAMONDS) ;
    cardP = cardsStack.drawCard() ;
    CHECK(cardP == NULL) ;

    //-----toString method test-----
    Card c1(0,14) ;
    Card c2(1,2) ;
    Card c3(2,3) ;
    cardsStack.addCard(&c1) ;
    cardsStack.addCard(&c2) ;
    cardsStack.addCard(&c3) ;
    CHECK_EQ(cardsStack.toString(), c1.toString() + "\n" + c2.toString() + "\n" + c3.toString() +"\n") ;
}

DOCTEST_TEST_CASE("Player class test"){
    Player p1("Yoram") ;
    Player p2("Matilda") ;
    Card c1(1, 14);
    Card c2(HEARTS, 2);
    Card c3(CLUBS, 11);
    Card c4(SPADES, 12);
    Card c5(CLUBS, 13);
    Card c6(DIAMONDS, 2) ;

    //-----addCard, drawCard and stacksize methods tests-----
    CHECK(p1.stacksize() == 0) ;
    p1.addCard(&c1) ;
    p1.addCard(&c2) ;
    CHECK(p1.stacksize() == 2) ;
    CHECK(p1.drawCard()->getValue() == 2) ;
    CHECK(p1.drawCard()->getValue() == 14) ;
    CHECK(p1.drawCard() == NULL) ;
    CHECK(p1.stacksize() == 0) ;

    //-----getName method tests-----
    CHECK_EQ(p1.getName(), "Yoram") ;
    CHECK_EQ(p2.getName(), "Matilda") ;

    //----addToWinningStack and cardsTaken methods tests------
    p1.addToWinningStack(&c3) ;
    p1.addToWinningStack(&c4) ;
    p1.addToWinningStack(&c5) ;
    p1.addToWinningStack(&c6) ;
    Deck winningStack(CARDS_STACK) ;
    winningStack.addCard(&c3) ;
    winningStack.addCard(&c4) ;
    winningStack.addCard(&c5) ;
    winningStack.addCard(&c6) ;

    CHECK(p1.cardesTaken() == 4) ;
    p2.addToWinningStack(winningStack) ;

    CHECK(p2.cardesTaken() == 4) ;

    //-----increaseNumOfWins, increaseNumOfTurns and printStats methods tests-----
    p1.increaseNumOfWins() ;
    p1.increaseNumOfWins() ;
    p1.increaseNumOfWins() ;
    p1.increaseNumOfTurns() ;
    p1.increaseNumOfTurns() ;
    p1.increaseNumOfTurns() ;
    p1.increaseNumOfTurns() ;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    p1.printStats();
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    CHECK(output == "Winning Rate: 0.75, Cards won: 4, Have 0 more cards to play.\n");
}

DOCTEST_TEST_CASE("Game class test"){
    Player p1("Yoram") ;
    Player p2("Matilda") ;

    Game game(p1, p2) ;

    //-----Test the game stats printing-----
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    game.printStats() ;
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    CHECK_EQ(output, "Game Statistics:\n"+p1.getName()+" - Winning Rate: 0, Cards won: 0, Have 26 more cards to play.\n"
                     +p2.getName()+" - Winning Rate: 0, Cards won: 0, Have 26 more cards to play.\n"
                     +"General - Turns played: 0, Draw rate: 0, Amount of draws: 0.\n") ;

    //-----Test the printWiner method when the game is not over yet-----
    buffer.str("") ;
    std::cout.rdbuf(buffer.rdbuf());
    game.printWiner() ;
    std::cout.rdbuf(old);
    output = buffer.str() ;
    CHECK_EQ(output, "The game has not over yet, there is no winner at this moment.\n") ;

    //-----Test the gameOver method output-----
    buffer.str("") ;
    std::cout.rdbuf(buffer.rdbuf());
    game.playAll() ;
    std::cout.rdbuf(old);
    output = buffer.str() ;
    CHECK_EQ(output, "The game is over.\n") ;

    //-----Test the printWiner method output when the game has over-----
    buffer.str("") ;
    std::cout.rdbuf(buffer.rdbuf());
    game.printWiner() ;
    std::cout.rdbuf(old);
    output = buffer.str() ;
    CHECK_NE(output, "The game has not over yet, there is no winner at this moment.") ;
}

DOCTEST_TEST_CASE("Full Draw test"){
    //-----Create a balanced deck that will create draw on each turn-----
    Deck deck(CARDS_STACK) ;
    Card* card ;
    for(int j = 2 ; j < 15 ; j++){
        for(int i = 0 ; i < 4 ; i++){
            card = new Card(i, j) ;
            deck.addCard(card) ;
        }
    }

    //-----Initiate the game-----
    Player p1("Yoram") ;
    Player p2("Matilda") ;
    Game game(p1, p2, deck) ;
    game.playAll() ;

    //-----Check if there is a winner (There shouldn't be)-----
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    game.printWiner() ;
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    CHECK_EQ(output, "There is no winner, its a draw.\n") ;

    //-----Check if both of player was divided the cards between them-----
    CHECK(p1.cardesTaken() == 26) ;
    CHECK(p2.cardesTaken() == 26) ;
}

DOCTEST_TEST_CASE("Player 1 full win scenario"){
    //-----Create a balanced deck that will create draw on each turn-----
    Deck deck(CARDS_STACK) ;
    Card* card ;

    for(int i = 2 ; i < 8 ; i++){
        for(int j = 0 ; j < 4 ; j++) {
            card = new Card(j,i) ;
            deck.addCard(card) ;
            if((j+2)%4 >1) {
                card = new Card((j + 2) % 4, i + 6);
            }else{
                card = new Card((j + 2) % 4, i + 7);
            }
            deck.addCard(card) ;
        }
    }
    for(int i = 0 ; i < 2 ; i++){
        card = new Card(i, 8) ;
        deck.addCard(card) ;
        card = new Card(i+2, 14) ;
        deck.addCard(card) ;
    }
    //-----Initiate the game-----
    Player p1("Yoram") ;
    Player p2("Matilda") ;
    Game game(p1, p2, deck) ;
    game.playAll() ;
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    game.printStats() ;
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    CHECK_EQ(output, "Game Statistics:\n"
                     "Yoram - Winning Rate: 1, Cards won: 52, Have 0 more cards to play.\n"
                     "Matilda - Winning Rate: 0, Cards won: 0, Have 0 more cards to play.\n"
                     "General - Turns played: 26, Draw rate: 0, Amount of draws: 0.\n") ;
}