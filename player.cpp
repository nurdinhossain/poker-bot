#include "player.h"

// constructor
Hand::Hand(int money, int la, int ba)
{
    isLittle = false;
    isBig = false;

    balance = money;
    littleAmount = la;
    bigAmount = ba;

    prevRaise = 0;
}

Hand::~Hand() {}

// operations
int Hand::viewBalance()
{
    return balance;
}

void Hand::addBalance(int money)
{
    balance += money;
}

void Hand::removeBalance(int money)
{
    if (money <= balance) balance -= money;
}

void Hand::clearHand()
{
    hand.clear();
}
void Hand::addHand(Card card)
{
    hand.push_back(card);
}

void Hand::toggleLittle()
{
    isLittle = true;
    isBig = false;
}

void Hand::toggleBig()
{
    isBig = true;
    isLittle = false;
}

void Hand::toggleNormal()
{
    isBig = false;
    isLittle = false;
}

void Hand::updatePrevRaise(int raise)
{
    prevRaise = raise;
}