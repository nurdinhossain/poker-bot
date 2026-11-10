#include "timing.h"
#include "poker.h"
#include <chrono>
#include <iostream>

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