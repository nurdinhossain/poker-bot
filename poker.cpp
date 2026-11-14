#include "poker.h"

int score(vector<Card> cards, Strength strength)
{
    int score = strength;
    for (Card card : cards) 
    {
        score <<= KICKER_SHIFT;
        score += getValue(card);
    }
    score <<= KICKER_SHIFT * (HAND_SIZE - cards.size());

    return score;
}

ScoredHand bestHand(vector<Card> cards)
{
    // sort cards into buckets
    vector<vector<Card>> buckets(13, vector<Card>());
    vector<Card> suitCards[4];
    for (Card card : cards) buckets[getValue(card)].push_back(card);

    // our final return
    Strength highestStrength = HIGH;
    vector<Card> bestHand;

    // book-keeping
    vector<bool> hasPT = { false, false };
    vector<Value> ptValues = { TWO, TWO };
    bool hasSecondPair;
    Value secondPairValue = TWO;
    int currentSequence = 0;

    // go through the buckets in descending order by value (ACE, KING, QUEEN, ..., THREE, TWO)
    for (int i = buckets.size()-1; i >= 0; i--) 
    {
        // check for quads
        if (buckets[i].size() >= 4)
        {
            // if quads are found, find kicker and return
            bestHand = buckets[i];
            for (int k = buckets.size()-1; k >= 0; k--)
            {
                if (buckets[k].size() > 0 && k != i)
                {
                    bestHand.push_back(buckets[k][0]);
                    return { bestHand, score(bestHand, FOUR_KIND) };
                }
            }
            
            // if no kicker is found, then return hand as-is
            return { bestHand, score(bestHand, FOUR_KIND) };
        }

        // straights, trips, pairs
        if (highestStrength < FULL_HOUSE)
        {
            // combining straights check w/ others
            if (buckets[i].size() > 0)
            {
                // add 1 to current sequence
                currentSequence++;

                // if current sequence is 5, we have a straight
                if (highestStrength < STRAIGHT)
                {
                    // high straight
                    if (currentSequence == 5)
                    {
                        highestStrength = STRAIGHT;
                        bestHand = { buckets[i+4][0], buckets[i+3][0], buckets[i+2][0], buckets[i+1][0], buckets[i][0] };
                    }

                    // low straight
                    else if (currentSequence == 4 && i == TWO && buckets[ACE].size() > 0)
                    {
                        highestStrength = STRAIGHT;
                        bestHand = { buckets[i+3][0], buckets[i+2][0], buckets[i+1][0], buckets[i][0], buckets[ACE][0] };
                    }
                }

                // check for trips
                if (buckets[i].size() >= 3)
                {
                    // if we've found trips before, this elevates to the best full house
                    if (hasPT[1])
                    {
                        highestStrength = FULL_HOUSE;
                        bestHand = { buckets[ptValues[1]][0], buckets[ptValues[1]][1], buckets[ptValues[1]][2], buckets[i][0], buckets[i][1] };
                    }

                    // if we've found a pair before, this elevates to a lesser full house
                    else if (hasPT[0])
                    {
                        highestStrength = FULL_HOUSE;
                        bestHand = { buckets[i][0], buckets[i][1], buckets[i][2], buckets[ptValues[0]][0], buckets[ptValues[0]][1] };
                    }

                    // otherwise these are just regular trips
                    else
                    {
                        hasPT[1] = true;
                        ptValues[1] = static_cast<Value>(i); 
                        highestStrength = max(highestStrength, THREE_KIND);
                    }
                }

                // check for pairs
                else if (buckets[i].size() >= 2)
                {
                    // if we've found trips before, this is a full house
                    if (hasPT[1])
                    {
                        highestStrength = FULL_HOUSE;
                        bestHand = { buckets[ptValues[1]][0], buckets[ptValues[1]][1], buckets[ptValues[1]][2], buckets[i][0], buckets[i][1] };
                    }

                    // if we've found pairs before, this is a two-pair
                    else if (hasPT[0] && !hasSecondPair)
                    {
                        hasSecondPair = true;
                        secondPairValue = static_cast<Value>(i);
                        highestStrength = max(highestStrength, TWO_PAIR);
                    }

                    // otherwise, this is just a pair
                    else
                    {
                        hasPT[0] = true;
                        ptValues[0] = static_cast<Value>(i);
                        highestStrength = max(highestStrength, PAIR);
                    }
                }
            }
            else currentSequence = 0;
        }

        // sort all cards in this value bucket into their appropriate suits
        for (Card card : buckets[i]) 
        {
            Suit cardSuit = getSuit(card);
            suitCards[cardSuit].push_back(card);

            // check if we've made a flush
            if (suitCards[cardSuit].size() >= 5 && FLUSH > highestStrength)
            {
                highestStrength = FLUSH;
                bestHand = suitCards[cardSuit];
            } 

            // check if we've made a straight flush
            if (suitCards[cardSuit].size() >= 5)
            {
                Value one = getValue(suitCards[cardSuit][suitCards[cardSuit].size()-1]);
                Value five = getValue(suitCards[cardSuit][suitCards[cardSuit].size()-5]);
                Value first = getValue(suitCards[cardSuit][0]);

                // check for highest straight flush possible
                if ((five - one) == 4) 
                {
                    bestHand = { suitCards[cardSuit][suitCards[cardSuit].size()-5], suitCards[cardSuit][suitCards[cardSuit].size()-4], suitCards[cardSuit][suitCards[cardSuit].size()-3], suitCards[cardSuit][suitCards[cardSuit].size()-2], suitCards[cardSuit][suitCards[cardSuit].size()-1] };
                    return { bestHand, score(bestHand, STRAIGHT_FLUSH) };
                }

                // check for lowest straight flush possible
                if (one == TWO && getValue(suitCards[cardSuit][suitCards[cardSuit].size()-4]) == FIVE && first == ACE) 
                {
                    bestHand = { suitCards[cardSuit][suitCards[cardSuit].size()-4], suitCards[cardSuit][suitCards[cardSuit].size()-3], suitCards[cardSuit][suitCards[cardSuit].size()-2], suitCards[cardSuit][suitCards[cardSuit].size()-1], suitCards[cardSuit][0] };
                    return { bestHand, score(bestHand, STRAIGHT_FLUSH) };
                }   
            }
        }
    }

    // final eval
    switch (highestStrength)
    {
        case FULL_HOUSE:
            return {bestHand, score(bestHand, highestStrength)};
        case FLUSH:
            return {bestHand, score(bestHand, highestStrength)};
        case STRAIGHT:
            return {bestHand, score(bestHand, highestStrength)};
        case THREE_KIND:
            // add 3 cards
            bestHand = buckets[ptValues[1]];

            for (int i = buckets.size()-1; i >= 0; i--)
            {
                if (i == ptValues[1]) continue;

                if (buckets[i].size() > 0)
                {
                    bestHand.push_back(buckets[i][0]);

                    if (bestHand.size() >= 5) return {bestHand, score(bestHand, highestStrength)};
                }
            }    

            return {bestHand, score(bestHand, highestStrength)};
        case TWO_PAIR:
            // add 4 cards
            bestHand = buckets[ptValues[0]];
            bestHand.push_back(buckets[secondPairValue][0]);
            bestHand.push_back(buckets[secondPairValue][1]);

            for (int i = buckets.size()-1; i >= 0; i--)
            {
                if (i == ptValues[0]) continue;
                if (i == secondPairValue) continue;

                if (buckets[i].size() > 0)
                {
                    bestHand.push_back(buckets[i][0]);

                    if (bestHand.size() >= 5) return {bestHand, score(bestHand, highestStrength)};
                }
            }    
            
            return {bestHand, score(bestHand, highestStrength)};
        case PAIR:
            // add two cards
            bestHand = buckets[ptValues[0]];

            for (int i = buckets.size()-1; i >= 0; i--)
            {
                if (i == ptValues[0]) continue;

                if (buckets[i].size() > 0)
                {
                    bestHand.push_back(buckets[i][0]);

                    if (bestHand.size() >= 5) return {bestHand, score(bestHand, highestStrength)};
                }
            }    
            
            return {bestHand, score(bestHand, highestStrength)};
        default:
            for (int i = buckets.size()-1; i >= 0; i--)
            {
                if (buckets[i].size() > 0)
                {
                    bestHand.push_back(buckets[i][0]);

                    if (bestHand.size() >= 5) return {bestHand, score(bestHand, highestStrength)};
                }
            }   

            return {bestHand, score(bestHand, highestStrength)};
    }
}

Strength getStrength(int score)
{
    return static_cast<Strength>(score >> (KICKER_SHIFT * 5));
}