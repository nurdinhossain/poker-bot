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

    // make sure hands are evaluated as four kinds
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

void testFullHouse()
{
    vector<Card> test1 = {createCard(TWO, CLUBS), createCard(TWO, HEARTS), createCard(TWO, DIAMONDS), createCard(EIGHT, SPADES), createCard(EIGHT, CLUBS)};
    vector<Card> test2 = {createCard(ACE, DIAMONDS), createCard(ACE, HEARTS), createCard(ACE, SPADES), createCard(KING, HEARTS), createCard(KING, DIAMONDS)};
    vector<Card> test3 = {createCard(JACK, SPADES), createCard(JACK, DIAMONDS), createCard(JACK, HEARTS), createCard(FIVE, CLUBS), createCard(FIVE, HEARTS)};
    vector<Card> test4 = {createCard(THREE, HEARTS), createCard(THREE, DIAMONDS), createCard(THREE, CLUBS), createCard(ACE, SPADES), createCard(ACE, HEARTS)};
    vector<Card> test5 = {createCard(TWO, DIAMONDS), createCard(TWO, SPADES), createCard(TWO, CLUBS), createCard(JACK, SPADES), createCard(JACK, HEARTS)};
    int hand1 = bestHand(test1).score;
    int hand2 = bestHand(test2).score;
    int hand3 = bestHand(test3).score;
    int hand4 = bestHand(test4).score;
    int hand5 = bestHand(test5).score;

    // make sure hands are evaluated as full houses
    assert(getStrength(hand1) == FULL_HOUSE);
    assert(getStrength(hand2) == FULL_HOUSE);
    assert(getStrength(hand3) == FULL_HOUSE);
    assert(getStrength(hand4) == FULL_HOUSE);
    assert(getStrength(hand5) == FULL_HOUSE);


    // make sure hands are ranked properly
    assert(hand1 < hand2);
    assert(hand3 < hand2);
    assert(hand3 > hand1);
    assert(hand4 > hand1);
    assert(hand5 > hand1);
    assert(hand4 < hand2);
    assert(hand4 > hand5);

    // print all clear
    cout << "Full house all clear." << endl;
}

void testFlush();
void testStraight();
void testThreeKind();
void testTwoPair();
void testPair();
void testHigh();
void testEverything();