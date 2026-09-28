#include <iostream>
#include "test.h"
#include "poker.h"

int main()
{
    // run battery of tests
    testStraightFlush();
    testFourKind();
    testFullHouse();
    testFlush();

    return 0;
}