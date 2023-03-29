#ifndef DECK_H
#define DECK_H
#include "card.hpp"

namespace ariel {
    enum DeckType {
        PLAYER_DECK = 0,
        GAME_DECK = 1,
        CARDS_STACK = 2
    };
    class Deck {
    private:
        Card **cards;
        int totalSize;
        int actualSize;
        Card** generateGameDeck() {return NULL ;}
        Card** shuffleDeck(Card **deck) {return NULL ;}
    public:
        Deck() {}
        Deck(DeckType deckType){}

        Card *drawCard(){return NULL ;}

        void addCard(Card *c){}

        int getSize(){return 0 ;}

        std::string toString(){return "" ;}
    };
}
#endif //DECK_H