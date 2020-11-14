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

void ATM::validateCard(std::string cardNum) {
    assert(card==nullptr); // Card-reader should be empty

    std::cout << "Validating card " << cardNum << std::endl; // DEBUG INFO
    bool retrieved = db.getDataByCardNo(cardNum);
    retrieved =true; // DELETE LATER
    if (retrieved) {
        card = new Card("1234567812345678");  //DELETE LATER;
        emit goToPage(EnterPIN);
    } else {
        emit errorMsg("Such card doesn't exist, counterfeit!!", Welcome);
    }

}
void ATM::validatePin(std::string pin) {
    assert(card!=nullptr); // There should be a card in card-reader

    bool correct = db.checkPin(card->getNumber(), pin);
    correct =true; // DELETE LATER

    if (correct) { //change to card pin
        emit goToPage(Menu);
    } else {
        emit errorMsg("Wrong pin code, try again", EnterPIN);
    }

}

void ATM::ejectCard() {
    assert(card!=nullptr); // There should be a card in card-reader
    delete card;
    card = nullptr;
    emit goToPage(Welcome);
}
