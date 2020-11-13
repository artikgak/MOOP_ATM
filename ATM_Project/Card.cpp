#include "Card.h"

Card::Card(const std::string& num):
    cardNumber(num)
{}

Card::Card(const Card& card):
    cardNumber(card.getNumber())
{}

Card& Card::operator=(const Card& card) {
    cardNumber = card.getNumber();
    return *this;
}

std::string Card::getPin() const {
    return "1234"; // TODO CHANGR!!!!!
}

std::string Card::getNumber() const {
    return cardNumber;
}
