#include "test.h"
#include "poker.h"
#include "timing.h"

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

    return 0;
}