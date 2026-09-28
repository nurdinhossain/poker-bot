#include "card.h"
#include <iostream>
#include <algorithm>

// creation
Card createCard(Value value, Suit suit)
{
    Card card = static_cast<Card>(value);
    card += static_cast<Card>(suit) << 4;
    
    return card;
}

// getters
Color getColor(Card card)
{
    Suit suit = getSuit(card);
    if (suit == HEARTS || suit == DIAMONDS) return RED;
    return BLACK;
}

Suit getSuit(Card card)
{
    return static_cast<Suit>( (card >> 4) & 3 );
}

Value getValue(Card card)
{
    return static_cast<Value>( card & 15 );
}

// display
void printCard(Card card)
{
    Suit suit = getSuit(card);
    Value value = getValue(card);

    cout << VALUE_NAMES[value] << " of " << SUIT_NAMES[suit] << endl;
}

// deck class
Deck::Deck()
{
    g = mt19937(random_device{}());
    reset();
}

Deck::~Deck()
{

}

void Deck::mix()
{
    shuffle(deck.begin(), deck.end(), g);
}

Card Deck::deal()
{
    Card card = deck.back();
    deck.pop_back();
    return card;
}

Card Deck::view() const
{
    return deck.back();
}

int Deck::remaining() const
{
    return deck.size();
}

void Deck::reset()
{
    // empty deck
    deck.clear();

    // instantiate cards in deck
    for (int i = SPADES; i <= CLUBS; i++)
    {
        for (int j = TWO; j <= ACE; j++)
        {
            deck.push_back(createCard(static_cast<Value>(j), static_cast<Suit>(i)));
        }
    }
}