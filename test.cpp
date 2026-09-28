#include "test.h"
#include "poker.h"
#include <cassert>
#include <iostream>

void testStraightFlush()
{
    vector<Card> test1 = {createCard(TWO, CLUBS), createCard(THREE, CLUBS), createCard(FOUR, CLUBS), createCard(FIVE, CLUBS), createCard(SIX, CLUBS)};
    vector<Card> test2 = {createCard(ACE, SPADES), createCard(TWO, SPADES), createCard(THREE, SPADES), createCard(FOUR, SPADES), createCard(FIVE, SPADES)};
    vector<Card> test3 = {createCard(ACE, HEARTS), createCard(KING, HEARTS), createCard(QUEEN, HEARTS), createCard(JACK, HEARTS), createCard(TEN, HEARTS)};
    int hand1 = bestHand(test1).score;
    int hand2 = bestHand(test2).score;
    int hand3 = bestHand(test3).score;

    // make sure hands are evaluated as straight flushes
    assert(getStrength(hand1) == STRAIGHT_FLUSH);
    assert(getStrength(hand2) == STRAIGHT_FLUSH);
    assert(getStrength(hand3) == STRAIGHT_FLUSH);

    // make sure hands are ranked properly
    assert(hand1 > hand2);
    assert(hand3 > hand2);
    assert(hand3 > hand1);

    // print all clear
    cout << "Straight flushes all clear." << endl;
}

void testFourKind()
{
    vector<Card> test1 = {createCard(TWO, CLUBS), createCard(TWO, HEARTS), createCard(TWO, DIAMONDS), createCard(TWO, SPADES), createCard(SIX, CLUBS)};
    vector<Card> test2 = {createCard(TWO, CLUBS), createCard(TWO, HEARTS), createCard(TWO, DIAMONDS), createCard(TWO, SPADES), createCard(SEVEN, CLUBS)};
    vector<Card> test3 = {createCard(ACE, HEARTS), createCard(ACE, DIAMONDS), createCard(ACE, SPADES), createCard(ACE, CLUBS), createCard(TEN, HEARTS)};
    int hand1 = bestHand(test1).score;
    int hand2 = bestHand(test2).score;
    int hand3 = bestHand(test3).score;
    for (Card card : bestHand(test1).hand)
    {
        cout << getValue(card) << endl;
    }
    cout << endl;

    // make sure hands are evaluated as straight flushes
    cout << getStrength(hand1) << endl;
    cout << getStrength(hand2) << endl;
    cout << getStrength(hand3) << endl;
    assert(getStrength(hand1) == FOUR_KIND);
    assert(getStrength(hand2) == FOUR_KIND);
    assert(getStrength(hand3) == FOUR_KIND);

    // make sure hands are ranked properly
    assert(hand1 < hand2);
    assert(hand3 > hand2);
    assert(hand3 > hand1);

    // print all clear
    cout << "Four of a kind all clear." << endl;
}

void testFullHouse();
void testFlush();
void testStraight();
void testThreeKind();
void testTwoPair();
void testPair();
void testHigh();
void testEverything();