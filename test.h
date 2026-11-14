#pragma once

// correctness
void testStraightFlush();
void testFourKind();
void testFullHouse();
void testFlush();
void testStraight();
void testThreeKind();
void testTwoPair();
void testPair();
void testHigh();
void testEverything();

// timing
const int MAX_N = 1000000;

void timeTests();

// probabilities
void testRandomHands();