#pragma once 
#include "card.h"

class Hand
{   
    public:
        // constructor
        Hand(int money, int la, int ba);
        ~Hand();
        
        // operations
        int viewBalance();
        void addBalance(int money);
        void removeBalance(int money);
        void clearHand();
        void addHand(Card card);

        void toggleLittle();
        void toggleBig();
        void toggleNormal();
        void updatePrevRaise(int raise);

    private:
        vector<Card> hand;
        int balance;
        bool isLittle;
        bool isBig;

        int littleAmount;
        int bigAmount;
        int prevRaise;
};  