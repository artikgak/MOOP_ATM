#include "ATM.h"
#include "mainwindow.h"

#include <iostream>
#include <QString>

ATM::ATM():
    mainW(nullptr),
    db(*new DataBase()),
    card(nullptr)
{
}


ATM::~ATM() {
    delete card;
}

bool ATM::insertCard(Card c) {
    if (card == nullptr)
        return false;

    card = &c;
    return true;
}

void ATM::pushButton(const Button button) {
    switch (state) {
    case Idle:
    case S1:
    case S2:
    case S3:
    case Fin:
    case Mntnc:

        break;



//    default:
        ;
    }

}

void ATM::validateCard(std::string cardNum) {
    assert(card==nullptr); // Card-reader should be empty

    std::cout << "Validating card " << cardNum << std::endl; // DEBUG INFo
    Card* retrieved = db.getDataByCardNo(QString::fromStdString(cardNum));

    if (retrieved) {
        std::cout << "yes" << std::endl; // DEBUG INFo
        card = retrieved;
        emit goToPage(EnterPIN);
    } else {
        std::cout << "no" << std::endl; // DEBUG INFo
        emit errorMsg("Such card doesn't exist, counterfeit!!", Welcome);
    }

}
void ATM::validatePin(std::string pin) {
    assert(card!=nullptr); // There should be a card in card-reader

    if (pin == card->getPin()) { //change to card pin
        emit goToPage(Menu);
    } else {
        emit errorMsg("Wrong pin code, try again", EnterPIN);
    }

}
