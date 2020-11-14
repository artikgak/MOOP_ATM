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
    }

}

void ATM::validateCard(std::string cardNum) {
    assert(card==nullptr); // Card-reader should be empty

    std::cout << "Validating card " << cardNum << std::endl; // DEBUG INFO
    Card* retrieved = db.getDataByCardNo(QString::fromStdString(cardNum));

    delete retrieved; //DELETE LATER
    retrieved = new Card("1234567812345678");  //DELETE LATER
    std::cout << retrieved << std::endl;  //DELETE LATER

    if (retrieved) {
        card = retrieved;
        emit goToPage(EnterPIN);
    } else {
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

void ATM::ejectCard() {
    assert(card!=nullptr); // There should be a card in card-reader
    delete card;
    card = nullptr;
}
