#ifndef CARD_H
#define CARD_H
#include <string>
namespace ariel {
    enum Type {
        HEARTS = 0,
        DIAMONDS = 1,
        SPADES = 2,
        CLUBS = 3,
        NONE = -1
    };

    class Card {
    private:
        Type type;
        int value;
    public:
        Card(){};

        Card(Type type, int value){}

        Card(int type, int value){}

        Type getType(){return NONE ;}

        int getValue(){return 0 ;}

        int compare(Card c){return 0 ;}

        std::string toString(){return "" ;}
    };


}
#endif //CARD_H
