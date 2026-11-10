#include "test.h"
#include "poker.h"

int main()
{
    // run battery of tests
    testStraightFlush();
    testFourKind();
    testFullHouse();
    testFlush();
    testStraight();
    testThreeKind();
    testTwoPair();
    testPair();
    testHigh();
    testEverything();

    // run timing tests
    timeTests();

    // run prob tests
    testRandomHands();

    return 0;
}