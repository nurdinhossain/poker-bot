#pragma once
#include "card.h"

struct ScoredHand 
{
    vector<Card> hand;
    int score;
};

// scoring enum
enum Strength
{
    HIGH,
    PAIR,
    TWO_PAIR,
    THREE_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_KIND,
    STRAIGHT_FLUSH
};

const int KICKER_SHIFT = 4;
const int HAND_SIZE = 5;

int score(vector<Card> cards, Strength strength);
ScoredHand bestHand(vector<Card> cards);
Strength getStrength(int score);