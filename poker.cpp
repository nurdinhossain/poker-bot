#include "poker.h"
#include <algorithm>

vector<Card> bestStraightFlush(vector<vector<Card>> buckets)
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
                return {suitCards[i][0], suitCards[i][suitCards[i].size()-4], suitCards[i][suitCards[i].size()-3], suitCards[i][suitCards[i].size()-2], suitCards[i][suitCards[i].size()-1]};
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
            return {buckets[i][0], buckets[i+1][0], buckets[i+2][0], buckets[i+3][0], buckets[i+4][0]};
        }
    }

    if (seqLength == 4 && buckets[ACE].size() > 0) return {buckets[0][0], buckets[1][0], buckets[2][0], buckets[3][0], buckets[ACE][0]};

    return {};
}

vector<Card> fourOfAKind(vector<vector<Card>> buckets)
{
    // iterate through cards to find four of a kind
    vector<Card> res;
    bool kindFound = false;
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        // add 4-of-a-kind to resulting hand
        if (!kindFound && buckets[i].size() == 4)
        {
            for (Card card : buckets[i]) res.push_back(card);
            kindFound = true;
            i = buckets.size(); // must reset so cards before the 4-kind don't get skipped for kicker choice
        }

        // add kicker
        else if (kindFound && buckets[i].size() > 0) 
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
    bool kindFound = false;
    int numKickers = 2;
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        // add 3-of-a-kind to resulting hand
        if (!kindFound && buckets[i].size() >= 3)
        {
            for (Card card : buckets[i]) res.push_back(card);
            kindFound = true;
            i = buckets.size(); // fix bug similar to four of a kind bug
        }

        // add kicker(s)
        else if (kindFound && buckets[i].size() > 0) 
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
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        // add pair to resulting hand
        if (pairsLeft > 0 && buckets[i].size() >= 2)
        {
            for (Card card : buckets[i]) res.push_back(card);
            pairsLeft--;

            if (pairsLeft == 0) i = buckets.size(); // fix bug similar to four of a kind bug
        }

        // add kicker
        else if (pairsLeft == 0 && buckets[i].size() > 0) 
        {
            res.push_back(buckets[i][0]);
            return res;
        }
    }
    
    return res;
}

vector<Card> bestPair(vector<vector<Card>> buckets)
{
    // iterate through cards to find pair
    vector<Card> res;
    bool pairFound = false;
    int kickers = 3;
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        // add pair to resulting hand
        if (!pairFound && buckets[i].size() >= 2)
        {
            for (Card card : buckets[i]) res.push_back(card);
            pairFound = true;
            i = buckets.size(); // fix bug similar to four of a kind bug
        }

        // add kickers
        else if (pairFound && kickers > 0 && buckets[i].size() > 0) 
        {
            res.push_back(buckets[i][0]);
            kickers--;
            
            if (kickers == 0) return res;
        }
    }
    
    return res;
}

ScoredHand bestHand(vector<Card> cards)
{
    // sort cards into buckets
    vector<vector<Card>> buckets(13, vector<Card>());
    for (Card card : cards) buckets[getValue(card)].push_back(card);

    // go down the list of best hands to find what hand this is

    // straight flush
    vector<Card> straightFlush = bestStraightFlush(buckets);
    if (straightFlush.size() > 0) 
    {
        int score = STRAIGHT_FLUSH;

        // be wary of ace-low
        if (getValue(straightFlush[0]) == ACE && getValue(straightFlush[4]) == TWO)
        {
            score <<= KICKER_SHIFT;
            score += getValue(straightFlush[1]);
            score <<= KICKER_SHIFT;
            score += getValue(straightFlush[2]);
            score <<= KICKER_SHIFT;
            score += getValue(straightFlush[3]);
            score <<= KICKER_SHIFT;
            score += getValue(straightFlush[4]);
            score <<= KICKER_SHIFT;
            score += 1;

            return {straightFlush, score};
        }

        for (Card card : straightFlush) 
        {
            score <<= KICKER_SHIFT;
            score += getValue(card);
        }
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
        return {flush, score};
    }

    // straight
    vector<Card> straight = bestStraight(buckets);
    if (straight.size() > 0)
    {
        int score = STRAIGHT;

        // be wary of ace-low
        if (getValue(straight[0]) == ACE && getValue(straight[4]) == TWO)
        {
            score <<= KICKER_SHIFT;
            score += getValue(straight[1]);
            score <<= KICKER_SHIFT;
            score += getValue(straight[2]);
            score <<= KICKER_SHIFT;
            score += getValue(straight[3]);
            score <<= KICKER_SHIFT;
            score += getValue(straight[4]);
            score <<= KICKER_SHIFT;
            score += 1;

            return {straight, score};
        }

        for (Card card : straight) 
        {
            score <<= KICKER_SHIFT;
            score += getValue(card);
        }
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
        return {pair, score};
    }

    // high card
    vector<Card> res;
    for (int i = buckets.size()-1; i >= 0; i--)
    {
        res.push_back(buckets[i][0]);
        if (res.size() >= 5 || res.size() == cards.size()) break;
    }

    int score = HIGH;
    for (Card card : res) 
    {
        score <<= KICKER_SHIFT;
        score += getValue(card);
    }
    return {res, score};
}

Strength getStrength(int score)
{
    return static_cast<Strength>(score >> (KICKER_SHIFT * 5));
}