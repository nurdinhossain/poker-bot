#include "poker.h"
#include <iostream>

vector<Card> bestStraightFlush(vector<vector<Card>> buckets)
{
    // assemble suits
    vector<Card> suitCards[4]; // each suit contains card values in descending order
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        for (Card card : buckets[i]) 
        {
            suitCards[getSuit(card)].push_back(card);
        }
    }

    // iterate thru each suit and seek out flush
    for (int i = SPADES; i <= CLUBS; i++)
    {
        // flush!
        if (suitCards[i].size() >= 5) 
        {
            for (int start = 0; start <= suitCards[i].size()-5; start++)
            {
                vector<Card> candidate = {suitCards[i][start], suitCards[i][start+1], suitCards[i][start+2], suitCards[i][start+3], suitCards[i][start+4]};

                bool isValid = true;
                for (int j = 1; j < candidate.size(); j++)
                {
                    if (( getValue(candidate[j-1]) - getValue(candidate[j]) ) != 1) 
                    {
                        isValid = false;
                        break;
                    }
                }

                if (isValid) return candidate;
            }
            
            // check for ace-low straight suit
            if (getValue(suitCards[i][suitCards[i].size()-1]) == TWO && getValue(suitCards[i][suitCards[i].size()-4]) == FIVE && getValue(suitCards[i][0]) == ACE)
                return {suitCards[i][suitCards[i].size()-4], suitCards[i][suitCards[i].size()-3], suitCards[i][suitCards[i].size()-2], suitCards[i][suitCards[i].size()-1], suitCards[i][0]};
        }
    }

    return {};
}

vector<Card> bestFlush(vector<vector<Card>> buckets)
{   
    // assemble suits
    vector<Card> suitCards[4];
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        for (Card card : buckets[i]) 
        {
            suitCards[getSuit(card)].push_back(card);
        }
    }

    // iterate thru each suit and seek out flush
    for (int i = SPADES; i <= CLUBS; i++)
    {
        // flush!
        if (suitCards[i].size() >= 5) return {suitCards[i][0], suitCards[i][1], suitCards[i][2], suitCards[i][3], suitCards[i][4]};
    }

    return {};
}

vector<Card> bestStraight(vector<vector<Card>> buckets)
{
    int seqLength = 0;
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        if (buckets[i].size() > 0) seqLength++;
        else seqLength = 0;

        if (seqLength == 5)
        {
            return {buckets[i+4][0], buckets[i+3][0], buckets[i+2][0], buckets[i+1][0], buckets[i][0]};
        }
    }

    if (seqLength == 4 && buckets[ACE].size() > 0) return {buckets[3][0], buckets[2][0], buckets[1][0], buckets[0][0], buckets[ACE][0]};

    return {};
}

vector<Card> fourOfAKind(vector<vector<Card>> buckets)
{
    // iterate through cards to find four of a kind
    vector<Card> res;
    int kindBucket = -1;
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        // add 4-of-a-kind to resulting hand
        if (kindBucket == -1 && buckets[i].size() == 4)
        {
            for (Card card : buckets[i]) res.push_back(card);
            kindBucket = i;
            i = buckets.size(); // must reset so cards before the 4-kind don't get skipped for kicker choice
        }

        // add kicker
        else if (kindBucket > -1 && buckets[i].size() > 0 && i != kindBucket) 
        {
            res.push_back(buckets[i][0]);
            return res;
        }
    }
    
    return res;
}

vector<Card> bestFullHouse(vector<vector<Card>> buckets)
{
    // go from highest to lowest value to see if we have >=3 on one value and >=2 on another
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        for (int j = buckets.size()-1; j >= 0; j--)
        {
            if (i == j) continue;

            if (buckets[i].size() >= 3 && buckets[j].size() >= 2) return {buckets[i][0], buckets[i][1], buckets[i][2], buckets[j][0], buckets[j][1]};
        }
    }

    return {}; 
}

vector<Card> bestThreeOfAKind(vector<vector<Card>> buckets)
{
    // iterate through cards to find three of a kind
    vector<Card> res;
    int kindBucket = -1;
    int numKickers = 2;
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        // add 3-of-a-kind to resulting hand
        if (kindBucket == -1 && buckets[i].size() >= 3)
        {
            for (Card card : buckets[i]) res.push_back(card);
            kindBucket = i;
            i = buckets.size(); // fix bug similar to four of a kind bug
        }

        // add kicker(s)
        else if (kindBucket >-1 && buckets[i].size() > 0 && i != kindBucket) 
        {
            res.push_back(buckets[i][0]);
            numKickers--;

            if (numKickers == 0) return res;
        }
    }
    
    return res;
}

vector<Card> bestTwoPair(vector<vector<Card>> buckets)
{
    // iterate through cards to find two pair
    vector<Card> res;
    int pairsLeft = 2;
    vector<int> kinds;
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        // add pair to resulting hand
        if (pairsLeft > 0 && buckets[i].size() >= 2)
        {
            for (Card card : buckets[i]) res.push_back(card);
            pairsLeft--;
            kinds.push_back(i);

            if (pairsLeft == 0) i = buckets.size(); // fix bug similar to four of a kind bug
        }

        // add kicker
        else if (pairsLeft == 0 && buckets[i].size() > 0 && i != kinds[0] && i != kinds[1]) 
        {
            res.push_back(buckets[i][0]);
            return res;
        }
    }
    
    if (pairsLeft > 0) return {};

    return res;
}

vector<Card> bestPair(vector<vector<Card>> buckets)
{
    // iterate through cards to find pair
    vector<Card> res;
    int pairKind = -1;
    int kickers = 3;
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        // add pair to resulting hand
        if (pairKind == -1 && buckets[i].size() >= 2)
        {
            for (Card card : buckets[i]) res.push_back(card);
            pairKind = i;
            i = buckets.size(); // fix bug similar to four of a kind bug
        }

        // add kickers
        else if (pairKind > -1 && kickers > 0 && buckets[i].size() > 0 && i != pairKind) 
        {
            res.push_back(buckets[i][0]);
            kickers--;
            
            if (kickers == 0) return res;
        }
    }

    return res;
}

ScoredHand bestHandHelper(vector<Card> cards)
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
                    return { bestHand, FOUR_KIND };
                }
            }
            
            // if no kicker is found, then return hand as-is
            return { bestHand, FOUR_KIND };
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
                if (currentSequence == 5 && highestStrength < STRAIGHT)
                {
                    highestStrength = STRAIGHT;
                    bestHand = { buckets[i+4][0], buckets[i+3][0], buckets[i+2][0], buckets[i+1][0], buckets[i][0] };
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
                std::cout << "Flush!" << endl;
                highestStrength = FLUSH;
                bestHand = suitCards[cardSuit];
            } 

            // check if we've made a straight flush
            if (suitCards[cardSuit].size() >= 5)
            {
                Value one = getValue(suitCards[cardSuit][suitCards[cardSuit].size()-1]);
                Value five = getValue(suitCards[cardSuit][suitCards[cardSuit].size()-5]);
                Value first = getValue(suitCards[cardSuit][0]);
                cout << five << ", " << one << endl;

                // check for highest straight flush possible
                if ((five - one) == 4) return { { suitCards[cardSuit][suitCards[cardSuit].size()-5], suitCards[cardSuit][suitCards[cardSuit].size()-4], suitCards[cardSuit][suitCards[cardSuit].size()-3], suitCards[cardSuit][suitCards[cardSuit].size()-2], suitCards[cardSuit][suitCards[cardSuit].size()-1] }, STRAIGHT_FLUSH };

                // check for lowest straight flush possible
                if (one == TWO && getValue(suitCards[cardSuit][suitCards[cardSuit].size()-4]) == FIVE && first == ACE) return { { suitCards[cardSuit][suitCards[cardSuit].size()-4], suitCards[cardSuit][suitCards[cardSuit].size()-3], suitCards[cardSuit][suitCards[cardSuit].size()-2], suitCards[cardSuit][suitCards[cardSuit].size()-1], suitCards[cardSuit][0] }, STRAIGHT_FLUSH};
            }
        }
    }

    // final eval
    switch (highestStrength)
    {
        case FULL_HOUSE:
            return {bestHand, highestStrength};
        case FLUSH:
            return {bestHand, highestStrength};
        case STRAIGHT:
            return {bestHand, highestStrength};
        case THREE_KIND:
            // add 3 cards
            bestHand = buckets[ptValues[1]];

            for (int i = buckets.size()-1; i >= 0; i--)
            {
                if (i == ptValues[1]) continue;

                if (buckets[i].size() > 0)
                {
                    bestHand.push_back(buckets[i][0]);

                    if (bestHand.size() >= 5) return {bestHand, highestStrength};
                }
            }    

            return {bestHand, highestStrength};
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

                    if (bestHand.size() >= 5) return {bestHand, highestStrength};
                }
            }    
            
            return {bestHand, highestStrength};
        case PAIR:
            // add two cards
            bestHand = buckets[ptValues[0]];

            for (int i = buckets.size()-1; i >= 0; i--)
            {
                if (i == ptValues[0]) continue;

                if (buckets[i].size() > 0)
                {
                    bestHand.push_back(buckets[i][0]);

                    if (bestHand.size() >= 5) return {bestHand, highestStrength};
                }
            }    
            
            return {bestHand, highestStrength};
        default:
            for (int i = buckets.size()-1; i >= 0; i--)
            {
                if (buckets[i].size() > 0)
                {
                    bestHand.push_back(buckets[i][0]);

                    if (bestHand.size() >= 5) return {bestHand, highestStrength};
                }
            }   

            return {bestHand, highestStrength};
    }
}

ScoredHand bestHand(vector<Card> cards)
{
    return bestHandHelper(cards);

    // sort cards into buckets
    vector<vector<Card>> buckets(13, vector<Card>());
    for (Card card : cards) buckets[getValue(card)].push_back(card);

    // go down the list of best hands to find what hand this is

    // straight flush
    vector<Card> straightFlush = bestStraightFlush(buckets);
    if (straightFlush.size() > 0) 
    {
        int score = STRAIGHT_FLUSH;
        for (Card card : straightFlush) 
        {
            score <<= KICKER_SHIFT;
            score += getValue(card);
        }
        score <<= KICKER_SHIFT * (HAND_SIZE - straightFlush.size());

        return {straightFlush, score};
    }

    // four of a kind
    vector<Card> four = fourOfAKind(buckets);
    if (four.size() > 0) 
    {
        int score = FOUR_KIND;
        for (Card card : four) 
        {
            score <<= KICKER_SHIFT;
            score += getValue(card);
        }
        score <<= KICKER_SHIFT * (HAND_SIZE - four.size());

        return {four, score};
    }

    // full house
    vector<Card> fullHouse = bestFullHouse(buckets);
    if (fullHouse.size() > 0) 
    {
        int score = FULL_HOUSE;
        for (Card card : fullHouse) 
        {
            score <<= KICKER_SHIFT;
            score += getValue(card);
        }
        score <<= KICKER_SHIFT * (HAND_SIZE - fullHouse.size());

        return {fullHouse, score};
    }

    // flush
    vector<Card> flush = bestFlush(buckets);
    if (flush.size() > 0)
    {
        int score = FLUSH;
        for (Card card : flush) 
        {
            score <<= KICKER_SHIFT;
            score += getValue(card);
        }
        score <<= KICKER_SHIFT * (HAND_SIZE - flush.size());

        return {flush, score};
    }

    // straight
    vector<Card> straight = bestStraight(buckets);
    if (straight.size() > 0)
    {
        int score = STRAIGHT;
        for (Card card : straight) 
        {
            score <<= KICKER_SHIFT;
            score += getValue(card);
        }
        score <<= KICKER_SHIFT * (HAND_SIZE - straight.size());

        return {straight, score};
    }

    // three of a kind
    vector<Card> three = bestThreeOfAKind(buckets);
    if (three.size() > 0) 
    {
        int score = THREE_KIND;
        for (Card card : three) 
        {
            score <<= KICKER_SHIFT;
            score += getValue(card);
        }
        score <<= KICKER_SHIFT * (HAND_SIZE - three.size());

        return {three, score};
    }

    // two pair
    vector<Card> twoPair = bestTwoPair(buckets);
    if (twoPair.size() > 0)
    {
        int score = TWO_PAIR;
        for (Card card : twoPair) 
        {
            score <<= KICKER_SHIFT;
            score += getValue(card);
        }
        score <<= KICKER_SHIFT * (HAND_SIZE - twoPair.size());

        return {twoPair, score};
    }

    // pair
    vector<Card> pair = bestPair(buckets);
    if (pair.size() > 0)
    {
        int score = PAIR;
        for (Card card : pair) 
        {
            score <<= KICKER_SHIFT;
            score += getValue(card);
        }
        score <<= KICKER_SHIFT * (HAND_SIZE - pair.size());

        return {pair, score};
    }

    // high card
    vector<Card> res;
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        if (buckets[i].size() > 0)
        {
            res.push_back(buckets[i][0]);
            if (res.size() >= 5 || res.size() == cards.size()) break;
        }
    }

    int score = HIGH;
    for (Card card : res) 
    {
        score <<= KICKER_SHIFT;
        score += getValue(card);
    }
    score <<= KICKER_SHIFT * (HAND_SIZE - res.size());

    return {res, score};
}

Strength getStrength(int score)
{
    return static_cast<Strength>(score >> (KICKER_SHIFT * 5));
}