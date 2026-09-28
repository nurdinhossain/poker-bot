#pragma once
#include <string_view>
#include <vector>
#include <random>
using Card = unsigned char;
using namespace std;

// define enums
enum Color
{
    RED,
    BLACK
};

enum Suit
{
    SPADES,
    HEARTS,
    DIAMONDS,
    CLUBS
};

enum Value
{
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

// define string names 
constexpr string_view COLOR_NAMES[] = {"Red", "Black"};
constexpr string_view SUIT_NAMES[] = {"Spades", "Hearts", "Diamonds", "Clubs"};
constexpr string_view VALUE_NAMES[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};

// creation
Card createCard(Value value, Suit suit);

// getters
Color getColor(Card card);
Suit getSuit(Card card);
Value getValue(Card card);

// display
void printCard(Card card);

// class to hold deck
class Deck
{
    public:
        // constructor
        Deck();
        ~Deck();

        // card operations
        void mix();
        Card deal(); 
        Card view() const; 
        int remaining() const;
        void reset();
    private:
        vector<Card> deck; 
        mt19937 g;
};