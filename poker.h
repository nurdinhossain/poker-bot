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

vector<Card> bestStraightFlush(vector<vector<Card>> buckets);
vector<Card> bestFlush(vector<vector<Card>> buckets);
vector<Card> bestStraight(vector<vector<Card>> buckets);
vector<Card> fourOfAKind(vector<vector<Card>> buckets);
vector<Card> bestFullHouse(vector<vector<Card>> buckets);
vector<Card> bestThreeOfAKind(vector<vector<Card>> buckets);
vector<Card> bestTwoPair(vector<vector<Card>> buckets);
vector<Card> bestPair(vector<vector<Card>> buckets);
ScoredHand bestHand(vector<Card> cards);
Strength getStrength(int score);