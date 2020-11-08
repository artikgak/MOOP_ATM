#include "Card.h"

Card::Card(const uint64 num):
    cardNumber(num)
{}

Card::Card(const Card& card):
    cardNumber(card.getNumber())
{}

Card::~Card() {

}

uint64 Card::getNumber() const {
    return cardNumber;
}
