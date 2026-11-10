#include "test.h"
#include "poker.h"
#include <cassert>
#include <chrono>
#include <iostream>

#define CC createCard

// correctness 
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

void testHigh()
{
    vector<Card> test1 = {createCard(ACE, CLUBS), createCard(FIVE, DIAMONDS), createCard(FOUR, HEARTS), createCard(THREE, DIAMONDS), createCard(KING, CLUBS)};
    vector<Card> test2 = {createCard(ACE, DIAMONDS), createCard(KING, SPADES), createCard(EIGHT, DIAMONDS), createCard(THREE, HEARTS), createCard(SIX, SPADES)};
    vector<Card> test3 = {createCard(KING, SPADES), createCard(EIGHT, CLUBS), createCard(QUEEN, SPADES), createCard(SEVEN, HEARTS), createCard(JACK, SPADES)};
    vector<Card> test5 = {createCard(KING, HEARTS), createCard(QUEEN, DIAMONDS), createCard(JACK, DIAMONDS), createCard(EIGHT, HEARTS), createCard(SEVEN, CLUBS)};
    int hand1 = bestHand(test1).score;
    int hand2 = bestHand(test2).score;
    int hand3 = bestHand(test3).score;
    int hand5 = bestHand(test5).score;

    // make sure hands are evaluated as highs
    assert(getStrength(hand1) == HIGH);
    assert(getStrength(hand2) == HIGH);
    assert(getStrength(hand3) == HIGH);
    assert(getStrength(hand5) == HIGH);

    // make sure hands are ranked properly
    assert(hand2 > hand1);
    assert(hand2 > hand3);
    assert(hand3 < hand1);
    assert(hand5 < hand1);
    assert(hand5 == hand3);

    // print all clear
    cout << "Highs all clear." << endl;
}

// Sonnet 5.5 generated test cases
void testEverything()
{
    using Strength = decltype(getStrength(0));
 
    // hands must be listed weakest -> strongest; checks category and strict ordering
    auto checkAscending = [](const vector<vector<Card>> &hands, const vector<Strength> &strengths)
    {
        for (size_t i = 0; i < hands.size(); i++)
        {
            assert(getStrength(bestHand(hands[i]).score) == strengths[i]);
            if (i > 0)
                assert(bestHand(hands[i - 1]).score < bestHand(hands[i]).score);
        }
    };
 
    // ---- 2 cards (pre-flop) ----
    checkAscending({{CC(THREE, CLUBS), CC(TWO, DIAMONDS)},
                    {CC(ACE, SPADES), CC(KING, DIAMONDS)},
                    {CC(TWO, CLUBS), CC(TWO, DIAMONDS)},
                    {CC(ACE, SPADES), CC(ACE, DIAMONDS)}},
                   {HIGH, HIGH, PAIR, PAIR});

    // ---- 3 cards ----
    checkAscending({{CC(FIVE, SPADES), CC(SIX, SPADES), CC(SEVEN, SPADES)}, // not a straight flush
                    {CC(ACE, CLUBS), CC(KING, DIAMONDS), CC(QUEEN, HEARTS)},
                    {CC(TWO, CLUBS), CC(TWO, DIAMONDS), CC(THREE, HEARTS)},
                    {CC(ACE, CLUBS), CC(ACE, DIAMONDS), CC(KING, HEARTS)},
                    {CC(TWO, CLUBS), CC(TWO, DIAMONDS), CC(TWO, HEARTS)},
                    {CC(ACE, CLUBS), CC(ACE, DIAMONDS), CC(ACE, HEARTS)}},
                   {HIGH, HIGH, PAIR, PAIR, THREE_KIND, THREE_KIND});
 
    // ---- 4 cards ----
    checkAscending({{CC(FIVE, CLUBS), CC(SIX, DIAMONDS), CC(SEVEN, HEARTS), CC(EIGHT, SPADES)}, // not a straight
                    {CC(ACE, CLUBS), CC(KING, DIAMONDS), CC(QUEEN, HEARTS), CC(JACK, SPADES)},
                    {CC(TWO, CLUBS), CC(TWO, DIAMONDS), CC(THREE, HEARTS), CC(FOUR, SPADES)},
                    {CC(ACE, CLUBS), CC(ACE, DIAMONDS), CC(KING, HEARTS), CC(QUEEN, SPADES)},
                    {CC(TWO, CLUBS), CC(TWO, DIAMONDS), CC(THREE, HEARTS), CC(THREE, SPADES)},
                    {CC(ACE, CLUBS), CC(ACE, DIAMONDS), CC(KING, HEARTS), CC(KING, SPADES)},
                    {CC(TWO, CLUBS), CC(TWO, DIAMONDS), CC(TWO, HEARTS), CC(THREE, SPADES)},
                    {CC(ACE, CLUBS), CC(ACE, DIAMONDS), CC(ACE, HEARTS), CC(KING, SPADES)},
                    {CC(TWO, CLUBS), CC(TWO, DIAMONDS), CC(TWO, HEARTS), CC(TWO, SPADES)},
                    {CC(ACE, CLUBS), CC(ACE, DIAMONDS), CC(ACE, HEARTS), CC(ACE, SPADES)}},
                   {HIGH, HIGH, PAIR, PAIR, TWO_PAIR, TWO_PAIR, THREE_KIND, THREE_KIND, FOUR_KIND, FOUR_KIND});
 
    // ---- 5 cards: weakest and strongest of every category, so every
    //      hand type is tested against every other ----
    checkAscending({
                       {CC(SEVEN, SPADES), CC(FIVE, DIAMONDS), CC(FOUR, HEARTS), CC(THREE, CLUBS), CC(TWO, SPADES)},            // worst high
                       {CC(ACE, SPADES), CC(KING, DIAMONDS), CC(QUEEN, HEARTS), CC(JACK, CLUBS), CC(NINE, SPADES)},             // best high
                       {CC(TWO, CLUBS), CC(TWO, DIAMONDS), CC(THREE, HEARTS), CC(FOUR, SPADES), CC(SIX, CLUBS)},                // worst pair
                       {CC(ACE, SPADES), CC(ACE, DIAMONDS), CC(KING, HEARTS), CC(QUEEN, CLUBS), CC(JACK, SPADES)},              // best pair
                       {CC(TWO, CLUBS), CC(TWO, DIAMONDS), CC(THREE, HEARTS), CC(THREE, SPADES), CC(FOUR, CLUBS)},              // worst two pair
                       {CC(ACE, SPADES), CC(ACE, DIAMONDS), CC(KING, HEARTS), CC(KING, SPADES), CC(QUEEN, CLUBS)},              // best two pair
                       {CC(TWO, CLUBS), CC(TWO, DIAMONDS), CC(TWO, HEARTS), CC(FOUR, SPADES), CC(THREE, CLUBS)},                // worst trips
                       {CC(ACE, SPADES), CC(ACE, DIAMONDS), CC(ACE, HEARTS), CC(KING, SPADES), CC(QUEEN, CLUBS)},               // best trips
                       {CC(ACE, CLUBS), CC(TWO, DIAMONDS), CC(THREE, HEARTS), CC(FOUR, SPADES), CC(FIVE, CLUBS)},               // worst straight (wheel)
                       {CC(TEN, CLUBS), CC(JACK, DIAMONDS), CC(QUEEN, HEARTS), CC(KING, SPADES), CC(ACE, CLUBS)},               // best straight
                       {CC(SEVEN, HEARTS), CC(FIVE, HEARTS), CC(FOUR, HEARTS), CC(THREE, HEARTS), CC(TWO, HEARTS)},             // worst flush
                       {CC(ACE, HEARTS), CC(KING, HEARTS), CC(QUEEN, HEARTS), CC(JACK, HEARTS), CC(NINE, HEARTS)},              // best flush
                       {CC(TWO, CLUBS), CC(TWO, DIAMONDS), CC(TWO, HEARTS), CC(THREE, SPADES), CC(THREE, CLUBS)},               // worst full house
                       {CC(ACE, SPADES), CC(ACE, DIAMONDS), CC(ACE, HEARTS), CC(KING, SPADES), CC(KING, CLUBS)},                // best full house
                       {CC(TWO, CLUBS), CC(TWO, DIAMONDS), CC(TWO, HEARTS), CC(TWO, SPADES), CC(THREE, CLUBS)},                // worst four kind
                       {CC(ACE, CLUBS), CC(ACE, DIAMONDS), CC(ACE, HEARTS), CC(ACE, SPADES), CC(KING, CLUBS)},                 // best four kind
                       {CC(ACE, CLUBS), CC(TWO, CLUBS), CC(THREE, CLUBS), CC(FOUR, CLUBS), CC(FIVE, CLUBS)},                    // worst straight flush
                       {CC(ACE, HEARTS), CC(KING, HEARTS), CC(QUEEN, HEARTS), CC(JACK, HEARTS), CC(TEN, HEARTS)},               // royal flush
                   },
                   {HIGH, HIGH, PAIR, PAIR, TWO_PAIR, TWO_PAIR, THREE_KIND, THREE_KIND, STRAIGHT, STRAIGHT,
                    FLUSH, FLUSH, FULL_HOUSE, FULL_HOUSE, FOUR_KIND, FOUR_KIND, STRAIGHT_FLUSH, STRAIGHT_FLUSH});
 
    // ---- 6 cards: one hand per category, best 5 of 6 must be found ----
    checkAscending({{CC(ACE, SPADES), CC(KING, DIAMONDS), CC(NINE, HEARTS), CC(SEVEN, CLUBS), CC(FIVE, SPADES), CC(THREE, DIAMONDS)},
                    {CC(ACE, SPADES), CC(ACE, DIAMONDS), CC(NINE, HEARTS), CC(SEVEN, CLUBS), CC(FIVE, SPADES), CC(THREE, DIAMONDS)},
                    {CC(ACE, SPADES), CC(ACE, DIAMONDS), CC(NINE, HEARTS), CC(NINE, CLUBS), CC(FIVE, SPADES), CC(THREE, DIAMONDS)},
                    {CC(ACE, SPADES), CC(ACE, DIAMONDS), CC(ACE, HEARTS), CC(SEVEN, CLUBS), CC(FIVE, SPADES), CC(THREE, DIAMONDS)},
                    {CC(FIVE, CLUBS), CC(SIX, DIAMONDS), CC(SEVEN, HEARTS), CC(EIGHT, SPADES), CC(NINE, CLUBS), CC(KING, DIAMONDS)},
                    {CC(TWO, HEARTS), CC(FIVE, HEARTS), CC(NINE, HEARTS), CC(JACK, HEARTS), CC(KING, HEARTS), CC(THREE, CLUBS)},
                    {CC(KING, CLUBS), CC(KING, DIAMONDS), CC(KING, HEARTS), CC(FOUR, SPADES), CC(FOUR, CLUBS), CC(FOUR, DIAMONDS)}, // two trips
                    {CC(FIVE, CLUBS), CC(FIVE, DIAMONDS), CC(FIVE, HEARTS), CC(FIVE, SPADES), CC(NINE, CLUBS), CC(NINE, DIAMONDS)},
                    {CC(FOUR, CLUBS), CC(FIVE, CLUBS), CC(SIX, CLUBS), CC(SEVEN, CLUBS), CC(EIGHT, CLUBS), CC(THREE, CLUBS)}},
                   {HIGH, PAIR, TWO_PAIR, THREE_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_KIND, STRAIGHT_FLUSH});
 
    // ---- 7 cards (river): one hand per category, best 5 of 7 must be found ----
    checkAscending({{CC(ACE, SPADES), CC(KING, DIAMONDS), CC(NINE, HEARTS), CC(SEVEN, CLUBS), CC(FIVE, SPADES), CC(THREE, DIAMONDS), CC(TWO, HEARTS)},
                    {CC(ACE, SPADES), CC(ACE, DIAMONDS), CC(NINE, HEARTS), CC(SEVEN, CLUBS), CC(FIVE, SPADES), CC(THREE, DIAMONDS), CC(TWO, HEARTS)},
                    {CC(ACE, SPADES), CC(ACE, DIAMONDS), CC(NINE, HEARTS), CC(NINE, CLUBS), CC(FIVE, SPADES), CC(THREE, DIAMONDS), CC(TWO, HEARTS)},
                    {CC(ACE, SPADES), CC(ACE, DIAMONDS), CC(ACE, HEARTS), CC(NINE, CLUBS), CC(FIVE, SPADES), CC(THREE, DIAMONDS), CC(TWO, HEARTS)},
                    {CC(FIVE, CLUBS), CC(FIVE, DIAMONDS), CC(SIX, HEARTS), CC(SEVEN, SPADES), CC(EIGHT, CLUBS), CC(NINE, DIAMONDS), CC(NINE, HEARTS)},   // straight + two pair
                    {CC(TWO, HEARTS), CC(THREE, HEARTS), CC(FOUR, HEARTS), CC(FIVE, HEARTS), CC(NINE, HEARTS), CC(SIX, CLUBS), CC(KING, DIAMONDS)},      // flush + straight
                    {CC(QUEEN, CLUBS), CC(QUEEN, DIAMONDS), CC(QUEEN, HEARTS), CC(NINE, SPADES), CC(NINE, CLUBS), CC(FOUR, DIAMONDS), CC(FOUR, HEARTS)}, // full house + extra pair
                    {CC(SEVEN, CLUBS), CC(SEVEN, DIAMONDS), CC(SEVEN, HEARTS), CC(SEVEN, SPADES), CC(KING, CLUBS), CC(KING, DIAMONDS), CC(KING, HEARTS)}, // quads + trips
                    {CC(ACE, HEARTS), CC(TWO, HEARTS), CC(THREE, HEARTS), CC(FOUR, HEARTS), CC(FIVE, HEARTS), CC(KING, CLUBS), CC(KING, DIAMONDS)}},      // wheel straight flush
                   {HIGH, PAIR, TWO_PAIR, THREE_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_KIND, STRAIGHT_FLUSH});
 
    cout << "Everything all clear." << endl;
}

// timing
void timeTests()
{
    vector<Card> test = {createCard(ACE, CLUBS), createCard(FIVE, DIAMONDS), createCard(FOUR, HEARTS), createCard(THREE, DIAMONDS), createCard(KING, CLUBS), createCard(SEVEN, SPADES), createCard(TWO, DIAMONDS)};

    auto start = chrono::system_clock::now();
    auto duration = start.time_since_epoch();
    auto millis = chrono::duration_cast<chrono::milliseconds>(duration).count();

    for (int i = 1; i <= MAX_N; i++)
    {
        bestHand(test);

        double lg = log10(i);
        if (lg > 0 && lg == floor(lg))
        {
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count() - millis;
            cout << "After " << i << " loops: " << elapsed << " ms" << endl;
        }
    }
}

// probabilities
void testRandomHands()
{
    Deck deck;
    vector<int> buckets = vector(STRAIGHT_FLUSH+1, 0);

    for (int i = 0; i < MAX_N; i++)
    {
        // reset and shuffle deck
        deck.reset();
        deck.mix();

        // deal 7 cards
        vector<Card> hand;
        for (int k = 0; k < 7; k++)
        {
            hand.push_back(deck.deal());
        }

        // get best hand
        ScoredHand best = bestHand(hand);
        Strength st = getStrength(best.score);
        buckets[st]++;
    }

    for (int i = 0; i < buckets.size(); i++)
    {
        cout << buckets[i] << endl;
    }
}