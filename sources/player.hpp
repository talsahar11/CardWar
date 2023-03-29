#ifndef TASK2_PLAYER_H
#define TASK2_PLAYER_H
#include "deck.hpp"
namespace ariel {
    class Player {
    private:
        std::string name;
        Deck *deck;
        Deck *winningStack;
        int numOfWins;
        int numOfTurns;

    public:
        Player(std::string name){}

        int stacksize(){return 0 ;}

        int cardesTaken(){return 0 ;}

        Card *drawCard(){return NULL ;}

        void addCard(Card *c){}

        void addToWinningStack(Card *c){}

        void addToWinningStack(Deck cardsStack){}

        float getWinningRate(){return 0 ;}

        void increaseNumOfWins(){}

        void increaseNumOfTurns(){}

        std::string getName(){return NULL ;}

        Deck *getDeck(){return NULL ;}

        void printStats(){}

    };
}
#endif
