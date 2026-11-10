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

void testFlush()
{
    vector<Card> test1 = {createCard(ACE, CLUBS), createCard(TWO, CLUBS), createCard(EIGHT, CLUBS), createCard(NINE, CLUBS), createCard(TEN, CLUBS)};
    vector<Card> test2 = {createCard(JACK, DIAMONDS), createCard(EIGHT, DIAMONDS), createCard(ACE, DIAMONDS), createCard(KING, DIAMONDS), createCard(FIVE, DIAMONDS)};
    vector<Card> test3 = {createCard(KING, SPADES), createCard(JACK, SPADES), createCard(QUEEN, SPADES), createCard(TWO, SPADES), createCard(ACE, SPADES)};
    vector<Card> test4 = {createCard(EIGHT, HEARTS), createCard(SEVEN, HEARTS), createCard(NINE, HEARTS), createCard(FOUR, HEARTS), createCard(FIVE, HEARTS)};
    vector<Card> test5 = {createCard(TWO, DIAMONDS), createCard(THREE, DIAMONDS), createCard(SEVEN, DIAMONDS), createCard(TEN, DIAMONDS), createCard(JACK, DIAMONDS)};
    int hand1 = bestHand(test1).score;
    int hand2 = bestHand(test2).score;
    int hand3 = bestHand(test3).score;
    int hand4 = bestHand(test4).score;
    int hand5 = bestHand(test5).score;

    // make sure hands are evaluated as flushes
    assert(getStrength(hand1) == FLUSH);
    assert(getStrength(hand2) == FLUSH);
    assert(getStrength(hand3) == FLUSH);
    assert(getStrength(hand4) == FLUSH);
    assert(getStrength(hand5) == FLUSH);


    // make sure hands are ranked properly
    assert(hand2 > hand1);
    assert(hand3 > hand2);
    assert(hand3 > hand1);
    assert(hand4 < hand1);
    assert(hand5 < hand1);
    assert(hand4 < hand2);
    assert(hand4 < hand5);

    // print all clear
    cout << "Flush all clear." << endl;
}

void testStraight()
{
    vector<Card> test1 = {createCard(ACE, CLUBS), createCard(TWO, DIAMONDS), createCard(THREE, CLUBS), createCard(FOUR, CLUBS), createCard(FIVE, CLUBS)};
    vector<Card> test2 = {createCard(TEN, DIAMONDS), createCard(JACK, SPADES), createCard(QUEEN, DIAMONDS), createCard(KING, DIAMONDS), createCard(ACE, DIAMONDS)};
    vector<Card> test3 = {createCard(SEVEN, SPADES), createCard(EIGHT, CLUBS), createCard(NINE, SPADES), createCard(TEN, SPADES), createCard(JACK, SPADES)};
    vector<Card> test4 = {createCard(TWO, HEARTS), createCard(THREE, HEARTS), createCard(FOUR, HEARTS), createCard(FIVE, CLUBS), createCard(SIX, DIAMONDS)};
    vector<Card> test5 = {createCard(FIVE, HEARTS), createCard(SIX, DIAMONDS), createCard(SEVEN, DIAMONDS), createCard(EIGHT, DIAMONDS), createCard(NINE, DIAMONDS)};
    int hand1 = bestHand(test1).score;
    int hand2 = bestHand(test2).score;
    int hand3 = bestHand(test3).score;
    int hand4 = bestHand(test4).score;
    int hand5 = bestHand(test5).score;

    // make sure hands are evaluated as straights
    assert(getStrength(hand1) == STRAIGHT);
    assert(getStrength(hand2) == STRAIGHT);
    assert(getStrength(hand3) == STRAIGHT);
    assert(getStrength(hand4) == STRAIGHT);
    assert(getStrength(hand5) == STRAIGHT);


    // make sure hands are ranked properly
    assert(hand2 > hand1);
    assert(hand2 > hand3);
    assert(hand3 > hand1);
    assert(hand4 > hand1);
    assert(hand5 > hand1);
    assert(hand4 < hand2);
    assert(hand4 < hand5);

    // print all clear
    cout << "Straights all clear." << endl;
}

void testThreeKind()
{
    vector<Card> test1 = {createCard(ACE, CLUBS), createCard(ACE, DIAMONDS), createCard(ACE, HEARTS), createCard(FOUR, DIAMONDS), createCard(FIVE, CLUBS)};
    vector<Card> test2 = {createCard(TEN, DIAMONDS), createCard(JACK, SPADES), createCard(QUEEN, DIAMONDS), createCard(QUEEN, HEARTS), createCard(QUEEN, SPADES)};
    vector<Card> test3 = {createCard(SEVEN, SPADES), createCard(EIGHT, CLUBS), createCard(EIGHT, SPADES), createCard(EIGHT, HEARTS), createCard(JACK, SPADES)};
    vector<Card> test4 = {createCard(TWO, HEARTS), createCard(TWO, SPADES), createCard(THREE, HEARTS), createCard(TWO, CLUBS), createCard(SIX, DIAMONDS)};
    vector<Card> test5 = {createCard(KING, HEARTS), createCard(SIX, DIAMONDS), createCard(KING, DIAMONDS), createCard(EIGHT, DIAMONDS), createCard(KING, CLUBS)};
    int hand1 = bestHand(test1).score;
    int hand2 = bestHand(test2).score;
    int hand3 = bestHand(test3).score;
    int hand4 = bestHand(test4).score;
    int hand5 = bestHand(test5).score;

    // make sure hands are evaluated as three-of-a-kind's
    assert(getStrength(hand1) == THREE_KIND);
    assert(getStrength(hand2) == THREE_KIND);
    assert(getStrength(hand3) == THREE_KIND);
    assert(getStrength(hand4) == THREE_KIND);
    assert(getStrength(hand5) == THREE_KIND);

    // make sure hands are ranked properly
    assert(hand2 < hand1);
    assert(hand2 > hand3);
    assert(hand3 < hand1);
    assert(hand4 < hand1);
    assert(hand5 < hand1);
    assert(hand4 < hand2);
    assert(hand5 > hand2);

    // print all clear
    cout << "Three kinds all clear." << endl;
}

void testTwoPair()
{
    vector<Card> test1 = {createCard(ACE, CLUBS), createCard(ACE, DIAMONDS), createCard(FOUR, HEARTS), createCard(FOUR, DIAMONDS), createCard(FIVE, CLUBS)};
    vector<Card> test2 = {createCard(ACE, DIAMONDS), createCard(ACE, SPADES), createCard(THREE, DIAMONDS), createCard(THREE, HEARTS), createCard(QUEEN, SPADES)};
    vector<Card> test3 = {createCard(ACE, SPADES), createCard(EIGHT, CLUBS), createCard(EIGHT, SPADES), createCard(SEVEN, HEARTS), createCard(SEVEN, SPADES)};
    vector<Card> test4 = {createCard(TWO, HEARTS), createCard(TWO, SPADES), createCard(THREE, HEARTS), createCard(THREE, CLUBS), createCard(SIX, DIAMONDS)};
    vector<Card> test5 = {createCard(KING, HEARTS), createCard(SIX, DIAMONDS), createCard(KING, DIAMONDS), createCard(SIX, HEARTS), createCard(QUEEN, CLUBS)};
    int hand1 = bestHand(test1).score;
    int hand2 = bestHand(test2).score;
    int hand3 = bestHand(test3).score;
    int hand4 = bestHand(test4).score;
    int hand5 = bestHand(test5).score;

    // make sure hands are evaluated as two pairs
    assert(getStrength(hand1) == TWO_PAIR);
    assert(getStrength(hand2) == TWO_PAIR);
    assert(getStrength(hand3) == TWO_PAIR);
    assert(getStrength(hand4) == TWO_PAIR);
    assert(getStrength(hand5) == TWO_PAIR);

    // make sure hands are ranked properly
    assert(hand2 < hand1);
    assert(hand2 > hand3);
    assert(hand3 < hand1);
    assert(hand4 < hand1);
    assert(hand5 < hand1);
    assert(hand4 < hand2);
    assert(hand5 < hand2);

    // print all clear
    cout << "Two pairs all clear." << endl;
}
void testPair()
{
    vector<Card> test1 = {createCard(ACE, CLUBS), createCard(ACE, DIAMONDS), createCard(FOUR, HEARTS), createCard(THREE, DIAMONDS), createCard(FIVE, CLUBS)};
    vector<Card> test2 = {createCard(ACE, DIAMONDS), createCard(ACE, SPADES), createCard(FOUR, DIAMONDS), createCard(THREE, HEARTS), createCard(SIX, SPADES)};
    vector<Card> test3 = {createCard(ACE, SPADES), createCard(EIGHT, CLUBS), createCard(EIGHT, SPADES), createCard(SEVEN, HEARTS), createCard(SIX, SPADES)};
    vector<Card> test5 = {createCard(FIVE, HEARTS), createCard(SIX, DIAMONDS), createCard(KING, DIAMONDS), createCard(QUEEN, HEARTS), createCard(QUEEN, CLUBS)};
    int hand1 = bestHand(test1).score;
    int hand2 = bestHand(test2).score;
    int hand3 = bestHand(test3).score;
    int hand5 = bestHand(test5).score;

    // make sure hands are evaluated as pairs
    assert(getStrength(hand1) == PAIR);
    assert(getStrength(hand2) == PAIR);
    assert(getStrength(hand3) == PAIR);
    assert(getStrength(hand5) == PAIR);

    // make sure hands are ranked properly
    assert(hand2 > hand1);
    assert(hand2 > hand3);
    assert(hand3 < hand1);
    assert(hand5 < hand1);
    assert(hand5 < hand2);

    // print all clear
    cout << "Pairs all clear." << endl;
}

void testHigh();
void testEverything();