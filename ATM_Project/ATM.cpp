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

void ATM::validateCard(Card card) {
    std::cout << "Validating card " << card.getNumber() << std::endl; // DEBUG INFo
    bool present = db.getDataByCardNo(QString::fromStdString(card.getNumber()));

    if (present) {
        std::cout << "yes" << std::endl; // DEBUG INFo
        emit cardConfirmation();
    } else {
        std::cout << "no" << std::endl; // DEBUG INFo
        emit errorMsg("Such card doesn't exist, counterfeit!!", Welcome);
    }

}

